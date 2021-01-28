/*
 * @file main.c
 * @author Michal Bogon
 * @date 03'rd Dec 2020
 * @brief File containing the main function.
 * @ver 1.0
 */

#include "Ryzyko_classes.hpp"
#include "Ryzyko_prototypes.hpp"



////////////////////////////////////////////// MAIN \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int main()
{
    // bool gameIsRunning = true;

    // Classic World initialization // 
    int menuOption = mainMenu();
    Sector exemplaryWorld;

    if (menuOption == 1 || menuOption == 2)
    {
        //Sector exemplaryWorld;
        system("cls");
        std::cout << "This is new world" << std::endl;
    }
    /*else if (menuOption == 2)
        std::cout << "Not developed yet" << std::endl;*/

        
    else if (menuOption == 4)
        exit(0);
    else 
    {
        std::cerr << "Something went wrong with main menu, please let me know, that this error has occurred, so I can fix it. Mail: michalbogon@o2.pl" << std::endl;
        exit(1);
    }


    ////////////////////////////////////////////////// GAME INIT //////////////////////////////////////////////////
    #ifndef gameInit

    bool gameInit_bool = true;
    int playerID = 0;   // to ma być losowane przez 
    int defaultNumberOfSquadsInSector = 1;

    while (gameInit_bool)
    {
        playerID %= exemplaryWorld.World::numberOfPlayers_Getter();              // playerID %= numberOfPlayers;
        bool regionSettlement_success = false;



        bool squadPlacementMenu = true;
        while (squadPlacementMenu)
        {
            int option;     
            //std::vector <std::string> vectorOfSectorsPlayerPossess;
            std::map <int, std::string> mapOfSectorsPlayerPossess;
            
            //system("cls");
            std::cout << "Placing squads on the map: " << exemplaryWorld.World::vectorOfPlayers[playerID].nick << "\n"
                      << "Options:\n"
                      << "1 - Where player squads are present\n"
                      << "2 - Where player can place squads\n"
                      << "3 - move to squad placement\n" << std::endl;

            std::cout << "Option: ";
            if (std::cin >> option)
            {
                if (option == 1)
                {

                    mapOfSectorsPlayerPossess = exemplaryWorld.mapOfSectorsPlayerPossess(exemplaryWorld.World::vectorOfPlayers[playerID].nick);

                    for (auto it = mapOfSectorsPlayerPossess.begin(); it != mapOfSectorsPlayerPossess.end(); it++)
                        std::cout << it->first << " - " << it->second << std::endl;
                }
                else if (option == 2)
                {

                    mapOfSectorsPlayerPossess = exemplaryWorld.mapOfSectorsPlayerPossess("NULL");

                    for (auto it = mapOfSectorsPlayerPossess.begin(); it != mapOfSectorsPlayerPossess.end(); it++)
                        std::cout << it->first << " - " << it->second << std::endl;
                }
                else if (option == 3)
                {
                    squadPlacementMenu = false;
                    break;
                }
                else
                {
                    //system("cls");  // trzeba sprawdzić, czy działa!
                    std::cout << "Please enter values between 1 - 3" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            else
            {
                std::cout << "Please enter a number between 1-3" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }


        while(!regionSettlement_success)
        {
            int sectorID;
            std::cout << "\nChoose a sector ID to put your squad - ";       
            
            bool sectorIDInputSetting = true;
            while (sectorIDInputSetting)
            {
                if (std::cin >> sectorID)
                {
                    if (sectorID >= 0 && sectorID < 42)
                    {
                        sectorIDInputSetting = false;
                        break;
                    }
                    else
                    {
                        std::cout << "Please enter a number between 0 - 41" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                else
                {
                    std::cout << "Please enter a number between 0 - 41" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                std::cout << "This sector is already occupied. Please choose another" << std::endl;
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
                std::cout << "Please enter a number between 0 - 41";
                //std::cout << "Something went wrong, please try again" << std::endl;
                //std::cout << "Checker Else" << std::endl;
            }
            
        }
    }
    #endif gameInit

    /////////////////////////////////////////////////// MAIN LOOP /////////////////////////////////////////////
    #ifndef mainLoop

    std::cout << "The game has started!" << std::endl;
    bool gameIsRunning = true;
    playerID = 0;   // starting player ID (has to be set in constructor probably)
    std::cout << "Starting player is " << exemplaryWorld.World::vectorOfPlayers[playerID].nick << std::endl;

    while (gameIsRunning)
    {

        system("cls");
        exemplaryWorld.regionChecker();
        playerID %= exemplaryWorld.World::numberOfPlayers_Getter();              // playerID %= numberOfPlayers;
        int reinforcements = exemplaryWorld.reinforements(exemplaryWorld.World::vectorOfPlayers[playerID].nick);       
        std::map <int, std::string> mapOfSectorsPlayerPossess;
        mapOfSectorsPlayerPossess = exemplaryWorld.mapOfSectorsPlayerPossess(exemplaryWorld.World::vectorOfPlayers[playerID].nick);

        bool squadPlacementMenu = true;
        while (squadPlacementMenu)
        {
            int option;

            //system("cls");
            std::cout << "Your turn " << exemplaryWorld.World::vectorOfPlayers[playerID].nick << std::endl
                << "You have to place " << reinforcements << " squads in sectors you control:\n"
                << "1 - Information about sectors you control and number of present squads\n"
                << "2 - Reinforcements placement\n"
                << "3 - Save game\n"
                << "4 - Exit game" << std::endl;
            std::cout << "Option: ";
            if (std::cin >> option)
            {
                if (option == 1)
                {
                    // PROTOTYPE

                    for (auto it = mapOfSectorsPlayerPossess.begin(); it != mapOfSectorsPlayerPossess.end(); it++)
                        std::cout << "Sector ID = " << it->first << " - " << it->second 
                        << ", squads present = " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter (it->second) << std::endl;
                }
                    // funkcja wyżej
                else if (option == 2)
                {
                    squadPlacementMenu = false;
                    break;
                }
                else if (option == 3)
                    std::cout << "Not developed yet!" << std::endl;
                else if (option == 4)
                {
                    std::cout << "Exiting game" << std::endl;
                    exit(0);
                }
                else
                {
                    std::cout << "Please enter a value between 1-4" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            else
            {
                std::cout << "Please enter a value between 1-4" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        /////////////////////////////// Reinforcements placement ///////////////////////////////////

        bool sectorIDInputSetting = true;
        while (sectorIDInputSetting)
        {
            int sectorID;
            std::cout << "Choose a sector ID to put " << reinforcements << " squads - ";
            if (std::cin >> sectorID)
            {
                if (mapOfSectorsPlayerPossess.find(sectorID) != mapOfSectorsPlayerPossess.end())
                {
                    int presentSquadsinSector = exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[sectorID]);
                    int newValueOfSquadsInSector = presentSquadsinSector + reinforcements;
                    exemplaryWorld.sectorMap_numberOfSquadsInSector_Setter(exemplaryWorld.allSectors[sectorID], newValueOfSquadsInSector);
                    sectorIDInputSetting = true;
                    std::cout << "Successfully placed reinforcements!" << std::endl;
                    break;
                }
                else
                {
                    std::cout << "Please enter a number between 0 - 41 and you have to own it" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            else
            {
                std::cout << "Please enter a number between 0 - 41 and you have to own it" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        /////////////////////////////////// Combat phase ///////////////////////////////////////////
        system("cls");
        bool combatPhaseMenu = true;
        while (combatPhaseMenu)
        {
            int combatPhase_option;     // gdy się wpisuje znak, a nie liczbę, to program się crashuje
            mapOfSectorsPlayerPossess = exemplaryWorld.mapOfSectorsPlayerPossess(exemplaryWorld.World::vectorOfPlayers[playerID].nick);     // refreshing

            std::cout << "Combat Phase" << std::endl
                << "1 - Information about sectors you control and number of present squads\n"
                << "2 - Attacking sector choice\n"
                << "3 - Skip combat phase\n"
                << "4 - Exit game\n";
            std::cout << "Option: ";
            if (std::cin >> combatPhase_option)
            {
                if (combatPhase_option == 1)
                {
                    for (auto it = mapOfSectorsPlayerPossess.begin(); it != mapOfSectorsPlayerPossess.end(); it++)
                        std::cout << "Sector ID = " << it->first << " - " << it->second
                        << ", squads present = " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(it->second) << std::endl;
                }
                else if (combatPhase_option == 2)
                {
                    // wybór sektora, z którego będzie miał być atak
                    bool combatPhase_sectorChoice = true;
                    while (combatPhase_sectorChoice)
                    {
                        // MENU
                        std::cout << "Choose sector you want to attack from: ";
                        int combatPhase_attackSector;     // gdy się wpisuje znak, a nie liczbę, to program się crashuje
                        if (std::cin >> combatPhase_attackSector)
                        {
                            if (mapOfSectorsPlayerPossess.find(combatPhase_attackSector) != mapOfSectorsPlayerPossess.end())
                            {
                                // informacja, jakie sektory można zaatakować
                                std::map <int, std::string> mapOfNeighbouringSectors = exemplaryWorld.mapOfNeighbouringSectors(exemplaryWorld.allSectors[combatPhase_attackSector]);
                                bool combatPhase_attackChoice = true;
                                while (combatPhase_attackChoice)
                                {
                                    int combatPhase_attackChoiceOption;
                                    std::cout << "Combat Phase" << std::endl
                                        << "1 - Information about sectors in neighbourhood, you can possibly attack\n"
                                        << "2 - Attack sector choice & information about its owner and present army\n"
                                        << "3 - Get back to Combat Phase\n";
                                    std::cout << "Option: ";
                                    if (std::cin >> combatPhase_attackChoiceOption)
                                    {
                                        if (combatPhase_attackChoiceOption == 1)
                                        {
                                            // Information about sectors in neighbourhood
                                            std::cout << "Sectors in neighbourhood: " << std::endl;
                                            for (auto it = mapOfNeighbouringSectors.begin(); it != mapOfNeighbouringSectors.end(); it++)
                                                std::cout << "Sector ID: " << it->first << ", Sector name: " << it->second 
                                                << ", Owner: " << exemplaryWorld.sectorMap_playerName_Getter(it->second)
                                                << ", present squads: " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(it->second) << std::endl;    // to musi jeszcze sprawdzać ownerów
                                        }
                                        else if (combatPhase_attackChoiceOption == 2)
                                        {
                                            // Attack sector choice (requires confirmation) & information about its owner and present army
                                            std::cout << "Attack sector choice (ID): " << std::endl;
                                            bool combatPhase_sectorToAttack = true;
                                            int attackSector;
                                            while (combatPhase_sectorToAttack)
                                            {
                                                if (std::cin >> attackSector)
                                                {
                                                    if ((mapOfNeighbouringSectors.find(attackSector) != mapOfNeighbouringSectors.end()) 
                                                        && (exemplaryWorld.vectorOfPlayers[playerID].nick) != exemplaryWorld.sectorMap_playerName_Getter(exemplaryWorld.allSectors[attackSector]))
                                                    {
                                                        combatPhase_sectorToAttack = false;
                                                        break;
                                                    }
                                                    else
                                                    {
                                                        std::cout << "You've entered wrong value. Please try again" << std::endl;
                                                        std::cin.clear();
                                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                    }
                                                }
                                                else
                                                {
                                                    std::cout << "You've entered wrong value. Please try again" << std::endl;
                                                    std::cin.clear();
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                }
                                            }
                                            std::cout << "You have chosen " << exemplaryWorld.allSectors[attackSector]
                                                << ", owner " << exemplaryWorld.sectorMap_playerName_Getter(exemplaryWorld.allSectors[attackSector])
                                                << ", present squads: " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[attackSector])
                                                << std::endl;
                                            std::cout << "Choose number of squads, you want attack with: ";
                                            bool combatPhase_numberOfAttackingSquads_choice = true;
                                            int numberOfAttackingSquads;
                                            while (combatPhase_numberOfAttackingSquads_choice)
                                            {
                                                if (std::cin >> numberOfAttackingSquads)
                                                {
                                                    if ((numberOfAttackingSquads) <=
                                                        (exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[combatPhase_attackSector]) - 1))
                                                    {
                                                        int presentNumberOfSquads = exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[combatPhase_attackSector]);
                                                        int newNumberOfSquadsInSector = presentNumberOfSquads - numberOfAttackingSquads;
                                                        exemplaryWorld.sectorMap_numberOfSquadsInSector_Setter(exemplaryWorld.allSectors[combatPhase_attackSector], newNumberOfSquadsInSector);
                                                        exemplaryWorld.squadEngagement(exemplaryWorld.allSectors[combatPhase_attackSector],
                                                            exemplaryWorld.allSectors[attackSector], numberOfAttackingSquads);
                                                        combatPhase_sectorChoice = false;
                                                        combatPhase_attackChoice = false;
                                                        combatPhase_numberOfAttackingSquads_choice = false;
                                                        break;
                                                    }
                                                    else if ((numberOfAttackingSquads) >
                                                        (exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[combatPhase_attackSector]) - 1))
                                                        
                                                        std::cout << "Number of squads in this region is less or equal to number of squads you chose" << std::endl
                                                        << "You chose " << numberOfAttackingSquads << ", but there are " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[combatPhase_attackSector])
                                                        << ", you can attach with " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[combatPhase_attackSector]) - 1 << " or less" << std::endl;
                                                    else
                                                    {
                                                        std::cout << "Something went wrong, please try again" << std::endl;
                                                        std::cin.clear();
                                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                    }
                                                }
                                                else
                                                {
                                                    std::cout << "Wrong input" << std::endl;
                                                    std::cin.clear();
                                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                }
                                            }
                                        }
                                        else if (combatPhase_attackChoiceOption == 3)
                                        {
                                            // Get back to Combat Phase
                                            combatPhase_sectorChoice = false;
                                            combatPhase_attackChoice = false;
                                            break;
                                            //system("cls");
                                        }
                                        else {
                                            std::cout << "Please enter a number between 1-3" << std::endl;
                                            std::cin.clear();
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        }
                                    }
                                    else {
                                        std::cout << "Please enter a number between 1-3" << std::endl;
                                        std::cin.clear();
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    }
                                }
                            }
                            else
                            {
                                std::cout << "Please enter a number between 0 - 41 and you have to own it" << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            }
                        }
                        else
                        {
                            std::cout << "Please enter a number between 0 - 41 and you have to own it" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }
                }
                else if (combatPhase_option == 3)
                {
                    combatPhaseMenu = false;
                    break;
                }
                else if (combatPhase_option == 4)
                {
                    std::cout << "Exiting game!" << std::endl;
                    exit(0);
                }
                else
                {
                    std::cout << "Please enter number between 1-4" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
            else
            {
                std::cout << "Please enter number between 1-4" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        //////////////////////////////// SQUADS REARANGEMENT PHASE ///////////////////////////////
        system("cls");
        bool squadsRearangementPhase = true;
        while (squadsRearangementPhase)
        {
            int squadsRearangementPhase_option;
            mapOfSectorsPlayerPossess = exemplaryWorld.mapOfSectorsPlayerPossess(exemplaryWorld.World::vectorOfPlayers[playerID].nick);     // refreshing, not necessary

            std::cout << "Squads Rearangement Phase" << std::endl
                << "1 - Information about sectors you control and number of present squads\n"
                << "2 - Rearangement sector choice\n"
                << "3 - Skip rearangement phase\n"
                << "4 - Exit game\n";
            std::cout << "Option: ";
            bool squadsRearangementPhase_optionBool = true;
            while (squadsRearangementPhase_optionBool)
            {
                if (std::cin >> squadsRearangementPhase_option) 
                {
                    if (squadsRearangementPhase_option == 1)
                    {
                        // information about sectors you control and number of present squads
                        for (auto it = mapOfSectorsPlayerPossess.begin(); it != mapOfSectorsPlayerPossess.end(); it++)
                            std::cout << "Sector ID = " << it->first << " - " << it->second
                            << ", squads present = " << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(it->second) << std::endl;
                    }
                    else if (squadsRearangementPhase_option == 2)
                    {
                        // Rearangement sector choice
                        bool squadsRearangementPhase_menu = true;
                        while (squadsRearangementPhase_menu)
                        {
                            int sectorID_rearangement;
                            std::cout << "Choose a sector ID, from where you want to sent your troops: ";
                            if (std::cin >> sectorID_rearangement)
                            {
                                if (mapOfSectorsPlayerPossess.find(sectorID_rearangement) != mapOfSectorsPlayerPossess.end())
                                {
                                    // please enter number of squads, you want to move
                                    int numberOfSquadsToMove;
                                    int sectorID_rearangementTarget;
                                    bool squadsRearangementPhase_squadNumberInput = true;
                                    while (squadsRearangementPhase_squadNumberInput)
                                    {
                                        std::cout << "Choose number of squads, you want to move (at least 1 squad has to be present): ";
                                        if (std::cin >> numberOfSquadsToMove)
                                        {
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
                                                std::cout << "You can't move more than " 
                                                    << exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[sectorID_rearangement]) - 1 << std::endl;
                                            }
                                            else
                                            {
                                                std::cout << "You have to input proper number of squads to move, that can't be greater"
                                                    << "than: (number of present squads) -1" << std::endl
                                                    << "Note, that you always have to have at least 1 squad present to own sector" << std::endl;
                                                std::cin.clear();
                                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                            }
                                        }
                                        else
                                        {
                                            std::cout << "You have to input proper number of squads to move, that can't be greater"
                                                << "than (number of present squads) -1" << std::endl
                                                << "Note, that you always have to have at least 1 squad present to own sector" << std::endl;
                                            std::cin.clear();
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        }
                                    }
                                    bool squadsRearangementPhase_rearangementTarget = true;
                                    while (squadsRearangementPhase_rearangementTarget)
                                    {
                                        std::cout << "Choose sector(ID), you want to send reinfocements";
                                        if (std::cin >> sectorID_rearangementTarget)
                                        {
                                            if (mapOfSectorsPlayerPossess.find(sectorID_rearangementTarget) != mapOfSectorsPlayerPossess.end())
                                            {
                                                squadsRearangementPhase_rearangementTarget = false;
                                                break;
                                            }
                                            else
                                            {
                                                std::cout << "You have to enter ID of the sector you control" << std::endl;
                                                std::cin.clear();
                                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                            }
                                        }
                                        else
                                        {
                                            std::cout << "You have to enter ID of the sector you control" << std::endl;
                                            std::cin.clear();
                                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                        }
                                    }
                                    // Squad movement
                                    int presentSquadsinSector = exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[sectorID_rearangement]);
                                    int newValueOfSquadsInSector = presentSquadsinSector - numberOfSquadsToMove;
                                    exemplaryWorld.sectorMap_numberOfSquadsInSector_Setter(exemplaryWorld.allSectors[sectorID_rearangement], newValueOfSquadsInSector);

                                    int presentSquadsinTargetSector = exemplaryWorld.sectorMap_numberOfSquadsInSector_Getter(exemplaryWorld.allSectors[sectorID_rearangementTarget]);
                                    int newValueOfSquadsInTargetSector = presentSquadsinTargetSector + numberOfSquadsToMove;
                                    exemplaryWorld.sectorMap_numberOfSquadsInSector_Setter(exemplaryWorld.allSectors[sectorID_rearangementTarget], newValueOfSquadsInTargetSector);
                                    std::cout << "Successfully moved reinforcements!" << std::endl;
                                    squadsRearangementPhase = false;
                                    squadsRearangementPhase_optionBool = false;
                                    squadsRearangementPhase_menu = false;
                                    break;
                                }
                                else
                                {
                                    std::cout << "Please enter a number between 0 - 41 and you have to own it" << std::endl;
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                            }
                            else
                            {
                                std::cout << "Please enter a number between 0 - 41 and you have to own it" << std::endl;
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                        std::cout << "Exiting game!" << std::endl;
                        exit(0);
                    }
                    else 
                    {
                        std::cout << "Please enter number between 1-4" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                else
                {
                    std::cout << "Please enter number between 1-4" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }

        int numberOfErasedPlayers = exemplaryWorld.playerErasure();
        int newNumberOfPlayers = exemplaryWorld.numberOfPlayers_Getter() - numberOfErasedPlayers;

        if (exemplaryWorld.win())
        {
            std::cout << "Game has ended!" << std::endl
                << "The winner is " << exemplaryWorld.winner << "!" << std::endl;
            exit(0);
        }
        else
        {
            playerID++;
        }
    }

    #endif mainLoop
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
