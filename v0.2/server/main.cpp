/*
 * @file main.c
 * @author Michal Bogon
 * @coauthor Igor Kaminski
 * @date 03'rd Dec 2020
 * @brief File containing the main function.
 * @ver 0.2
 */

#include "Ryzyko_classes.hpp"
#include "Ryzyko_prototypes.hpp"
#include "SerwerTCP.hpp"
#include "SerwerMULTICAST.h"
#include <sys/syslog.h>



////////////////////////////////////////////// MAIN \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int main(int argc, char** argv)
{
    // bool gameIsRunning = true;

    // Classic World initialization // 
    // int menuOption = mainMenu();

    setlogmask(LOG_UPTO(LOG_INFO));
	daemon_init(argv[0], LOG_LOCAL1, LOG_DAEMON);
    syslog(LOG_NOTICE, ">------------------- SERVER START -------------------< \n");
    char buffer[MAXLINE];

    int argv0size = 20;
	strncpy(argv[0],"Risk-game",argv0size);
	
	int multicast_pipe[2];
	if (pipe (multicast_pipe) == -1) { exit(1); }
	
	int info = 1;
	
	int multicast_pid = fork();
	if (multicast_pid == 0){
		strncpy(argv[0],"Risk-UDP-multicast",argv0size);
		ServMULTICAST(&multicast_pipe[0]);
	}
	else{   // Whole program
    
    int c2pPipe[2];                         // Child to Parent Pipe
    int p2cPipe[2];                         // Parent to Child Pipe
    int operation;
    
    
    if (pipe (c2pPipe) == -1) { exit(1); }
    if (pipe (p2cPipe) == -1) { exit(2); }

    std::string                             stringTemp;
    std::stringstream                       stringStreamTemp;
    PipeHelper                              pipeComStructure;
    pipeComStructure.p2cPipe[0]             = p2cPipe[0];
    pipeComStructure.p2cPipe[1]             = p2cPipe[1];
    pipeComStructure.c2pPipe[0]             = c2pPipe[0];
    pipeComStructure.c2pPipe[1]             = c2pPipe[1];
    pipeComStructure.stringAddress          = &stringTemp;
    pipeComStructure.stringStreamAddress    = &stringStreamTemp;

    int pid = fork();

    
    // Server TCP - child
    if (pid == 0) 
    {
        close(p2cPipe[1]);
        close(c2pPipe[0]);

        strncpy(argv[0],"Risk-TCP",argv0size);
        servTCP(&p2cPipe[0], &c2pPipe[1]);

        close(p2cPipe[0]);
        close(c2pPipe[1]);

    }

    // Backend (game) - parent
    else
    {
        close(p2cPipe[0]);
        close(c2pPipe[1]);

        // Reading number of players from server
        int numberOfPlayers_ServRecv;
        if (read (c2pPipe[0], &numberOfPlayers_ServRecv, sizeof(int [2])) == -1) printf("Read pipe error");

        // Reading player nicks from server
        char arrayOfChars[150];
        if (read(c2pPipe[0], &arrayOfChars, sizeof(arrayOfChars)) == -1) printf("Read pipe error");

		char buff1[MAXPLAYERS][25];
		sscanf(arrayOfChars,"%s %s %s %s %s %s", buff1[0], buff1[1], buff1[2], buff1[3], buff1[4], buff1[5]);

        if (write(multicast_pipe[1], &info, sizeof(int)) == -1) printf("Write pipe error");// closing multicast
        kill (multicast_pid, SIGKILL);      // just in case if multicast didn't close itself

		
		char* arrayOfNicks[numberOfPlayers_ServRecv];
		for (int temp = 0; temp < numberOfPlayers_ServRecv; temp++){
			arrayOfNicks[temp] = buff1[temp];
		}
		
		
        Sector exemplaryWorld(numberOfPlayers_ServRecv, arrayOfNicks);
        
        
        /*
        if (menuOption == 1 || menuOption == 2)
        {
            //Sector exemplaryWorld;
            system("clear");
            std::cout << "This is new world" << std::endl;
        }
        else if (menuOption == 2)
            std::cout << "Not developed yet" << std::endl;

            
        else if (menuOption == 4)
            exit(0);
        else 
        {
            std::cerr << "Something went wrong with main menu, please let me know, that this error has occurred, so I can fix it. Mail: michalbogon@o2.pl" << std::endl;
            exit(1);
        }
        */

        ////////////////////////////////////////////////// GAME INIT //////////////////////////////////////////////////
        #ifndef gameInit

        bool gameInit_bool = true, wrongNumber_bool = false;
        srand(time(NULL));
        int playerID = rand() % exemplaryWorld.World::numberOfPlayers_Getter();   // to ma być losowane przez 
        pipeComStructure.playerID_Address = &playerID;
        const int startingPlayer = playerID;
        if(write(p2cPipe[1] , &playerID, sizeof(int)) == -1) printf("Write pipe error");
        int defaultNumberOfSquadsInSector = 1;


        while (gameInit_bool)
        {
            playerID %= exemplaryWorld.World::numberOfPlayers_Getter();              // playerID %= numberOfPlayers;
            bool regionSettlement_success = false;

            /* if (write(p2cPipe[1], &operationCliChng, sizeof(int))    == -1) { printf("Write pipe error"); }
            if (write(p2cPipe[1], &playerID, sizeof(int))            == -1) { printf("Write pipe error"); } */
            pipeComParent (&pipeComStructure, operationCliChng);



            bool squadPlacementMenu = true;
            while (squadPlacementMenu)
            {
                int option;
                std::map <int, std::string> mapOfSectorsPlayerPossess;

                memset(buffer, 0, sizeof(buffer));
                stringStreamTemp << "Placing squads on the map: " << exemplaryWorld.World::vectorOfPlayers[playerID].nick << "\n"
                      << "Options:\n"
                      << "1 - Where player squads are present\n"
                      << "2 - Where player can place squads\n"
                      << "3 - move to squad placement\n" << std::endl;

                stringStreamTemp << "Option: ";

                pipeComParent(&pipeComStructure, operationREAD);
                option = atoi(pipeComStructure.buffer);
                std::cout << "option: " << option << std::endl;

                if (option == 1)
                {
                    mapOfSectorsPlayerPossess = exemplaryWorld.mapOfSectorsPlayerPossess(exemplaryWorld.World::vectorOfPlayers[playerID].nick);

                    for (auto it = mapOfSectorsPlayerPossess.begin(); it != mapOfSectorsPlayerPossess.end(); it++)
                        stringStreamTemp << it->first << " - " << it->second << std::endl;
                }

                else if (option == 2)
                {

                    mapOfSectorsPlayerPossess = exemplaryWorld.mapOfSectorsPlayerPossess("NULL");

                    for (auto it = mapOfSectorsPlayerPossess.begin(); it != mapOfSectorsPlayerPossess.end(); it++)
                        stringStreamTemp << it->first << " - " << it->second << std::endl;

                }
                else if (option == 3)
                {
                    squadPlacementMenu = false;
                    break;
                }
                else
                {
                    stringStreamTemp << "Please enter values between 1 - 3\n";
                }

                pipeComParent(&pipeComStructure, operationWRITE);
            }


            while(!regionSettlement_success)
            {
                int sectorID;                
                bool sectorIDInputSetting = true;
                while (sectorIDInputSetting)
                {
                    
                    stringStreamTemp << "\nChoose a sector ID to put your squad - ";    
                    pipeComParent(&pipeComStructure, operationREAD);
                    sectorID = atoiChecker(pipeComStructure.buffer);
                    /* sectorID = atoi(pipeComStructure.buffer);

                    if (sectorID == 0)      // If atoi read buffer incorrectly, compensate
                    {
                        stringTemp = pipeComStructure.buffer;
                        if (stringTemp.find("0") == std::string::npos)
                            sectorID = -1;
                    } */


                    if (sectorID >= 0 && sectorID < 42)
                    {
                        sectorIDInputSetting = false;
                        break;
                    }
                    else
                    {
                        stringStreamTemp << "Please enter a number between 0 - 41\n";
                        pipeComParent(&pipeComStructure, operationWRITE);
                    }
                }
                

                // players choose sectors, they acquire
                if (exemplaryWorld.sectorMap_playerName_Getter(exemplaryWorld.allSectors[sectorID]) == "NULL")
                {
                    exemplaryWorld.sectorMap_playerName_Setter(exemplaryWorld.allSectors[sectorID], exemplaryWorld.World::vectorOfPlayers[playerID].nick);
                    exemplaryWorld.sectorMap_numberOfSquadsInSector_Setter(exemplaryWorld.allSectors[sectorID], defaultNumberOfSquadsInSector);
                    regionSettlement_success = true;
                }

                else
                {
                    stringStreamTemp << "This sector is already occupied. Please choose another" << std::endl;
                    pipeComParent(&pipeComStructure, operationWRITE);
                    regionSettlement_success = false;
                }
                
                
                // checking, if all sectors are acquired. If yes: gameInit_bool = false && break. If not, playerID++, continue;
                if (regionSettlement_success)
                {
                    if (exemplaryWorld.allSectorsAcquired_checker())
                    {
                        gameInit_bool = false;
                        break;
                    }

                    else
                        playerID++;
                }

                else        
                {
                    stringStreamTemp << "Please enter a number between 0 - 41";
                    pipeComParent(&pipeComStructure, operationWRITE);
                }
                
            }
        }
        #endif// gameInit

        /////////////////////////////////////////////////// MAIN LOOP /////////////////////////////////////////////
        #ifndef mainLoop

        stringStreamTemp << "The game has started!" << std::endl;
        pipeComParent(&pipeComStructure, operationWRITE_2ALL);
        bool gameIsRunning = true;
        playerID = startingPlayer;   // starting player ID (has to be set in constructor probably)
        stringStreamTemp << "Starting player is " << exemplaryWorld.World::vectorOfPlayers[playerID].nick << std::endl;
        pipeComParent(&pipeComStructure, operationWRITE_2ALL);

        while (gameIsRunning)
        {
            exemplaryWorld.regionChecker();
            playerID %= exemplaryWorld.World::numberOfPlayers_Getter();              // playerID %= numberOfPlayers;
            pipeComParent(&pipeComStructure, operationCliChng);
            int reinforcements = exemplaryWorld.reinforements(exemplaryWorld.World::vectorOfPlayers[playerID].nick);       
            std::map <int, std::string> mapOfSectorsPlayerPossess;
            mapOfSectorsPlayerPossess = exemplaryWorld.mapOfSectorsPlayerPossess(exemplaryWorld.World::vectorOfPlayers[playerID].nick);

            bool squadPlacementMenu = true;
            while (squadPlacementMenu)
            {
                int option;

                stringStreamTemp << "Your turn " << exemplaryWorld.World::vectorOfPlayers[playerID].nick << std::endl
                    << "You have to place " << reinforcements << " squads in sectors you control:\n"
                    << "1 - Information about sectors you control and number of present squads\n"
                    << "2 - Reinforcements placement\n"
                    << "3 - Save game\n"
                    << "4 - Exit game" << std::endl;
                stringStreamTemp << "Option: ";
                pipeComParent(&pipeComStructure, operationREAD);


                option = atoiChecker(pipeComStructure.buffer);
                if (option == 1)
                {
                    // PROTOTYPE

                    for (auto it = mapOfSectorsPlayerPossess.begin(); it != mapOfSectorsPlayerPossess.end(); it++)
                        stringStreamTemp << "Sector ID = " << it->first << " - " << it->second 
                        << ", squads present = " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter (it->second) << std::endl;
                }
                    // funkcja wyżej
                else if (option == 2)
                {
                    squadPlacementMenu = false;
                    break;
                }
                else if (option == 3)
                    stringStreamTemp << "Not developed yet!" << std::endl;
                else if (option == 4)
                {
                    stringStreamTemp << "Exiting game" << std::endl;
                    pipeComParent(&pipeComStructure, operationWRITE_2ALL);
                    pipeComParent(&pipeComStructure, operationEXIT);
                    close(p2cPipe[1]);
                    close(c2pPipe[0]);
                    //kill(pid, SIGKILL);     // old
                    exit(0);
                }
                else
                {
                    stringStreamTemp << "Please enter a value between 1-4" << std::endl;
                }
                pipeComParent(&pipeComStructure, operationWRITE);
            }

            /////////////////////////////// Reinforcements placement ///////////////////////////////////

            bool sectorIDInputSetting = true;
            while (sectorIDInputSetting)
            {
                int sectorID;
                stringStreamTemp << "Choose a sector ID to put " << reinforcements << " squads - ";
                pipeComParent(&pipeComStructure, operationREAD);

                sectorID = atoiChecker(pipeComStructure.buffer);
                if (mapOfSectorsPlayerPossess.find(sectorID) != mapOfSectorsPlayerPossess.end())
                {
                    int presentSquadsinSector = exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[sectorID]);
                    int newValueOfSquadsInSector = presentSquadsinSector + reinforcements;
                    exemplaryWorld.sectorMap_numberOfSquadsInSector_Setter(exemplaryWorld.allSectors[sectorID], newValueOfSquadsInSector);
                    sectorIDInputSetting = true;
                    stringStreamTemp << "Successfully placed reinforcements!" << std::endl;
                    break;
                }
                else
                {
                    stringStreamTemp << "Please enter a number between 0 - 41 and you have to own it" << std::endl;
                }
            }
            pipeComParent(&pipeComStructure, operationWRITE);

            /////////////////////////////////// Combat phase ///////////////////////////////////////////
            bool combatPhaseMenu = true;
            while (combatPhaseMenu)
            {
                int combatPhase_option;     // gdy się wpisuje znak, a nie liczbę, to program się crashuje
                mapOfSectorsPlayerPossess = exemplaryWorld.mapOfSectorsPlayerPossess(exemplaryWorld.World::vectorOfPlayers[playerID].nick);     // refreshing

                stringStreamTemp << "Combat Phase" << std::endl
                    << "1 - Information about sectors you control and number of present squads\n"
                    << "2 - Attacking sector choice\n"
                    << "3 - Skip combat phase\n"
                    << "4 - Exit game\n";
                stringStreamTemp << "Option: ";
                pipeComParent(&pipeComStructure, operationREAD);


                combatPhase_option = atoiChecker(pipeComStructure.buffer);
                if (combatPhase_option == 1)
                {
                    for (auto it = mapOfSectorsPlayerPossess.begin(); it != mapOfSectorsPlayerPossess.end(); it++)
                        stringStreamTemp << "Sector ID = " << it->first << " - " << it->second
                        << ", squads present = " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(it->second) << std::endl;
                    pipeComParent(&pipeComStructure, operationWRITE);
                }

                else if (combatPhase_option == 2)
                {
                    // wybór sektora, z którego będzie miał być atak
                    bool combatPhase_sectorChoice = true;
                    while (combatPhase_sectorChoice)
                    {
                        // MENU
                        stringStreamTemp << "Choose sector you want to attack from: ";
                        int combatPhase_attackSector;     // gdy się wpisuje znak, a nie liczbę, to program się crashuje
                        pipeComParent(&pipeComStructure, operationREAD);

                        combatPhase_attackSector = atoiChecker(pipeComStructure.buffer);
                        if (mapOfSectorsPlayerPossess.find(combatPhase_attackSector) != mapOfSectorsPlayerPossess.end())
                        {
                            // informacja, jakie sektory można zaatakować
                            std::map <int, std::string> mapOfNeighbouringSectors = exemplaryWorld.mapOfNeighbouringSectors(exemplaryWorld.allSectors[combatPhase_attackSector]);
                            bool combatPhase_attackChoice = true;
                            while (combatPhase_attackChoice)
                            {
                                int combatPhase_attackChoiceOption;
                                stringStreamTemp << "Combat Phase" << std::endl
                                    << "1 - Information about sectors in neighbourhood, you can possibly attack\n"
                                    << "2 - Attack sector choice & information about its owner and present army\n"
                                    << "3 - Get back to Combat Phase\n";
                                stringStreamTemp << "Option: ";
                                pipeComParent(&pipeComStructure, operationREAD);

                                combatPhase_attackChoiceOption = atoiChecker(pipeComStructure.buffer);
                                if (combatPhase_attackChoiceOption == 1)
                                {
                                    // Information about sectors in neighbourhood
                                    stringStreamTemp << "Sectors in neighbourhood: " << std::endl;
                                    for (auto it = mapOfNeighbouringSectors.begin(); it != mapOfNeighbouringSectors.end(); it++)
                                        stringStreamTemp << "Sector ID: " << it->first << ", Sector name: " << it->second 
                                        << ", Owner: " << exemplaryWorld.sectorMap_playerName_Getter(it->second)
                                        << ", present squads: " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(it->second) << std::endl;    // to musi jeszcze sprawdzać ownerów
                                    pipeComParent(&pipeComStructure, operationWRITE);
                                }

                                else if (combatPhase_attackChoiceOption == 2)
                                {
                                    // Attack sector choice (requires confirmation) & information about its owner and present army
                                    stringStreamTemp << "Attack sector choice (ID): " << std::endl;
                                    bool combatPhase_sectorToAttack = true;
                                    int attackSector;
                                    while (combatPhase_sectorToAttack)
                                    {
                                        pipeComParent(&pipeComStructure, operationREAD);

                                        attackSector = atoiChecker(pipeComStructure.buffer);
                                        if ((mapOfNeighbouringSectors.find(attackSector) != mapOfNeighbouringSectors.end()) 
                                            && (exemplaryWorld.vectorOfPlayers[playerID].nick) != exemplaryWorld.sectorMap_playerName_Getter(exemplaryWorld.allSectors[attackSector]))
                                        {
                                            combatPhase_sectorToAttack = false;
                                            break;
                                        }
                                        else
                                        {
                                            stringStreamTemp << "You've entered wrong value. Please try again" << std::endl;
                                        }
                                    }

                                    stringStreamTemp << "You have chosen " << exemplaryWorld.allSectors[attackSector]
                                        << ", owner " << exemplaryWorld.sectorMap_playerName_Getter(exemplaryWorld.allSectors[attackSector])
                                        << ", present squads: " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[attackSector])
                                        << std::endl;
                                    stringStreamTemp << "Choose number of squads, you want attack with: ";
                                    bool combatPhase_numberOfAttackingSquads_choice = true;
                                    int numberOfAttackingSquads;
                                    while (combatPhase_numberOfAttackingSquads_choice)
                                    {
                                        pipeComParent(&pipeComStructure, operationREAD);

                                        numberOfAttackingSquads = atoiChecker(pipeComStructure.buffer);
                                        if ((numberOfAttackingSquads) <=
                                            (exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[combatPhase_attackSector]) - 1))
                                        {
                                            int presentNumberOfSquads = exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[combatPhase_attackSector]);
                                            int newNumberOfSquadsInSector = presentNumberOfSquads - numberOfAttackingSquads;
                                            exemplaryWorld.sectorMap_numberOfSquadsInSector_Setter(exemplaryWorld.allSectors[combatPhase_attackSector], newNumberOfSquadsInSector);
                                            exemplaryWorld.squadEngagement(exemplaryWorld.allSectors[combatPhase_attackSector],
                                                exemplaryWorld.allSectors[attackSector], numberOfAttackingSquads, &pipeComStructure);
                                            combatPhase_sectorChoice = false;
                                            combatPhase_attackChoice = false;
                                            combatPhase_numberOfAttackingSquads_choice = false;
                                            break;
                                        }

                                        else if ((numberOfAttackingSquads) >
                                            (exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[combatPhase_attackSector]) - 1))
                                        {  
                                            stringStreamTemp << "Number of squads in this region is less or equal to number of squads you chose" << std::endl
                                            << "You chose " << numberOfAttackingSquads << ", but there are " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[combatPhase_attackSector])
                                            << ", you can attach with " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[combatPhase_attackSector]) - 1 << " or less" << std::endl;
                                            pipeComParent(&pipeComStructure, operationWRITE);
                                        }
                                        
                                        else
                                        {
                                            stringStreamTemp << "Something went wrong, please try again" << std::endl;
                                            pipeComParent(&pipeComStructure, operationWRITE);
                                        }
                                    }
                                }

                                else if (combatPhase_attackChoiceOption == 3)
                                {
                                    // Get back to Combat Phase
                                    combatPhase_sectorChoice = false;
                                    combatPhase_attackChoice = false;
                                    break;
                                }
                                else {
                                    stringStreamTemp << "Please enter a number between 1-3" << std::endl;
                                    pipeComParent(&pipeComStructure, operationWRITE);
                                }
                            }
                        }
                         /*    else
                            {
                                stringStreamTemp << "Please enter a number between 0 - 41 and you have to own it" << std::endl;
                            } */
                        // }
                        /* else
                        {
                            stringStreamTemp << "Please enter a number between 0 - 41 and you have to own it" << std::endl;
                        } */
                    }
                }

                else if (combatPhase_option == 3)
                {
                    combatPhaseMenu = false;
                    break;
                }

                else if (combatPhase_option == 4)
                {
                    stringStreamTemp << "Exiting game!" << std::endl;
                    pipeComParent(&pipeComStructure, operationWRITE_2ALL);
                    pipeComParent(&pipeComStructure, operationEXIT);
                    close(p2cPipe[1]);
                    close(c2pPipe[0]);
                    // how to close all children?
                    //kill(pid, SIGKILL);     // old
                    exit(0);
                }

                else
                {
                    stringStreamTemp << "Please enter number between 1-4" << std::endl;
                    pipeComParent(&pipeComStructure, operationWRITE);
                }
            }

            //////////////////////////////// SQUADS REARANGEMENT PHASE ///////////////////////////////
            system("clear");
            bool squadsRearangementPhase = true;
            while (squadsRearangementPhase)
            {
                int squadsRearangementPhase_option;
                mapOfSectorsPlayerPossess = exemplaryWorld.mapOfSectorsPlayerPossess(exemplaryWorld.World::vectorOfPlayers[playerID].nick);     // refreshing, not necessary

                stringStreamTemp << "Squads Rearangement Phase" << std::endl
                    << "1 - Information about sectors you control and number of present squads\n"
                    << "2 - Rearangement sector choice\n"
                    << "3 - Skip rearangement phase\n"
                    << "4 - Exit game\n";
                stringStreamTemp << "Option: ";
                bool squadsRearangementPhase_optionBool = true;
                while (squadsRearangementPhase_optionBool)
                {
                    pipeComParent(&pipeComStructure, operationREAD);
                    squadsRearangementPhase_option = atoiChecker(pipeComStructure.buffer);
                    if (squadsRearangementPhase_option == 1)
                    {
                        // information about sectors you control and number of present squads
                        for (auto it = mapOfSectorsPlayerPossess.begin(); it != mapOfSectorsPlayerPossess.end(); it++)
                            stringStreamTemp << "Sector ID = " << it->first << " - " << it->second
                            << ", squads present = " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(it->second) << std::endl;
                    }
                    else if (squadsRearangementPhase_option == 2)
                    {
                        // Rearangement sector choice
                        bool squadsRearangementPhase_menu = true;
                        while (squadsRearangementPhase_menu)
                        {
                            int sectorID_rearangement;
                            stringStreamTemp << "Choose a sector ID, from where you want to sent your troops: ";
                            pipeComParent(&pipeComStructure, operationREAD);

                            sectorID_rearangement = atoiChecker(pipeComStructure.buffer);
                            if (mapOfSectorsPlayerPossess.find(sectorID_rearangement) != mapOfSectorsPlayerPossess.end())
                            {
                                // please enter number of squads, you want to move
                                int numberOfSquadsToMove;
                                int sectorID_rearangementTarget;
                                bool squadsRearangementPhase_squadNumberInput = true;
                                while (squadsRearangementPhase_squadNumberInput)
                                {
                                    stringStreamTemp << "Choose number of squads, you want to move (at least 1 squad has to be present): ";
                                    pipeComParent(&pipeComStructure, operationREAD);

                                    numberOfSquadsToMove = atoiChecker(pipeComStructure.buffer);
                                    if (((numberOfSquadsToMove) 
                                        <= (exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[sectorID_rearangement]) - 1))
                                        && (numberOfSquadsToMove >= 0))
                                    {
                                        squadsRearangementPhase_squadNumberInput = false;
                                        break;
                                    }
                                    else if ((numberOfSquadsToMove)
                                        > (exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[sectorID_rearangement]) - 1))
                                    {
                                        stringStreamTemp << "You can't move more than " 
                                            << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[sectorID_rearangement]) - 1 << std::endl;
                                    }
                                    else
                                    {
                                        stringStreamTemp << "You have to input proper number of squads to move, that can't be greater"
                                            << "than: (number of present squads) -1" << std::endl
                                            << "Note, that you always have to have at least 1 squad present to own sector" << std::endl;
                                    }
                                }
                                bool squadsRearangementPhase_rearangementTarget = true;
                                while (squadsRearangementPhase_rearangementTarget)
                                {
                                    stringStreamTemp << "Choose sector(ID), you want to send reinfocements";
                                    pipeComParent(&pipeComStructure, operationREAD);

                                    sectorID_rearangementTarget = atoiChecker(pipeComStructure.buffer);
                                    if (mapOfSectorsPlayerPossess.find(sectorID_rearangementTarget) != mapOfSectorsPlayerPossess.end())
                                    {
                                        squadsRearangementPhase_rearangementTarget = false;
                                        break;
                                    }
                                    else
                                    {
                                        stringStreamTemp << "You have to enter ID of the sector you control" << std::endl;
                                    }
                                }
                                // Squad movement
                                int presentSquadsinSector = exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[sectorID_rearangement]);
                                int newValueOfSquadsInSector = presentSquadsinSector - numberOfSquadsToMove;
                                exemplaryWorld.sectorMap_numberOfSquadsInSector_Setter(exemplaryWorld.allSectors[sectorID_rearangement], newValueOfSquadsInSector);

                                int presentSquadsinTargetSector = exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[sectorID_rearangementTarget]);
                                int newValueOfSquadsInTargetSector = presentSquadsinTargetSector + numberOfSquadsToMove;
                                exemplaryWorld.sectorMap_numberOfSquadsInSector_Setter(exemplaryWorld.allSectors[sectorID_rearangementTarget], newValueOfSquadsInTargetSector);
                                stringStreamTemp << "Successfully moved reinforcements!" << std::endl;
                                pipeComParent(&pipeComStructure, operationWRITE);
                                squadsRearangementPhase = false;
                                squadsRearangementPhase_optionBool = false;
                                squadsRearangementPhase_menu = false;
                                break;
                            }
                            else
                            {
                                stringStreamTemp << "Please enter a number between 0 - 41 and you have to own it" << std::endl;
                            }
                        }
                    }
                    else if (squadsRearangementPhase_option == 3)
                    {
                        // Skip rearangement phase
                        squadsRearangementPhase_optionBool = false;
                        squadsRearangementPhase = false;
                        break;
                    }
                    else if (squadsRearangementPhase_option == 4)
                    {
                        // exit
                        stringStreamTemp << "Exiting game!" << std::endl;
                        pipeComParent(&pipeComStructure, operationWRITE_2ALL);
                        pipeComParent(&pipeComStructure, operationEXIT);
                        close(p2cPipe[1]);
                        close(c2pPipe[0]);
                        //kill(pid, SIGKILL);     // old
                        exit(0);
                    }
                    else 
                    {
                        stringStreamTemp << "Please enter number between 1-4" << std::endl;
                    }
                }
            }

            int numberOfErasedPlayers = exemplaryWorld.playerErasure();
            int newNumberOfPlayers = exemplaryWorld.numberOfPlayers_Getter() - numberOfErasedPlayers;

            if (exemplaryWorld.win())
            {
                stringStreamTemp << "Game has ended!" << std::endl
                    << "The winner is " << exemplaryWorld.winner << "!" << std::endl;
                pipeComParent(&pipeComStructure, operationWRITE_2ALL);
                pipeComParent(&pipeComStructure, operationEXIT);
                close(p2cPipe[1]);
                close(c2pPipe[0]);
                //kill(pid, SIGKILL);     // old
                exit(0);
            }
            else
            {
                playerID++;
            }
        }
        

        #endif// mainLoop
        /*
        while (gameIsRunning)
        {
            // Menu
            // GameInit - players place their starting squads             
            // Reinforcement placement phase - players place reinforcements, they get at the beggining of each turn
            // Combat phase - players fight with each other
            // Rearangement phase - players move squads from sectors to another sectors to defend most important sectors
            // win() if (win) {                                             
            // cout << game has beeen won by X, gz
            // gameIsRunning = false;
            // exit(0) }
            // else { Player++ }
        }
        */
    }
    }

}
