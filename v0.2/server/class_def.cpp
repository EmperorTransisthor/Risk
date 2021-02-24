#include "Ryzyko_classes.hpp"
#include "Ryzyko_prototypes.hpp"


World::World()
{
    //numberOfPlayers_Setter();
    listOfBonusSquadsForRegionPossession["Asia"] = 7;                       // 7 additional squads for ASIA (ID = 0) possession      
    listOfBonusSquadsForRegionPossession["Africa"] = 3;                     // 3 additional squads for AFRICA (ID = 1) possession
    listOfBonusSquadsForRegionPossession["Europe"] = 5;                     // 5 additional squads for EUROPE (ID = 2) possession
    listOfBonusSquadsForRegionPossession["NorthAmerica"] = 5;               // 5 additional squads for NORTHAMERICA (ID = 3) possession
    listOfBonusSquadsForRegionPossession["Oceania"] = 2;                    // 2 additional squads for OCEANIA (ID = 4) possession
    listOfBonusSquadsForRegionPossession["SouthAmerica"] = 3;               // 3 additional squads for SOUTHAMERICA (ID = 5) possession
}

World::World(std::map <std::string, int> WorldMapInput)
{
    //numberOfPlayers_Setter();
    listOfBonusSquadsForRegionPossession = WorldMapInput;                       // 
}

void World::numberOfPlayers_Setter()
{
    bool settingNumbers = true;
    while (settingNumbers)
    {
        std::cout << "Specify number of players: ";
        bool numberOfPlayersSetting = true;
        while (numberOfPlayersSetting)
        {
            if (std::cin >> numberOfPlayers)
            {
                numberOfPlayersSetting = false;
                break;
            }
            else
            {
                std::cout << "The proper value of players in game can't be less than 2 and more than 6" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        std::cout << std::endl;
        if (numberOfPlayers == 2 || numberOfPlayers == 3 || numberOfPlayers == 4 || numberOfPlayers == 5 || numberOfPlayers == 6)
            settingNumbers = false;
        else
            std::cout << "The proper value of players in game can't be less than 2 and more than 6" << std::endl;
    }
}

void World::numberOfPlayers_Setter2(int input)
{
    numberOfPlayers = input;
}

int World::numberOfPlayers_Getter()
{
    return numberOfPlayers;
}

void World::listOfBonusSquadsForRegionPossession_Setter(std::string regionName, int numberOfBonusSquads)
{
    listOfBonusSquadsForRegionPossession[regionName] = numberOfBonusSquads;
}

void World::playerConv( PlayerServ playerFrom, Player* player )
{
    std::cout << "Assigning nick: " << playerFrom.nickChar << std::endl;
    player->nick = playerFrom.nickChar;
    std::cout << "Assigned nick:  " << player->nick << std::endl;
}

Region::Region() : World()
{
    // Default values for regionData map
    regionData["Asia"] = "NULL";
    regionData["Africa"] = "NULL";
    regionData["Europe"] = "NULL";
    regionData["NorthAmerica"] = "NULL";
    regionData["Oceania"] = "NULL";
    regionData["SouthAmerica"] = "NULL";

    allRegions = { "Asia" , "Africa" , "Europe" , "NorthAmerica" , "Oceania" , "SouthAmerica" };        // to nie jest potrzebne do testowania, mo�na to przecie� zrobi� r�cznie

    // Default values for second map
    std::vector <std::string> sectors_Asia;
    std::vector <std::string> sectors_Africa;
    std::vector <std::string> sectors_Europe;
    std::vector <std::string> sectors_NorthAmerica;
    std::vector <std::string> sectors_Oceania;
    std::vector <std::string> sectors_SouthAmerica;
    // sectors_X [ ID ]
    sectors_Asia.push_back("MiddleEast");                           // ID = 0
    sectors_Asia.push_back("Afganistan");                           // ID = 1
    sectors_Asia.push_back("India");                                // ID = 2
    sectors_Asia.push_back("Ural");                                 // ID = 3
    sectors_Asia.push_back("Siberia");                              // ID = 4
    sectors_Asia.push_back("Yakutia");                              // ID = 5
    sectors_Asia.push_back("Kamchatka");                            // ID = 6
    sectors_Asia.push_back("EastSiberia");                          // ID = 7
    sectors_Asia.push_back("Mongolia");                             // ID = 8
    sectors_Asia.push_back("China");                                // ID = 9
    sectors_Asia.push_back("Siam");                                 // ID = 10
    sectors_Asia.push_back("Japan");                                // ID = 11

    sectors_Africa.push_back("Egypt");                              // ID = 12
    sectors_Africa.push_back("NorthAfrica");                        // ID = 13
    sectors_Africa.push_back("EastAfrica");                         // ID = 14
    sectors_Africa.push_back("Kongo");                              // ID = 15
    sectors_Africa.push_back("SouthAfrica");                        // ID = 16
    sectors_Africa.push_back("Madagascar");                         // ID = 17

    sectors_Europe.push_back("GreatBritain");                       // ID = 18
    sectors_Europe.push_back("Iceland");                            // ID = 19
    sectors_Europe.push_back("Scandinavia");                        // ID = 20
    sectors_Europe.push_back("Ukraine");                            // ID = 21
    sectors_Europe.push_back("NorthEurope");                        // ID = 22
    sectors_Europe.push_back("SouthEurope");                        // ID = 23
    sectors_Europe.push_back("WestEurope");                         // ID = 24

    sectors_NorthAmerica.push_back("Alaska");                       // ID = 25
    sectors_NorthAmerica.push_back("Alberta");                      // ID = 26
    sectors_NorthAmerica.push_back("NorthWestArea");                // ID = 27
    sectors_NorthAmerica.push_back("Greenland");                    // ID = 28
    sectors_NorthAmerica.push_back("Ontario");                      // ID = 29
    sectors_NorthAmerica.push_back("Quebec");                       // ID = 30
    sectors_NorthAmerica.push_back("WestUS");                       // ID = 31
    sectors_NorthAmerica.push_back("EastUS");                       // ID = 32
    sectors_NorthAmerica.push_back("CentralAmerica");               // ID = 33

    sectors_Oceania.push_back("Indonesia");                         // ID = 34
    sectors_Oceania.push_back("NewGuinea");                         // ID = 35
    sectors_Oceania.push_back("WestAustralia");                     // ID = 36
    sectors_Oceania.push_back("EastAustralia");                     // ID = 37

    sectors_SouthAmerica.push_back("Venezuela");                    // ID = 38
    sectors_SouthAmerica.push_back("Brasil");                       // ID = 39
    sectors_SouthAmerica.push_back("Peru");                         // ID = 40
    sectors_SouthAmerica.push_back("Argentina");                    // ID = 41

    regionSectors["Asia"] = sectors_Asia;
    regionSectors["Africa"] = sectors_Africa;
    regionSectors["Europe"] = sectors_Europe;
    regionSectors["NorthAmerica"] = sectors_NorthAmerica;
    regionSectors["Oceania"] = sectors_Oceania;
    regionSectors["SouthAmerica"] = sectors_SouthAmerica;

    allSectors.reserve(sectors_Asia.size() + sectors_Africa.size()              // memory allocation in order to concatenate vectors
        + sectors_Europe.size() + sectors_NorthAmerica.size()
        + sectors_Oceania.size() + sectors_SouthAmerica.size());

    // Concatenation of all sectors to one vector of
    allSectors.insert(allSectors.end(), sectors_Asia.begin(), sectors_Asia.end());                          // + Asia
    allSectors.insert(allSectors.end(), sectors_Africa.begin(), sectors_Africa.end());                      // + Africa
    allSectors.insert(allSectors.end(), sectors_Europe.begin(), sectors_Europe.end());                      // + Europe
    allSectors.insert(allSectors.end(), sectors_NorthAmerica.begin(), sectors_NorthAmerica.end());          // + NorthAmerica
    allSectors.insert(allSectors.end(), sectors_Oceania.begin(), sectors_Oceania.end());                    // + Oceania
    allSectors.insert(allSectors.end(), sectors_SouthAmerica.begin(), sectors_SouthAmerica.end());          // + SouthAmerica


    // Prototype Map
    allSectorsMap[0] = allSectors[0];
    allSectorsMap[1] = allSectors[1];
    allSectorsMap[2] = allSectors[2];
    allSectorsMap[3] = allSectors[3];
    allSectorsMap[4] = allSectors[4];
    allSectorsMap[5] = allSectors[5];
    allSectorsMap[6] = allSectors[6];
    allSectorsMap[7] = allSectors[7];
    allSectorsMap[8] = allSectors[8];
    allSectorsMap[9] = allSectors[9];
    allSectorsMap[10] = allSectors[10];
    allSectorsMap[11] = allSectors[11];
    allSectorsMap[12] = allSectors[12];
    allSectorsMap[13] = allSectors[13];
    allSectorsMap[14] = allSectors[14];
    allSectorsMap[15] = allSectors[15];
    allSectorsMap[16] = allSectors[16];
    allSectorsMap[17] = allSectors[17];
    allSectorsMap[18] = allSectors[18];
    allSectorsMap[19] = allSectors[19];
    allSectorsMap[20] = allSectors[20];
    allSectorsMap[21] = allSectors[21];
    allSectorsMap[22] = allSectors[22];
    allSectorsMap[23] = allSectors[23];
    allSectorsMap[24] = allSectors[24];
    allSectorsMap[25] = allSectors[25];
    allSectorsMap[26] = allSectors[26];
    allSectorsMap[27] = allSectors[27];
    allSectorsMap[28] = allSectors[28];
    allSectorsMap[29] = allSectors[29];
    allSectorsMap[30] = allSectors[30];
    allSectorsMap[31] = allSectors[31];
    allSectorsMap[32] = allSectors[32];
    allSectorsMap[33] = allSectors[33];
    allSectorsMap[34] = allSectors[34];
    allSectorsMap[35] = allSectors[35];
    allSectorsMap[36] = allSectors[36];
    allSectorsMap[37] = allSectors[37];
    allSectorsMap[38] = allSectors[38];
    allSectorsMap[39] = allSectors[39];
    allSectorsMap[40] = allSectors[40];
    allSectorsMap[41] = allSectors[41];
}



Region::Region(std::string allRegions,                                          // putting regions and vectors of sectors particular region consists of
    std::vector <std::string> asiaSectors, std::vector <std::string> africaSectors,
    std::vector <std::string> europeSectors, std::vector <std::string> northAmericaSectors,
    std::vector <std::string> oceaniaSectors, std::vector <std::string> southAmericaSectors)// :
    //World(std::map <std::string, int> worldMapInput)
{
    // Przypisanie regionowi sektor�w wraz z NULLami do nich wszystkich

    //regionData = mapaRegion�w; // b��d celowy, szybko mog� skoczy�, aby uzupe�ni�
}

void Region::setRegion(std::pair <std::string, std::string> region_map_change)
{
    regionData[region_map_change.first] = region_map_change.second;
}

void Region::regionAdditionalSquads(std::string regionName)
{
    if (regionData[regionName] != "NULL")
    {
        //World::bonusSquadz;
    }
}

bool Region::possession(std::map<std::string, std::string> region_map)
{
    for (auto i : region_map) {
        if (region_map.begin()->second == i.second)
        {
            if (region_map.end()->second == i.second)
                return true;

            continue;
        }

        else if (region_map.begin()->second != i.second)
            return false;

        else
        {
            std::cerr << "Error while seaching in map region_map" << std::endl;
            return false;
        }

    }
    return false;
}

int Region::additionalSquads(std::string regionName)
{
    //return world.ListOfBonusSquadsForRegionPossession_Getter[NameOfTheRegion];
    return 0;
}

Sector::Sector(int numberOfPlayers_FromServ, char* arrayOfNicks[MAXPLAYERS])
{

    //int numberOfPlayers = numberOfPlayers_Getter();
    //int numberOfPlayers = vectorOfPlayers_Serv.size();
    
    numberOfPlayers_Setter2(numberOfPlayers_FromServ);
    int numberOfPlayers = numberOfPlayers_FromServ;
    std::cout << "Number of Players (Server): " << numberOfPlayers_Getter() << std::endl;
    std::cout << "Number of Players (Game):   " << numberOfPlayers << std::endl;

    struct World::Player player1;
    struct World::Player player2;
    struct World::Player player3;
    struct World::Player player4;
    struct World::Player player5;
    struct World::Player player6;

    // czy stuktury player1, 2, 3, 4, 5, 6 s� usuwane podczas wrzucenia ich do wektora?
    World::vectorOfPlayers.push_back(player1);                  // Player ID = 0
    World::vectorOfPlayers.push_back(player2);                  // Player ID = 1
    World::vectorOfPlayers.push_back(player3);                  // Player ID = 2
    World::vectorOfPlayers.push_back(player4);                  // Player ID = 3
    World::vectorOfPlayers.push_back(player5);                  // Player ID = 4
    World::vectorOfPlayers.push_back(player6);                  // Player ID = 5

    if (!(numberOfPlayers_FromServ > 1 and numberOfPlayers_FromServ < 7))
    {
        std::cout << "Something went wrong! Number of players: " << numberOfPlayers << std::endl;
        exit (13);
    }

    for (int temp = 0; temp < numberOfPlayers; temp++)
    {
        vectorOfPlayers[temp].implemented = true;
        vectorOfPlayers[temp].nick = arrayOfNicks[temp];
    }
/*
    switch (numberOfPlayers)
    {

    case 2:
        vectorOfPlayers[0].implemented = true;
        vectorOfPlayers[1].implemented = true;
        //std::cout << "Enter first player nick: "; std::cin >> vectorOfPlayers[0].nick;
        //std::cout << "Enter second player nick: "; std::cin >> vectorOfPlayers[1].nick;
        vectorOfPlayers[0].nick = arrayOfNicks[0];
        vectorOfPlayers[1].nick = arrayOfNicks[1];
        break;

    case 3:
        vectorOfPlayers[0].implemented = true;
        vectorOfPlayers[1].implemented = true;
        vectorOfPlayers[2].implemented = true;
        //std::cout << "Enter first player nick: "; std::cin >> vectorOfPlayers[0].nick;
        //std::cout << "Enter second player nick: "; std::cin >> vectorOfPlayers[1].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[2].nick;
        vectorOfPlayers[0].nick = arrayOfNicks[0];
        vectorOfPlayers[1].nick = arrayOfNicks[1];
        vectorOfPlayers[2].nick = arrayOfNicks[2];
        break;

    case 4:
        vectorOfPlayers[0].implemented = true;
        vectorOfPlayers[1].implemented = true;
        vectorOfPlayers[2].implemented = true;
        vectorOfPlayers[3].implemented = true;
        //std::cout << "Enter first player nick: "; std::cin >> vectorOfPlayers[0].nick;
        //std::cout << "Enter second player nick: "; std::cin >> vectorOfPlayers[1].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[2].nick;
        //std::cout << "Enter forth player nick: "; std::cin >> vectorOfPlayers[3].nick;
        vectorOfPlayers[0].nick = arrayOfNicks[0];
        vectorOfPlayers[0].nick = arrayOfNicks[0];
        vectorOfPlayers[0].nick = arrayOfNicks[0]; 
        vectorOfPlayers[0].nick = arrayOfNicks[0]; 
        break;

    case 5:
        vectorOfPlayers[0].implemented = true;
        vectorOfPlayers[1].implemented = true;
        vectorOfPlayers[2].implemented = true;
        vectorOfPlayers[3].implemented = true;
        vectorOfPlayers[4].implemented = true;
        //std::cout << "Enter first player nick: "; std::cin >> vectorOfPlayers[0].nick;
        //std::cout << "Enter second player nick: "; std::cin >> vectorOfPlayers[1].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[2].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[3].nick;
        //std::cout << "Enter fifth player nick: "; std::cin >> vectorOfPlayers[4].nick;
        playerConv(vectorOfPlayers_Serv[0], &vectorOfPlayers[0]); 
        playerConv(vectorOfPlayers_Serv[1], &vectorOfPlayers[1]); 
        playerConv(vectorOfPlayers_Serv[2], &vectorOfPlayers[2]); 
        playerConv(vectorOfPlayers_Serv[3], &vectorOfPlayers[3]); 
        playerConv(vectorOfPlayers_Serv[4], &vectorOfPlayers[4]); 
        break;

    case 6:
        vectorOfPlayers[0].implemented = true;
        vectorOfPlayers[1].implemented = true;
        vectorOfPlayers[2].implemented = true;
        vectorOfPlayers[3].implemented = true;
        vectorOfPlayers[4].implemented = true;
        vectorOfPlayers[5].implemented = true;
        //std::cout << "Enter first player nick: "; std::cin >> vectorOfPlayers[0].nick;
        //std::cout << "Enter second player nick: "; std::cin >> vectorOfPlayers[1].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[2].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[3].nick;
        //std::cout << "Enter fifth player nick: "; std::cin >> vectorOfPlayers[4].nick;
        //std::cout << "Enter sixth player nick: "; std::cin >> vectorOfPlayers[5].nick;
        playerConv(vectorOfPlayers_Serv[0], &vectorOfPlayers[0]); 
        playerConv(vectorOfPlayers_Serv[1], &vectorOfPlayers[1]); 
        playerConv(vectorOfPlayers_Serv[2], &vectorOfPlayers[2]); 
        playerConv(vectorOfPlayers_Serv[3], &vectorOfPlayers[3]); 
        playerConv(vectorOfPlayers_Serv[4], &vectorOfPlayers[4]); 
        playerConv(vectorOfPlayers_Serv[5], &vectorOfPlayers[5]); 
        break;

    default:
        std::cout << "Something went wrong..." << std::endl;
        exit(1);
    }
*/
    // Deletion of unnecessary players (first two players are always present, game shouldn't start if they aren't)

    if (!vectorOfPlayers[5].implemented)
        vectorOfPlayers.pop_back();
    if (!vectorOfPlayers[4].implemented)
        vectorOfPlayers.pop_back();
    if (!vectorOfPlayers[3].implemented)
        vectorOfPlayers.pop_back();
    if (!vectorOfPlayers[2].implemented)
        vectorOfPlayers.pop_back();

    // World Initialization (setting all sectors owners from unspecified to NULL        &&      making all sectors empty (numberOfSquadsInSector = 0)


    // Sector ID = 0
    sectorMap[allSectors[0]].first = "NULL";
    sectorMap[allSectors[0]].second = 0;
    // Sector ID = 1
    sectorMap[allSectors[1]].first = "NULL";
    sectorMap[allSectors[1]].second = 0;
    // Sector ID = 2
    sectorMap[allSectors[2]].first = "NULL";
    sectorMap[allSectors[2]].second = 0;
    // Sector ID = 3
    sectorMap[allSectors[3]].first = "NULL";
    sectorMap[allSectors[3]].second = 0;
    // Sector ID = 4
    sectorMap[allSectors[4]].first = "NULL";
    sectorMap[allSectors[4]].second = 0;
    // Sector ID = 5
    sectorMap[allSectors[5]].first = "NULL";
    sectorMap[allSectors[5]].second = 0;
    // Sector ID = 6
    sectorMap[allSectors[6]].first = "NULL";
    sectorMap[allSectors[6]].second = 0;
    // Sector ID = 7
    sectorMap[allSectors[7]].first = "NULL";
    sectorMap[allSectors[7]].second = 0;
    // Sector ID = 8
    sectorMap[allSectors[8]].first = "NULL";
    sectorMap[allSectors[8]].second = 0;
    // Sector ID = 9
    sectorMap[allSectors[9]].first = "NULL";
    sectorMap[allSectors[9]].second = 0;
    // Sector ID = 10
    sectorMap[allSectors[10]].first = "NULL";
    sectorMap[allSectors[10]].second = 0;
    // Sector ID = 11
    sectorMap[allSectors[11]].first = "NULL";
    sectorMap[allSectors[11]].second = 0;
    // Sector ID = 12
    sectorMap[allSectors[12]].first = "NULL";
    sectorMap[allSectors[12]].second = 0;
    // Sector ID = 13
    sectorMap[allSectors[13]].first = "NULL";
    sectorMap[allSectors[13]].second = 0;
    // Sector ID = 14
    sectorMap[allSectors[14]].first = "NULL";
    sectorMap[allSectors[14]].second = 0;
    // Sector ID = 15
    sectorMap[allSectors[15]].first = "NULL";
    sectorMap[allSectors[15]].second = 0;
    // Sector ID = 16
    sectorMap[allSectors[16]].first = "NULL";
    sectorMap[allSectors[16]].second = 0;
    // Sector ID = 17
    sectorMap[allSectors[17]].first = "NULL";
    sectorMap[allSectors[17]].second = 0;
    // Sector ID = 18
    sectorMap[allSectors[18]].first = "NULL";
    sectorMap[allSectors[18]].second = 0;
    // Sector ID = 19
    sectorMap[allSectors[19]].first = "NULL";
    sectorMap[allSectors[19]].second = 0;
    // Sector ID = 20
    sectorMap[allSectors[20]].first = "NULL";
    sectorMap[allSectors[20]].second = 0;
    // Sector ID = 21
    sectorMap[allSectors[21]].first = "NULL";
    sectorMap[allSectors[21]].second = 0;
    // Sector ID = 22
    sectorMap[allSectors[22]].first = "NULL";
    sectorMap[allSectors[22]].second = 0;
    // Sector ID = 23
    sectorMap[allSectors[23]].first = "NULL";
    sectorMap[allSectors[23]].second = 0;
    // Sector ID = 24
    sectorMap[allSectors[24]].first = "NULL";
    sectorMap[allSectors[24]].second = 0;
    // Sector ID = 25
    sectorMap[allSectors[25]].first = "NULL";
    sectorMap[allSectors[25]].second = 0;
    // Sector ID = 26
    sectorMap[allSectors[26]].first = "NULL";
    sectorMap[allSectors[26]].second = 0;
    // Sector ID = 27
    sectorMap[allSectors[27]].first = "NULL";
    sectorMap[allSectors[27]].second = 0;
    // Sector ID = 28
    sectorMap[allSectors[28]].first = "NULL";
    sectorMap[allSectors[28]].second = 0;
    // Sector ID = 29
    sectorMap[allSectors[29]].first = "NULL";
    sectorMap[allSectors[29]].second = 0;
    // Sector ID = 30
    sectorMap[allSectors[30]].first = "NULL";
    sectorMap[allSectors[30]].second = 0;
    // Sector ID = 31
    sectorMap[allSectors[31]].first = "NULL";
    sectorMap[allSectors[31]].second = 0;
    // Sector ID = 32
    sectorMap[allSectors[32]].first = "NULL";
    sectorMap[allSectors[32]].second = 0;
    // Sector ID = 33
    sectorMap[allSectors[33]].first = "NULL";
    sectorMap[allSectors[33]].second = 0;
    // Sector ID = 34
    sectorMap[allSectors[34]].first = "NULL";
    sectorMap[allSectors[34]].second = 0;
    // Sector ID = 35
    sectorMap[allSectors[35]].first = "NULL";
    sectorMap[allSectors[35]].second = 0;
    // Sector ID = 36
    sectorMap[allSectors[36]].first = "NULL";
    sectorMap[allSectors[36]].second = 0;
    // Sector ID = 37
    sectorMap[allSectors[37]].first = "NULL";
    sectorMap[allSectors[37]].second = 0;
    // Sector ID = 38
    sectorMap[allSectors[38]].first = "NULL";
    sectorMap[allSectors[38]].second = 0;
    // Sector ID = 39
    sectorMap[allSectors[39]].first = "NULL";
    sectorMap[allSectors[39]].second = 0;
    // Sector ID = 40
    sectorMap[allSectors[40]].first = "NULL";
    sectorMap[allSectors[40]].second = 0;
    // Sector ID = 41
    sectorMap[allSectors[41]].first = "NULL";
    sectorMap[allSectors[41]].second = 0;

    // Filling sectors neighbourhood
    // Asia neighbour
    // Sector ID = 0
    std::vector <std::string> sectorNeighbourhood_temp{ "SouthEurope" , "Egypt" , "EastAfrica" , "India" , "Afganistan" , "Ukraine" };
    neighbourSectors[allSectors[0]] = sectorNeighbourhood_temp;
    // Sector ID = 1
    sectorNeighbourhood_temp = { "Ukraine", "MiddleEast", "India", "China", "Ural" };
    neighbourSectors[allSectors[1]] = sectorNeighbourhood_temp;
    // Sector ID = 2
    sectorNeighbourhood_temp = { "Siam" , "China" , "Afganistan" , "MiddleEast" };
    neighbourSectors[allSectors[2]] = sectorNeighbourhood_temp;
    // Sector ID = 3
    sectorNeighbourhood_temp = { "Ukraine" , "Afganistan" , "China" , "Siberia" };
    neighbourSectors[allSectors[3]] = sectorNeighbourhood_temp;
    // Sector ID = 4
    sectorNeighbourhood_temp = { "Ural" , "China" , "Mongolia" , "EastSiberia" , "Yakutia" };
    neighbourSectors[allSectors[4]] = sectorNeighbourhood_temp;
    // Sector ID = 5
    sectorNeighbourhood_temp = { "Siberia" , "EastSiberia" , "Kamchatka" };
    neighbourSectors[allSectors[5]] = sectorNeighbourhood_temp;
    // Sector ID = 6
    sectorNeighbourhood_temp = { "Yakutia" , "EastSiberia" , "Mongolia" , "Japan" , "Alaska" };
    neighbourSectors[allSectors[6]] = sectorNeighbourhood_temp;
    // Sector ID = 7
    sectorNeighbourhood_temp = { "Yakutia" , "Siberia" , "Mongolia" , "Kamchatka" };
    neighbourSectors[allSectors[7]] = sectorNeighbourhood_temp;
    // Sector ID = 8
    sectorNeighbourhood_temp = { "EastSiberia" , "Siberia" , "China" , "Japan" , "Kamchatka" };
    neighbourSectors[allSectors[8]] = sectorNeighbourhood_temp;
    // Sector ID = 9
    sectorNeighbourhood_temp = { "Mongolia" , "Siberia" , "Ural" , "Afganistan" , "India" , "Siam" };
    neighbourSectors[allSectors[9]] = sectorNeighbourhood_temp;
    // Sector ID = 10
    sectorNeighbourhood_temp = { "Indonesia" , "China" , "India" };
    neighbourSectors[allSectors[10]] = sectorNeighbourhood_temp;
    // Sector ID = 11
    sectorNeighbourhood_temp = { "Mongolia", "Kamchatka" };
    neighbourSectors[allSectors[11]] = sectorNeighbourhood_temp;
    // Africa neighbour
    // Sector ID = 12
    sectorNeighbourhood_temp = { "SouthEurope" , "MiddleEast" , "NorthAfrica" , "EastAfrica" };
    neighbourSectors[allSectors[12]] = sectorNeighbourhood_temp;
    // Sector ID = 13
    sectorNeighbourhood_temp = { "Brasil", "Kongo" , "EastAfrica" , "Egypt" , "SouthEurope" , "WestEurope" };
    neighbourSectors[allSectors[13]] = sectorNeighbourhood_temp;
    // Sector ID = 14
    sectorNeighbourhood_temp = { "Egypt" , "NorthAfrica" , "Kongo" , "SouthAfrica" , "Madagascar" , "MiddleEast" };
    neighbourSectors[allSectors[14]] = sectorNeighbourhood_temp;
    // Sector ID = 15
    sectorNeighbourhood_temp = { "SouthAfrica" , "EastAfrica" , "NorthAfrica" };
    neighbourSectors[allSectors[15]] = sectorNeighbourhood_temp;
    // Sector ID = 16
    sectorNeighbourhood_temp = { "Madagascar" , "EastAfrica" , "Kongo" };
    neighbourSectors[allSectors[16]] = sectorNeighbourhood_temp;
    // Sector ID = 17
    sectorNeighbourhood_temp = { "SouthAfrica" , "EastAfrica" };
    neighbourSectors[allSectors[17]] = sectorNeighbourhood_temp;
    // Europe neighbour
    // Sector ID = 18
    sectorNeighbourhood_temp = { "Iceland" , "Scandinavia" , "WestEurope" };
    neighbourSectors[allSectors[18]] = sectorNeighbourhood_temp;
    // Sector ID = 19
    sectorNeighbourhood_temp = { "Greenland" , "GreatBritain" , "Scandinavia" };
    neighbourSectors[allSectors[19]] = sectorNeighbourhood_temp;
    // Sector ID = 20
    sectorNeighbourhood_temp = { "Iceland" , "GreatBritain" , "NorthEurope" , "Ukraine" };
    neighbourSectors[allSectors[20]] = sectorNeighbourhood_temp;
    // Sector ID = 21
    sectorNeighbourhood_temp = { "Scandinavia" , "NorthEurope" , "SouthEurope" , "MiddleEast" , "Afganistan" , "Ural" };
    neighbourSectors[allSectors[21]] = sectorNeighbourhood_temp;
    // Sector ID = 22
    sectorNeighbourhood_temp = { "Scandinavia" , "GreatBritain" , "WestEurope" , "SouthEurope" , "Ukraine" };
    neighbourSectors[allSectors[22]] = sectorNeighbourhood_temp;
    // Sector ID = 23
    sectorNeighbourhood_temp = { "NorthEurope" , "WestEurope" , "NorthAfrica" , "Egypt" , "MiddleEast" , "Ukraine" };
    neighbourSectors[allSectors[23]] = sectorNeighbourhood_temp;
    // Sector ID = 24
    sectorNeighbourhood_temp = { "NorthAfrica" , "SouthEurope" , "NorthEurope" , "GreatBritain" };
    neighbourSectors[allSectors[24]] = sectorNeighbourhood_temp;
    // NorthAmerica neighbour
    // Sector ID = 25
    sectorNeighbourhood_temp = { "Kamchatka" , "Alberta" , "NorthWestArea" };
    neighbourSectors[allSectors[25]] = sectorNeighbourhood_temp;
    // Sector ID = 26
    sectorNeighbourhood_temp = { "Alaska" , "NorthWestArea" , "Ontario" , "WestUS" };
    neighbourSectors[allSectors[26]] = sectorNeighbourhood_temp;
    // Sector ID = 27
    sectorNeighbourhood_temp = { "Alaska" , "Alberta" , "Ontario" , "Greenland" };
    neighbourSectors[allSectors[27]] = sectorNeighbourhood_temp;
    // Sector ID = 28
    sectorNeighbourhood_temp = { "NorthWestArea" , "Ontario" , "Quebec" , "Iceland" };
    neighbourSectors[allSectors[28]] = sectorNeighbourhood_temp;
    // Sector ID = 29
    sectorNeighbourhood_temp = { "NorthWestArea" , "Alberta" , "WestUS" , "EastUS" , "Quebec" , "Greenland" };
    neighbourSectors[allSectors[29]] = sectorNeighbourhood_temp;
    // Sector ID = 30
    sectorNeighbourhood_temp = { "Greenland" , "Ontario" , "EastUS" };
    neighbourSectors[allSectors[30]] = sectorNeighbourhood_temp;
    // Sector ID = 31
    sectorNeighbourhood_temp = { "EastUS" , "Ontario" , "Alberta" , "CentralAmerica" };
    neighbourSectors[allSectors[31]] = sectorNeighbourhood_temp;
    // Sector ID = 32
    sectorNeighbourhood_temp = { "WestUS" , "CentralAmerica" , "Quebec" , "Ontario" };
    neighbourSectors[allSectors[32]] = sectorNeighbourhood_temp;
    // Sector ID = 33
    sectorNeighbourhood_temp = { "WestUS" , "EastUS" , "Venezuela" };
    neighbourSectors[allSectors[33]] = sectorNeighbourhood_temp;
    // Oceania neighbour
    // Sector ID = 34
    sectorNeighbourhood_temp = { "Siam" , "NewGuinea" , "WestAustralia" };
    neighbourSectors[allSectors[34]] = sectorNeighbourhood_temp;
    // Sector ID = 35
    sectorNeighbourhood_temp = { "Indonesia" , "EastAustralia" , "WestAustralia" };
    neighbourSectors[allSectors[35]] = sectorNeighbourhood_temp;
    // Sector ID = 36
    sectorNeighbourhood_temp = { "EastAustralia" , "NewGuinea" , "Indonesia" };
    neighbourSectors[allSectors[36]] = sectorNeighbourhood_temp;
    // Sector ID = 37
    sectorNeighbourhood_temp = { "NewGuinea" , "Indonesia" , "WestAustralia" };
    neighbourSectors[allSectors[37]] = sectorNeighbourhood_temp;
    // SouthAmerica neighbour
    // Sector ID = 38
    sectorNeighbourhood_temp = { "CentralAmerica" , "Peru" , "Brasil" };
    neighbourSectors[allSectors[38]] = sectorNeighbourhood_temp;
    // Sector ID = 39
    sectorNeighbourhood_temp = { "Venezuela" , "Peru" , "Argentina" , "SouthAfrica" };
    neighbourSectors[allSectors[39]] = sectorNeighbourhood_temp;
    // Sector ID = 40
    sectorNeighbourhood_temp = { "Venezuela" , "Argentina" , "Brasil" };
    neighbourSectors[allSectors[40]] = sectorNeighbourhood_temp;
    // Sector ID = 41
    sectorNeighbourhood_temp = { "Peru", "Brasil" };
    neighbourSectors[allSectors[41]] = sectorNeighbourhood_temp;
    // Zrobienie tego, co ma zrobi� Sector
    std::cout << "World generation complete" << std::endl;
}

Sector::Sector(std::vector <PlayerServ> vectorOfPlayers_Serv)
{

    //int numberOfPlayers = numberOfPlayers_Getter();
    int numberOfPlayers = vectorOfPlayers_Serv.size();
    std::cout << "Number of Players (Game): " << numberOfPlayers << std::endl;
    numberOfPlayers_Setter2(numberOfPlayers);
    // std::cout << "Specify number of players: "; std::cin >> numberOfPlayers; std::cout << std::endl;
    std::cout << "Number of Players (Server): " << numberOfPlayers_Getter() << std::endl;

    struct World::Player player1;
    struct World::Player player2;
    struct World::Player player3;
    struct World::Player player4;
    struct World::Player player5;
    struct World::Player player6;

    // czy stuktury player1, 2, 3, 4, 5, 6 s� usuwane podczas wrzucenia ich do wektora?
    World::vectorOfPlayers.push_back(player1);                  // Player ID = 0
    World::vectorOfPlayers.push_back(player2);                  // Player ID = 1
    World::vectorOfPlayers.push_back(player3);                  // Player ID = 2
    World::vectorOfPlayers.push_back(player4);                  // Player ID = 3
    World::vectorOfPlayers.push_back(player5);                  // Player ID = 4
    World::vectorOfPlayers.push_back(player6);                  // Player ID = 5

    switch (numberOfPlayers)
    {

    case 2:
        vectorOfPlayers[0].implemented = true;
        vectorOfPlayers[1].implemented = true;
        //std::cout << "Enter first player nick: "; std::cin >> vectorOfPlayers[0].nick;
        //std::cout << "Enter second player nick: "; std::cin >> vectorOfPlayers[1].nick;
        playerConv(vectorOfPlayers_Serv[0], &vectorOfPlayers[0]); 
        playerConv(vectorOfPlayers_Serv[1], &vectorOfPlayers[1]); 
        break;

    case 3:
        vectorOfPlayers[0].implemented = true;
        vectorOfPlayers[1].implemented = true;
        vectorOfPlayers[2].implemented = true;
        //std::cout << "Enter first player nick: "; std::cin >> vectorOfPlayers[0].nick;
        //std::cout << "Enter second player nick: "; std::cin >> vectorOfPlayers[1].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[2].nick;
        playerConv(vectorOfPlayers_Serv[0], &vectorOfPlayers[0]); 
        playerConv(vectorOfPlayers_Serv[1], &vectorOfPlayers[1]); 
        playerConv(vectorOfPlayers_Serv[2], &vectorOfPlayers[2]); 
        break;

    case 4:
        vectorOfPlayers[0].implemented = true;
        vectorOfPlayers[1].implemented = true;
        vectorOfPlayers[2].implemented = true;
        vectorOfPlayers[3].implemented = true;
        //std::cout << "Enter first player nick: "; std::cin >> vectorOfPlayers[0].nick;
        //std::cout << "Enter second player nick: "; std::cin >> vectorOfPlayers[1].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[2].nick;
        //std::cout << "Enter forth player nick: "; std::cin >> vectorOfPlayers[3].nick;
        playerConv(vectorOfPlayers_Serv[0], &vectorOfPlayers[0]); 
        playerConv(vectorOfPlayers_Serv[1], &vectorOfPlayers[1]); 
        playerConv(vectorOfPlayers_Serv[2], &vectorOfPlayers[2]); 
        playerConv(vectorOfPlayers_Serv[3], &vectorOfPlayers[3]); 
        break;

    case 5:
        vectorOfPlayers[0].implemented = true;
        vectorOfPlayers[1].implemented = true;
        vectorOfPlayers[2].implemented = true;
        vectorOfPlayers[3].implemented = true;
        vectorOfPlayers[4].implemented = true;
        //std::cout << "Enter first player nick: "; std::cin >> vectorOfPlayers[0].nick;
        //std::cout << "Enter second player nick: "; std::cin >> vectorOfPlayers[1].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[2].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[3].nick;
        //std::cout << "Enter fifth player nick: "; std::cin >> vectorOfPlayers[4].nick;
        playerConv(vectorOfPlayers_Serv[0], &vectorOfPlayers[0]); 
        playerConv(vectorOfPlayers_Serv[1], &vectorOfPlayers[1]); 
        playerConv(vectorOfPlayers_Serv[2], &vectorOfPlayers[2]); 
        playerConv(vectorOfPlayers_Serv[3], &vectorOfPlayers[3]); 
        playerConv(vectorOfPlayers_Serv[4], &vectorOfPlayers[4]); 
        break;

    case 6:
        vectorOfPlayers[0].implemented = true;
        vectorOfPlayers[1].implemented = true;
        vectorOfPlayers[2].implemented = true;
        vectorOfPlayers[3].implemented = true;
        vectorOfPlayers[4].implemented = true;
        vectorOfPlayers[5].implemented = true;
        //std::cout << "Enter first player nick: "; std::cin >> vectorOfPlayers[0].nick;
        //std::cout << "Enter second player nick: "; std::cin >> vectorOfPlayers[1].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[2].nick;
        //std::cout << "Enter third player nick: "; std::cin >> vectorOfPlayers[3].nick;
        //std::cout << "Enter fifth player nick: "; std::cin >> vectorOfPlayers[4].nick;
        //std::cout << "Enter sixth player nick: "; std::cin >> vectorOfPlayers[5].nick;
        playerConv(vectorOfPlayers_Serv[0], &vectorOfPlayers[0]); 
        playerConv(vectorOfPlayers_Serv[1], &vectorOfPlayers[1]); 
        playerConv(vectorOfPlayers_Serv[2], &vectorOfPlayers[2]); 
        playerConv(vectorOfPlayers_Serv[3], &vectorOfPlayers[3]); 
        playerConv(vectorOfPlayers_Serv[4], &vectorOfPlayers[4]); 
        playerConv(vectorOfPlayers_Serv[5], &vectorOfPlayers[5]); 
        break;

    default:
        std::cout << "Something went wrong..." << std::endl;
        exit(1);
    }

    // Deletion of unnecessary players (first two players are always present, game shouldn't start if they aren't)

    if (!vectorOfPlayers[5].implemented)
        vectorOfPlayers.pop_back();
    if (!vectorOfPlayers[4].implemented)
        vectorOfPlayers.pop_back();
    if (!vectorOfPlayers[3].implemented)
        vectorOfPlayers.pop_back();
    if (!vectorOfPlayers[2].implemented)
        vectorOfPlayers.pop_back();

    // World Initialization (setting all sectors owners from unspecified to NULL        &&      making all sectors empty (numberOfSquadsInSector = 0)


    // Sector ID = 0
    sectorMap[allSectors[0]].first = "NULL";
    sectorMap[allSectors[0]].second = 0;
    // Sector ID = 1
    sectorMap[allSectors[1]].first = "NULL";
    sectorMap[allSectors[1]].second = 0;
    // Sector ID = 2
    sectorMap[allSectors[2]].first = "NULL";
    sectorMap[allSectors[2]].second = 0;
    // Sector ID = 3
    sectorMap[allSectors[3]].first = "NULL";
    sectorMap[allSectors[3]].second = 0;
    // Sector ID = 4
    sectorMap[allSectors[4]].first = "NULL";
    sectorMap[allSectors[4]].second = 0;
    // Sector ID = 5
    sectorMap[allSectors[5]].first = "NULL";
    sectorMap[allSectors[5]].second = 0;
    // Sector ID = 6
    sectorMap[allSectors[6]].first = "NULL";
    sectorMap[allSectors[6]].second = 0;
    // Sector ID = 7
    sectorMap[allSectors[7]].first = "NULL";
    sectorMap[allSectors[7]].second = 0;
    // Sector ID = 8
    sectorMap[allSectors[8]].first = "NULL";
    sectorMap[allSectors[8]].second = 0;
    // Sector ID = 9
    sectorMap[allSectors[9]].first = "NULL";
    sectorMap[allSectors[9]].second = 0;
    // Sector ID = 10
    sectorMap[allSectors[10]].first = "NULL";
    sectorMap[allSectors[10]].second = 0;
    // Sector ID = 11
    sectorMap[allSectors[11]].first = "NULL";
    sectorMap[allSectors[11]].second = 0;
    // Sector ID = 12
    sectorMap[allSectors[12]].first = "NULL";
    sectorMap[allSectors[12]].second = 0;
    // Sector ID = 13
    sectorMap[allSectors[13]].first = "NULL";
    sectorMap[allSectors[13]].second = 0;
    // Sector ID = 14
    sectorMap[allSectors[14]].first = "NULL";
    sectorMap[allSectors[14]].second = 0;
    // Sector ID = 15
    sectorMap[allSectors[15]].first = "NULL";
    sectorMap[allSectors[15]].second = 0;
    // Sector ID = 16
    sectorMap[allSectors[16]].first = "NULL";
    sectorMap[allSectors[16]].second = 0;
    // Sector ID = 17
    sectorMap[allSectors[17]].first = "NULL";
    sectorMap[allSectors[17]].second = 0;
    // Sector ID = 18
    sectorMap[allSectors[18]].first = "NULL";
    sectorMap[allSectors[18]].second = 0;
    // Sector ID = 19
    sectorMap[allSectors[19]].first = "NULL";
    sectorMap[allSectors[19]].second = 0;
    // Sector ID = 20
    sectorMap[allSectors[20]].first = "NULL";
    sectorMap[allSectors[20]].second = 0;
    // Sector ID = 21
    sectorMap[allSectors[21]].first = "NULL";
    sectorMap[allSectors[21]].second = 0;
    // Sector ID = 22
    sectorMap[allSectors[22]].first = "NULL";
    sectorMap[allSectors[22]].second = 0;
    // Sector ID = 23
    sectorMap[allSectors[23]].first = "NULL";
    sectorMap[allSectors[23]].second = 0;
    // Sector ID = 24
    sectorMap[allSectors[24]].first = "NULL";
    sectorMap[allSectors[24]].second = 0;
    // Sector ID = 25
    sectorMap[allSectors[25]].first = "NULL";
    sectorMap[allSectors[25]].second = 0;
    // Sector ID = 26
    sectorMap[allSectors[26]].first = "NULL";
    sectorMap[allSectors[26]].second = 0;
    // Sector ID = 27
    sectorMap[allSectors[27]].first = "NULL";
    sectorMap[allSectors[27]].second = 0;
    // Sector ID = 28
    sectorMap[allSectors[28]].first = "NULL";
    sectorMap[allSectors[28]].second = 0;
    // Sector ID = 29
    sectorMap[allSectors[29]].first = "NULL";
    sectorMap[allSectors[29]].second = 0;
    // Sector ID = 30
    sectorMap[allSectors[30]].first = "NULL";
    sectorMap[allSectors[30]].second = 0;
    // Sector ID = 31
    sectorMap[allSectors[31]].first = "NULL";
    sectorMap[allSectors[31]].second = 0;
    // Sector ID = 32
    sectorMap[allSectors[32]].first = "NULL";
    sectorMap[allSectors[32]].second = 0;
    // Sector ID = 33
    sectorMap[allSectors[33]].first = "NULL";
    sectorMap[allSectors[33]].second = 0;
    // Sector ID = 34
    sectorMap[allSectors[34]].first = "NULL";
    sectorMap[allSectors[34]].second = 0;
    // Sector ID = 35
    sectorMap[allSectors[35]].first = "NULL";
    sectorMap[allSectors[35]].second = 0;
    // Sector ID = 36
    sectorMap[allSectors[36]].first = "NULL";
    sectorMap[allSectors[36]].second = 0;
    // Sector ID = 37
    sectorMap[allSectors[37]].first = "NULL";
    sectorMap[allSectors[37]].second = 0;
    // Sector ID = 38
    sectorMap[allSectors[38]].first = "NULL";
    sectorMap[allSectors[38]].second = 0;
    // Sector ID = 39
    sectorMap[allSectors[39]].first = "NULL";
    sectorMap[allSectors[39]].second = 0;
    // Sector ID = 40
    sectorMap[allSectors[40]].first = "NULL";
    sectorMap[allSectors[40]].second = 0;
    // Sector ID = 41
    sectorMap[allSectors[41]].first = "NULL";
    sectorMap[allSectors[41]].second = 0;

    // Filling sectors neighbourhood
    // Asia neighbour
    // Sector ID = 0
    std::vector <std::string> sectorNeighbourhood_temp{ "SouthEurope" , "Egypt" , "EastAfrica" , "India" , "Afganistan" , "Ukraine" };
    neighbourSectors[allSectors[0]] = sectorNeighbourhood_temp;
    // Sector ID = 1
    sectorNeighbourhood_temp = { "Ukraine", "MiddleEast", "India", "China", "Ural" };
    neighbourSectors[allSectors[1]] = sectorNeighbourhood_temp;
    // Sector ID = 2
    sectorNeighbourhood_temp = { "Siam" , "China" , "Afganistan" , "MiddleEast" };
    neighbourSectors[allSectors[2]] = sectorNeighbourhood_temp;
    // Sector ID = 3
    sectorNeighbourhood_temp = { "Ukraine" , "Afganistan" , "China" , "Siberia" };
    neighbourSectors[allSectors[3]] = sectorNeighbourhood_temp;
    // Sector ID = 4
    sectorNeighbourhood_temp = { "Ural" , "China" , "Mongolia" , "EastSiberia" , "Yakutia" };
    neighbourSectors[allSectors[4]] = sectorNeighbourhood_temp;
    // Sector ID = 5
    sectorNeighbourhood_temp = { "Siberia" , "EastSiberia" , "Kamchatka" };
    neighbourSectors[allSectors[5]] = sectorNeighbourhood_temp;
    // Sector ID = 6
    sectorNeighbourhood_temp = { "Yakutia" , "EastSiberia" , "Mongolia" , "Japan" , "Alaska" };
    neighbourSectors[allSectors[6]] = sectorNeighbourhood_temp;
    // Sector ID = 7
    sectorNeighbourhood_temp = { "Yakutia" , "Siberia" , "Mongolia" , "Kamchatka" };
    neighbourSectors[allSectors[7]] = sectorNeighbourhood_temp;
    // Sector ID = 8
    sectorNeighbourhood_temp = { "EastSiberia" , "Siberia" , "China" , "Japan" , "Kamchatka" };
    neighbourSectors[allSectors[8]] = sectorNeighbourhood_temp;
    // Sector ID = 9
    sectorNeighbourhood_temp = { "Mongolia" , "Siberia" , "Ural" , "Afganistan" , "India" , "Siam" };
    neighbourSectors[allSectors[9]] = sectorNeighbourhood_temp;
    // Sector ID = 10
    sectorNeighbourhood_temp = { "Indonesia" , "China" , "India" };
    neighbourSectors[allSectors[10]] = sectorNeighbourhood_temp;
    // Sector ID = 11
    sectorNeighbourhood_temp = { "Mongolia", "Kamchatka" };
    neighbourSectors[allSectors[11]] = sectorNeighbourhood_temp;
    // Africa neighbour
    // Sector ID = 12
    sectorNeighbourhood_temp = { "SouthEurope" , "MiddleEast" , "NorthAfrica" , "EastAfrica" };
    neighbourSectors[allSectors[12]] = sectorNeighbourhood_temp;
    // Sector ID = 13
    sectorNeighbourhood_temp = { "Brasil", "Kongo" , "EastAfrica" , "Egypt" , "SouthEurope" , "WestEurope" };
    neighbourSectors[allSectors[13]] = sectorNeighbourhood_temp;
    // Sector ID = 14
    sectorNeighbourhood_temp = { "Egypt" , "NorthAfrica" , "Kongo" , "SouthAfrica" , "Madagascar" , "MiddleEast" };
    neighbourSectors[allSectors[14]] = sectorNeighbourhood_temp;
    // Sector ID = 15
    sectorNeighbourhood_temp = { "SouthAfrica" , "EastAfrica" , "NorthAfrica" };
    neighbourSectors[allSectors[15]] = sectorNeighbourhood_temp;
    // Sector ID = 16
    sectorNeighbourhood_temp = { "Madagascar" , "EastAfrica" , "Kongo" };
    neighbourSectors[allSectors[16]] = sectorNeighbourhood_temp;
    // Sector ID = 17
    sectorNeighbourhood_temp = { "SouthAfrica" , "EastAfrica" };
    neighbourSectors[allSectors[17]] = sectorNeighbourhood_temp;
    // Europe neighbour
    // Sector ID = 18
    sectorNeighbourhood_temp = { "Iceland" , "Scandinavia" , "WestEurope" };
    neighbourSectors[allSectors[18]] = sectorNeighbourhood_temp;
    // Sector ID = 19
    sectorNeighbourhood_temp = { "Greenland" , "GreatBritain" , "Scandinavia" };
    neighbourSectors[allSectors[19]] = sectorNeighbourhood_temp;
    // Sector ID = 20
    sectorNeighbourhood_temp = { "Iceland" , "GreatBritain" , "NorthEurope" , "Ukraine" };
    neighbourSectors[allSectors[20]] = sectorNeighbourhood_temp;
    // Sector ID = 21
    sectorNeighbourhood_temp = { "Scandinavia" , "NorthEurope" , "SouthEurope" , "MiddleEast" , "Afganistan" , "Ural" };
    neighbourSectors[allSectors[21]] = sectorNeighbourhood_temp;
    // Sector ID = 22
    sectorNeighbourhood_temp = { "Scandinavia" , "GreatBritain" , "WestEurope" , "SouthEurope" , "Ukraine" };
    neighbourSectors[allSectors[22]] = sectorNeighbourhood_temp;
    // Sector ID = 23
    sectorNeighbourhood_temp = { "NorthEurope" , "WestEurope" , "NorthAfrica" , "Egypt" , "MiddleEast" , "Ukraine" };
    neighbourSectors[allSectors[23]] = sectorNeighbourhood_temp;
    // Sector ID = 24
    sectorNeighbourhood_temp = { "NorthAfrica" , "SouthEurope" , "NorthEurope" , "GreatBritain" };
    neighbourSectors[allSectors[24]] = sectorNeighbourhood_temp;
    // NorthAmerica neighbour
    // Sector ID = 25
    sectorNeighbourhood_temp = { "Kamchatka" , "Alberta" , "NorthWestArea" };
    neighbourSectors[allSectors[25]] = sectorNeighbourhood_temp;
    // Sector ID = 26
    sectorNeighbourhood_temp = { "Alaska" , "NorthWestArea" , "Ontario" , "WestUS" };
    neighbourSectors[allSectors[26]] = sectorNeighbourhood_temp;
    // Sector ID = 27
    sectorNeighbourhood_temp = { "Alaska" , "Alberta" , "Ontario" , "Greenland" };
    neighbourSectors[allSectors[27]] = sectorNeighbourhood_temp;
    // Sector ID = 28
    sectorNeighbourhood_temp = { "NorthWestArea" , "Ontario" , "Quebec" , "Iceland" };
    neighbourSectors[allSectors[28]] = sectorNeighbourhood_temp;
    // Sector ID = 29
    sectorNeighbourhood_temp = { "NorthWestArea" , "Alberta" , "WestUS" , "EastUS" , "Quebec" , "Greenland" };
    neighbourSectors[allSectors[29]] = sectorNeighbourhood_temp;
    // Sector ID = 30
    sectorNeighbourhood_temp = { "Greenland" , "Ontario" , "EastUS" };
    neighbourSectors[allSectors[30]] = sectorNeighbourhood_temp;
    // Sector ID = 31
    sectorNeighbourhood_temp = { "EastUS" , "Ontario" , "Alberta" , "CentralAmerica" };
    neighbourSectors[allSectors[31]] = sectorNeighbourhood_temp;
    // Sector ID = 32
    sectorNeighbourhood_temp = { "WestUS" , "CentralAmerica" , "Quebec" , "Ontario" };
    neighbourSectors[allSectors[32]] = sectorNeighbourhood_temp;
    // Sector ID = 33
    sectorNeighbourhood_temp = { "WestUS" , "EastUS" , "Venezuela" };
    neighbourSectors[allSectors[33]] = sectorNeighbourhood_temp;
    // Oceania neighbour
    // Sector ID = 34
    sectorNeighbourhood_temp = { "Siam" , "NewGuinea" , "WestAustralia" };
    neighbourSectors[allSectors[34]] = sectorNeighbourhood_temp;
    // Sector ID = 35
    sectorNeighbourhood_temp = { "Indonesia" , "EastAustralia" , "WestAustralia" };
    neighbourSectors[allSectors[35]] = sectorNeighbourhood_temp;
    // Sector ID = 36
    sectorNeighbourhood_temp = { "EastAustralia" , "NewGuinea" , "Indonesia" };
    neighbourSectors[allSectors[36]] = sectorNeighbourhood_temp;
    // Sector ID = 37
    sectorNeighbourhood_temp = { "NewGuinea" , "Indonesia" , "WestAustralia" };
    neighbourSectors[allSectors[37]] = sectorNeighbourhood_temp;
    // SouthAmerica neighbour
    // Sector ID = 38
    sectorNeighbourhood_temp = { "CentralAmerica" , "Peru" , "Brasil" };
    neighbourSectors[allSectors[38]] = sectorNeighbourhood_temp;
    // Sector ID = 39
    sectorNeighbourhood_temp = { "Venezuela" , "Peru" , "Argentina" , "SouthAfrica" };
    neighbourSectors[allSectors[39]] = sectorNeighbourhood_temp;
    // Sector ID = 40
    sectorNeighbourhood_temp = { "Venezuela" , "Argentina" , "Brasil" };
    neighbourSectors[allSectors[40]] = sectorNeighbourhood_temp;
    // Sector ID = 41
    sectorNeighbourhood_temp = { "Peru", "Brasil" };
    neighbourSectors[allSectors[41]] = sectorNeighbourhood_temp;
    // Zrobienie tego, co ma zrobi� Sector
    std::cout << "World generation complete" << std::endl;
}

Sector::Sector(std::vector <std::string> allSectors)
{
    //int vectorSize = allSectors.size();
    std::cout << "Yet to be developed" << std::endl;

}

void Sector::sectorMap_Init(std::string sectorName)
{
    std::string playerName_default = "NULL";                                                                // initialization makes empty sectors, that have to be filled yet
    int numberOfSquadsInSector_default = 0;
    sectorMap[sectorName].first = playerName_default;
    sectorMap[sectorName].second = numberOfSquadsInSector_default;
}

void Sector::sectorMap_playerName_Setter(std::string sectorName, std::string playerName)
{
    sectorMap[sectorName].first = playerName;
}

void Sector::sectorMap_numberOfSquadsInSector_Setter(std::string sectorName, int numberOfSquadsInSector)
{
    sectorMap[sectorName].second = numberOfSquadsInSector;
}

void Sector::sectorMap_bothParameters_Setter(std::string sectorName, std::string playerName, int numberOfSquads)
{
    sectorMap[sectorName].first = playerName;
    sectorMap[sectorName].second = numberOfSquads;
}

void Sector::neighbourSectors_Setter(std::string sectorName, std::vector<std::string> nearbySectors)
{
    neighbourSectors[sectorName] = nearbySectors;
}

std::string Sector::sectorMap_playerName_Getter(std::string sectorName)
{
    return sectorMap[sectorName].first;
}

int Sector::sectorMap_numberOfSquadsInSector_Getter(std::string sectorName)
{
    return sectorMap[sectorName].second;
}

std::pair<std::string, int> Sector::sectorMap_bothArgGetter(std::string sectorName)
{
    std::pair <std::string, int> bothArguments;
    bothArguments.first = sectorMap_playerName_Getter(sectorName);
    bothArguments.second = sectorMap_numberOfSquadsInSector_Getter(sectorName);
    // kt�ry return jest czytelniejszy?
    //return std::pair<std::string, int>(bothArguments);
    return bothArguments;
}


bool Sector::allSectorsAcquired_checker()
{

    int iter = 0;
    for (auto it = sectorMap.begin(); it != sectorMap.end(); it++)
    {
        if (it->second.first == "NULL")
        {
            //std::cout << "FALSE" << std::endl;
            return false;
        }
        else
        {
            if (iter == 41)
            {
                //std::cout << "TRUE" << std::endl;
                return true;
            }
        }
        iter++;
    }
    std::cout << "Exception detected in allSectorsAcquired_checker()!" << std::endl;
    std::cout << "Iter = " << iter << std::endl;
    exit(12);
    //return false; // linijka dodana na potrzeby wyeliminowania ostrze�enia wygenerowanego przez g�upie IDE
}

bool Sector::canAttackSector_checker(std::string attackingSector, std::string defendingSector)
{   //  Checking, if defender != attacker
    if (sectorMap[attackingSector].first != sectorMap[defendingSector].first)
    {   //  Checking, if defending sector is in attacking sector neighbourhood
        if (std::find(neighbourSectors[attackingSector].begin(), neighbourSectors[attackingSector].end(), defendingSector) != neighbourSectors[attackingSector].end())
            return true;
        else
            return false;
    }
    else
        return false;
}


std::vector<std::string> Sector::vectorOfSectorsPlayerPossess(std::string possessingPlayer)
{
    std::vector <std::string> vectorOfSectorsPlayerPossess;
    for (auto it = sectorMap.begin(); it != sectorMap.end(); it++)
        if (it->second.first == possessingPlayer)   
            vectorOfSectorsPlayerPossess.push_back(it->first);

    return vectorOfSectorsPlayerPossess;
}

std::map <int, std::string> Sector::mapOfSectorsPlayerPossess(std::string possessingPlayer)
{
    std::map <int, std::string> mapOfSectorsPlayerPossess;
    for (auto it = sectorMap.begin(); it != sectorMap.end(); it++)
    {
        if (it->second.first == possessingPlayer)   
        {
            for (auto it2 = allSectorsMap.begin(); it2 != allSectorsMap.end(); it2++)
            {
                if (it2->second == it->first)
                {
                    mapOfSectorsPlayerPossess[it2->first] = it->first;
                    break;
                }
            }
        }
    }
    return mapOfSectorsPlayerPossess;
}

std::map<int, std::string> Sector::mapOfNeighbouringSectors(std::string attackingSector)
{
    std::map <int, std::string> mapOfNeighbouringSectors_temp;
    std::vector <std::string> neighbourhood = neighbourSectors[attackingSector];
    for (uint8_t i = 0; i < neighbourhood.size(); i++)
    {
        for (auto it = allSectorsMap.begin(); it != allSectorsMap.end(); it++)
        {
            if (neighbourhood[i] == it->second)
                mapOfNeighbouringSectors_temp[it->first] = it->second;
        }
    }

    return mapOfNeighbouringSectors_temp;
}

int Sector::reinforements(std::string playerNick)
{
    int numberOfReinforcementSquads = defaultNumberOfReinforcementSquads;

    // Checking, if a player is in possession of any regions
    for (uint8_t i = 0; i != allRegions.size(); i++)
    {
        std::string regionPossessingPlayer = regionData[allRegions[i]];
        if (playerNick == regionPossessingPlayer)
            numberOfReinforcementSquads += listOfBonusSquadsForRegionPossession_Getter(allRegions[i]);
    }
    return numberOfReinforcementSquads;
}

void Sector::squadEngagement(std::string attackingSector, std::string attackedSector, int numberOfAttackingSquads)
{
    bool squadEngagement_bool = true;
    bool attackSuccess = false;
    if (numberOfAttackingSquads <= 0)
    {
        std::cout << "You can't attack with less than 1 squad" << std::endl;
        sectorMap[attackingSector].second += numberOfAttackingSquads;
        squadEngagement_bool = false;
    }

    int attackingSquads = numberOfAttackingSquads;
    int defendingSquads = sectorMap[attackedSector].second;
    while (squadEngagement_bool)
    {
        int attackResult = rand() % 6 + 1;
        int defendResult = rand() % 6 + 1;
        if (attackResult > defendResult)
            defendingSquads--;
        else if (attackResult <= defendResult)
            attackingSquads--;

        if (defendingSquads == 0)
        {
            attackSuccess = true;
            sectorMap[attackedSector].first = sectorMap[attackingSector].first;    // setting new owner
            sectorMap[attackedSector].second = attackingSquads;
            squadEngagement_bool = false;
            break;
        }
        else if (attackingSquads == 0)
        {
            attackSuccess = false;
            sectorMap[attackedSector].second = defendingSquads;
            squadEngagement_bool = false;
            break;
        }
    }
    if (attackSuccess)
    {
        std::cout << "Attack is successful!" << std::endl;
        std::cout << "New owner of " << attackedSector << ": " << sectorMap[attackedSector].first
            << ", number of present squads: " << sectorMap[attackedSector].second << std::endl;
    }
    else
    {
        std::cout << "Attack is unsuccessful!" << std::endl;
        std::cout << sectorMap[attackedSector].first << " remains as owner of " << attackedSector
            << " with " << sectorMap[attackedSector].second << " squads present" << std::endl;
    }
    std::cout << "Enter any character to continue" << std::endl;
    std::string temp; std::cin >> temp;
    std::cin.clear(); std::cin.ignore();    // just in case of error
}

void Sector::squadEngagement(std::string attackingSector, std::string attackedSector, int numberOfAttackingSquads, struct PipeHelper* pipeC)
{
    bool squadEngagement_bool = true;
    bool attackSuccess = false;
    std::stringstream *stringStreamTemp;
    stringStreamTemp = pipeC->stringStreamAddress;

    if (numberOfAttackingSquads <= 0)
    {
        *stringStreamTemp << "You can't attack with less than 1 squad" << std::endl;
        sectorMap[attackingSector].second += numberOfAttackingSquads;
        squadEngagement_bool = false;
        pipeComParent(pipeC, operationWRITE);
    }

    int attackingSquads = numberOfAttackingSquads;
    int defendingSquads = sectorMap[attackedSector].second;
    while (squadEngagement_bool)
    {
        int attackResult = rand() % 6 + 1;
        int defendResult = rand() % 6 + 1;
        if (attackResult > defendResult)
            defendingSquads--;
        else if (attackResult <= defendResult)
            attackingSquads--;

        if (defendingSquads == 0)
        {
            attackSuccess = true;
            sectorMap[attackedSector].first = sectorMap[attackingSector].first;    // setting new owner
            sectorMap[attackedSector].second = attackingSquads;
            squadEngagement_bool = false;
            break;
        }
        else if (attackingSquads == 0)
        {
            attackSuccess = false;
            sectorMap[attackedSector].second = defendingSquads;
            squadEngagement_bool = false;
            break;
        }
    }

    if (attackSuccess)
    {
        *stringStreamTemp << "Attack is successful!" << std::endl;
        *stringStreamTemp << "New owner of " << attackedSector << ": " << sectorMap[attackedSector].first
            << ", number of present squads: " << sectorMap[attackedSector].second << std::endl;
    }
    else
    {
        *stringStreamTemp << "Attack is unsuccessful!" << std::endl;
        *stringStreamTemp << sectorMap[attackedSector].first << " remains as owner of " << attackedSector
            << " with " << sectorMap[attackedSector].second << " squads present" << std::endl;
    }
    pipeComParent(pipeC, operationWRITE);
    //*stringStreamTemp << "Enter any character to continue" << std::endl;
    //std::string temp; std::cin >> temp;

}

bool Sector::win()
{
    // takes first nick from the map
    std::string possibleWinner = sectorMap[allSectors[0]].first;

    // checks, if all sectors in map are in one's player possesson (via iterator)
    std::map <int, std::string> mapOfSectorsInPossibleWinnerPossession = mapOfSectorsPlayerPossess(possibleWinner);

    if (mapOfSectorsInPossibleWinnerPossession.size() == sectorMap.size())
    {
        winner = possibleWinner;
        return true;
    }
    else
        return false;
}

int Sector::playerErasure()
{
    int playerID = 0;
    int numberOfErasedPlayers = 0;
    int numberOfPlayers = World::numberOfPlayers_Getter();
    // std::string input;
    for (int i = 0; i < numberOfPlayers; i++)
    {                               // Nie mo�na nazwa� mapy nazw� funkcji -> inaczej jest kolizja nazw, przes�anianie nie dzia�a w ten spos�b
        std::map <int, std::string> mapOfSectorsPlayerPossess_temp = mapOfSectorsPlayerPossess(vectorOfPlayers[i].nick);
        if (mapOfSectorsPlayerPossess_temp.empty())
        {
            std::cout << vectorOfPlayers[i].nick << " has been defeated!" << std::endl;
            // input  << 
            numberOfErasedPlayers++;
            vectorOfPlayers.erase(vectorOfPlayers.begin() + i);
        }
    }
    return numberOfErasedPlayers;
}

int Sector::playerErasure(struct PipeHelper* pipeC)
{
    int playerID = 0;
    int numberOfErasedPlayers = 0;
    int numberOfPlayers = World::numberOfPlayers_Getter();
    std::stringstream *stringStreamTemp;
    stringStreamTemp = pipeC->stringStreamAddress;
    // std::string input;
    for (int i = 0; i < numberOfPlayers; i++)
    {                               // Nie mo�na nazwa� mapy nazw� funkcji -> inaczej jest kolizja nazw, przes�anianie nie dzia�a w ten spos�b
        std::map <int, std::string> mapOfSectorsPlayerPossess_temp = mapOfSectorsPlayerPossess(vectorOfPlayers[i].nick);
        if (mapOfSectorsPlayerPossess_temp.empty())
        {
            *stringStreamTemp << vectorOfPlayers[i].nick << " has been defeated!" << std::endl;
            // input  << 
            numberOfErasedPlayers++;
            vectorOfPlayers.erase(vectorOfPlayers.begin() + i);
        }
    }
    pipeComParent(pipeC, operationWRITE_2ALL);
    return numberOfErasedPlayers;
}

void Sector::regionChecker()
{
    // If player is in possession of all sectors particular region consists of, rework region possession
    std::map <std::string, std::vector <std::string> > regionSectors_temp = regionSectors_Getter(); // -> zwraca map� sektor�w, z kt�rych sk�ada si� region

    for (uint8_t i = 0; i < allRegions.size(); i++)
    {
        std::map <std::string, std::string> mapOfRegion_temp;
        std::vector <std::string> vectorOfSectorsInRegion = regionSectors_temp[allRegions[i]];
        // doda� funkcj� informuj�c� o utracie przez gracza kontroli nad regionem
        regionData[allRegions[i]] = "NULL";

        // Filling map of Region
        for (uint8_t it = 0; it != vectorOfSectorsInRegion.size(); it++)
        {
            mapOfRegion_temp[vectorOfSectorsInRegion[it]] = sectorMap[vectorOfSectorsInRegion[it]].first;
        }

        // Searching in map for possible owner of the Region
        uint8_t iterator = 1;
        std::string possibleOwnerOfTheRegion = sectorMap[vectorOfSectorsInRegion[0]].first;
        for (auto it = mapOfRegion_temp.begin(); it != mapOfRegion_temp.end(); it++)
        {
            if (it->second == possibleOwnerOfTheRegion)
            {
                if (iterator == vectorOfSectorsInRegion.size())
                {
                    regionData[allRegions[i]] = possibleOwnerOfTheRegion;
                    std::cout << possibleOwnerOfTheRegion << " is now the owner of " << allRegions[i] << std::endl;
                }
                else
                    iterator++;
            }
            else
                break;
        }
    }


}

void Sector::regionChecker(struct PipeHelper* pipeC)
{
    // If player is in possession of all sectors particular region consists of, rework region possession
    std::map <std::string, std::vector <std::string> > regionSectors_temp = regionSectors_Getter(); // -> zwraca map� sektor�w, z kt�rych sk�ada si� region
    std::stringstream *stringStreamTemp;
    stringStreamTemp = pipeC->stringStreamAddress;

    for (uint8_t i = 0; i < allRegions.size(); i++)
    {
        std::map <std::string, std::string> mapOfRegion_temp;
        std::vector <std::string> vectorOfSectorsInRegion = regionSectors_temp[allRegions[i]];
        // doda� funkcj� informuj�c� o utracie przez gracza kontroli nad regionem
        regionData[allRegions[i]] = "NULL";

        // Filling map of Region
        for (uint8_t it = 0; it != vectorOfSectorsInRegion.size(); it++)
        {
            mapOfRegion_temp[vectorOfSectorsInRegion[it]] = sectorMap[vectorOfSectorsInRegion[it]].first;
        }

        // Searching in map for possible owner of the Region
        uint8_t iterator = 1;
        std::string possibleOwnerOfTheRegion = sectorMap[vectorOfSectorsInRegion[0]].first;
        for (auto it = mapOfRegion_temp.begin(); it != mapOfRegion_temp.end(); it++)
        {
            if (it->second == possibleOwnerOfTheRegion)
            {
                if (iterator == vectorOfSectorsInRegion.size())
                {
                    regionData[allRegions[i]] = possibleOwnerOfTheRegion;
                    *stringStreamTemp << possibleOwnerOfTheRegion << " is now the owner of " << allRegions[i] << std::endl;
                }
                else
                    iterator++;
            }
            else
                break;
        }
    }
    pipeComParent(pipeC, operationWRITE_2ALL);


}

int mainMenu()
{
    std::cout << "Ryzyko 2077 v 1.0\n";
	std::cout << "PS project game server\n";
	std::cout << "Authors: Michal Bogon\n";
	std::cout << "Coauthors: Igor Kaminski, Krzysztof Reczek\n\n";
    bool inMenu = true;
    int menuOption;

    while (inMenu)
    {
        std::cout << "OPTIONS:" << std::endl;
        std::cout << "New Game - 1" << std::endl;
        std::cout << "Load game - 2 (not developed yet)" << std::endl;
        std::cout << "About - 3" << std::endl;
        std::cout << "Exit - 4" << std::endl;

        bool menuOptionSetting = true;
        while (menuOptionSetting)
        {
            if (std::cin >> menuOption)
            {
                menuOptionSetting = false;
                break;
            }
            else
            {
                std::cout << "Incorrect option, please choose between options 1 - 4" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        if (menuOption == 1 || menuOption == 2 /*|| menuOption == 4*/)
            inMenu = false;
        else if (menuOption == 3)
        {
            std::cout << "Project has been developed by Michal Bogon, EiT student in purpose of programming project realisation. Semester 2020/2021" << std::endl << std::endl;

            std::cout << "Enter any character to continue" << std::endl;
                  // wtf, dlaczego ten cin >> nie dzia�a??
            std::string irrelevant; std::cin >> irrelevant;
            /*
            system("clear");
            menuOption = mainMenu();
            */
        }
        else if (menuOption == 4)
        {
            exit(0);
        }
        else
        {
            std::cout << "Incorrect option, please choose between options 1 - 4";
        }
        system("clear");
    }
    return menuOption;
}

// prototype function to cover nasty while loops and ifs
int choice()
{
    // this function has to return value and handle exceptions
    int choice_out;

    if (std::cin >> choice_out)
    {
        return choice_out;
    }
    else
    {
        // error handling
        std::cin.clear();
        std::cin.ignore();
        return -1;
    }
}

int atoiChecker(char buffer[MAXLINE])
{
    std::string stringTemp;
    int temp = atoi(buffer);

    if (temp == 0)      // If atoi read buffer incorrectly, compensate
    {
        stringTemp = buffer;
        if (stringTemp.find("0") == std::string::npos)
            temp = -1;
    }
    return temp;
}

void write_Buffer2Pipe_WRITE (int writingPipe, char buffer[MAXLINE], std::string *stringTemp)
{
	int stringLength;
	strcpy(buffer, (*stringTemp).c_str());
	if (write(writingPipe, &operationWRITE, sizeof(int))        == -1) { printf("Write pipe error"); }
	stringLength = strlen(buffer);
	if (write(writingPipe, &stringLength, sizeof(int))          == -1) { printf("Write pipe error"); }
	if (write(writingPipe, buffer, stringLength * sizeof(char)) == -1) { printf("Write pipe error"); }
	(*stringTemp).clear(); // juz niepotrzebna
}

void write_Buffer2Pipe_WRITE_2ALL (int writingPipe, char buffer[MAXLINE], std::string *stringTemp)
{
	int stringLength;
	strcpy(buffer, (*stringTemp).c_str());
	if (write(writingPipe, &operationWRITE_2ALL, sizeof(int))   == -1) { printf("Write pipe error"); }
	stringLength = strlen(buffer);
	if (write(writingPipe, &stringLength, sizeof(int))          == -1) { printf("Write pipe error"); }
	if (write(writingPipe, buffer, stringLength * sizeof(char)) == -1) { printf("Write pipe error"); }
	(*stringTemp).clear();  // juz niepotrzebna
}

void write_Buffer2Pipe_READ (int writingPipe, char buffer[MAXLINE], std::string *stringTemp)
{
	int stringLength;
	strcpy(buffer, (*stringTemp).c_str());
	if (write(writingPipe, &operationREAD, sizeof(int))         == -1) { printf("Write pipe error"); }
	stringLength = strlen(buffer);
	if (write(writingPipe, &stringLength, sizeof(int))          == -1) { printf("Write pipe error"); }
	if (write(writingPipe, buffer, stringLength * sizeof(char)) == -1) { printf("Write pipe error"); }
	(*stringTemp).clear(); // juz niepotrzebna
}

void read_Buffer2Pipe (int readingPipe, char buffer[MAXLINE])
{
	int stringLength;
	if (read(readingPipe, &stringLength, 	sizeof(int)) 	    == -1) printf("Error reading buffer length from pipe\n");
    if (read(readingPipe, buffer, stringLength * sizeof(char)) == -1) printf("Error reading buffer from pipe\n");
}

// old, replaced by pipeComParent
void mutliOperationalPipe (int writingPipe, int readingPipe, int operation, char buffer[MAXLINE], std::string *stringTemp)
{
    if (operation == operationWRITE)
        write_Buffer2Pipe_WRITE (writingPipe, buffer, stringTemp);
    else if (operation == operationREAD)
    {
        write_Buffer2Pipe_READ  (writingPipe, buffer, stringTemp);
        read_Buffer2Pipe        (readingPipe, buffer);
    }
    else   
        std::cout << "Something went wrong in multiOperationalPipe\nWrong operation: " << operation << std::endl;
}

void pipeComParent(struct PipeHelper* pipeComStructure, int operation)
{
    std::string             *stringTempAddress;
    std::stringstream       *stringStreamTempAddress;
    int writingPipe         = pipeComStructure->p2cPipe[1];
    int readingPipe         = pipeComStructure->c2pPipe[0];
    stringTempAddress       = pipeComStructure->stringAddress;
    stringStreamTempAddress = pipeComStructure->stringStreamAddress;

    // zamiana stream na string
    *stringTempAddress = stringStreamTempAddress->str();
    // zamiana string na buffer

    if (operation == operationWRITE)
    {
        write_Buffer2Pipe_WRITE (writingPipe, pipeComStructure->buffer, stringTempAddress);

        // buffer flush
        memset(pipeComStructure->buffer, 0, sizeof(pipeComStructure->buffer));
    }

    else if (operation == operationREAD)
    {
        write_Buffer2Pipe_READ  (writingPipe, pipeComStructure->buffer, stringTempAddress);

        // buffer flush
        memset(pipeComStructure->buffer, 0, sizeof(pipeComStructure->buffer));
        read_Buffer2Pipe        (readingPipe, pipeComStructure->buffer);
    }

    else if (operation == operationCliChng)
    {
        if (write(writingPipe, &operationCliChng, sizeof(int))                  == -1) { printf ("Write operation to pipe error\n "); }
        if (write(writingPipe, pipeComStructure->playerID_Address, sizeof(int)) == -1) { printf ("Write client to pipe error\n"); }
    }

    else if (operation == operationWRITE_2ALL)
    {
        write_Buffer2Pipe_WRITE_2ALL (writingPipe, pipeComStructure->buffer, stringTempAddress);

        // buffer flush
        memset(pipeComStructure->buffer, 0, sizeof(pipeComStructure->buffer));
    }

    else if (operation == operationEXIT)
    {
        // ToDo
        if (write(writingPipe, &operationEXIT, sizeof(int)) == -1) { printf ("Write operation to pipe error\n"); }
    }

    else 
        std::cout << "Something went wrong in pipeComParent\nWrong operation: " << operation << std::endl;

    // clearing
    string_Flush (pipeComStructure->stringAddress);
    stringstream_Flush (pipeComStructure->stringStreamAddress);

}

void string_Flush (std::string* stringAddress)
{
    stringAddress->clear();
}

void stringstream_Flush (std::stringstream* stringStreamAddress)
{
    stringStreamAddress->str(std::string());
    stringStreamAddress->clear();
}
