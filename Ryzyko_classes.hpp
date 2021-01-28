#pragma once
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>


class World {
    /* This class checks if all regions are in ones player possession
    *  If so -> end + info, who won (win function)
    * This class also has list of Bonuses for each region possession
    */
    private:
        std::map <std::string, int> listOfBonusSquadsForRegionPossession;
        int numberOfPlayers;

        /*if all sectors are in ones player possession -> end + info, who won (function)
         *
         */
    public:

        // Constructors
        World();
        World(std::map <std::string, int> WorldMapInput);                            // WorldMapInput [ VectorOfRegions ] = ListOfBonusSquadsForRegionPossession

        struct Player {
            std::string nick = "NULL";
            bool implemented = false;
            std::vector <std::string> possessingSectors;
            //int reinforements();
        };

        std::vector <struct Player> vectorOfPlayers;

        // Accessors (World Generation)
        void numberOfPlayers_Setter();
        void listOfBonusSquadsForRegionPossession_Setter(std::string NameOfTheRegion, int NumberOfBonusSquads);

        // Getters
        int numberOfPlayers_Getter();
        int listOfBonusSquadsForRegionPossession_Getter(std::string region) { return listOfBonusSquadsForRegionPossession[region]; }

        // Functions

};

class Region : public World
{ /* Asia, Africa, Europe,
   * This class has map of sectors and list of players possessing certain regions
   *
   */

    private:
        //std::map <std::string, char[NICKMAXLENGTH]> region_map;               // map of regions and players, who possess certain regions 
        // std::map <std::string, std::string> regionData;                         // pair of region and player, who possess particular region
        std::map <std::string, std::vector <std::string> > regionSectors;       // map of sectors particular region consists of

    public:

        // Constructors
        //Region (std::map <std::string, char[NICKMAXLENGTH]> region_map_input);
        Region();
        Region(std::string allRegions,                                          // putting regions and vectors of sectors particular region consists of
            std::vector <std::string> asiaSectors, std::vector <std::string> africaSectors,
            std::vector <std::string> europeSectors, std::vector <std::string> northAmericaSectors,
            std::vector <std::string> oceaniaSectors, std::vector <std::string> southAmericaSectors);

        // Setters (once constructor was used, not neccessary)
        void setRegion(std::pair <std::string, std::string> region_map_change);
        void regionAdditionalSquads(std::string regionName);

        // Getters
        //std::map <std::string, std::string> get_region() const { return regionData; }
        std::vector <std::string> regionSectors_Getter(std::string key) { return regionSectors[key]; };
        std::map <std::string, std::vector <std::string> > regionSectors_Getter() { return regionSectors; };

        // Functions
        // Both below replaced with reinforements() function
        bool possession(std::map <std::string, std::string> regionData); // sprawdza, czy jeden gracz ma w posiadaniu wszystkie sektory danego regionu
        int additionalSquads(std::string regionName);                                                         // if possession == true, then Additional Squads are acquired

        // Variables
        //std::map <int, std::string> allSectors;
        std::vector <std::string> allSectors;
        std::vector <std::string> allRegions;
        std::map <int, std::string> allSectorsMap;
        std::map <std::string, std::string> regionData;                         // pair of region and player, who possess particular region
};

class Sector : public Region
{
    private:
        //std::map< std::string, std::vector<std::string> > sectorMap;
        std::map< std::string, std::pair<std::string, int> > sectorMap;                     // Map with sector (key), which allows to check, which player is possessing region and how many squads are present
        std::map< std::string, std::vector <std::string> > neighbourSectors;                // Map with sector (key) and vector of nearbySectors

    public:

        // Constructors
        Sector();
        Sector(std::vector <std::string> allSectors);

        // Setters
        void sectorMap_Init(std::string sectorName);                                        // Sector initialization
        void sectorMap_playerName_Setter(std::string sectorName, std::string playerName);   // Changes player possessing certain region
        void sectorMap_numberOfSquadsInSector_Setter(std::string sectorName, int numberOfSquadsInSector);                           // Changes number of squads of player possessing certain region
        void sectorMap_bothParameters_Setter(std::string sectorName, std::string playerName, int numberOfSquads);
        void neighbourSectors_Setter(std::string sectorName, std::vector <std::string> nearbySectors);

        // Getter
        std::string sectorMap_playerName_Getter(std::string sectorName);
        int sectorMap_numberOfSquadsInSector_Getter(std::string sectorName);
        std::pair <std::string, int> sectorMap_bothArgGetter(std::string sectorName);

        // Functions
        bool allSectorsAcquired_checker();
        bool canAttackSector_checker(std::string attackingSector, std::string defendingSector);     // if attackingSector_Owner != defendingSector_Owner && defendingSector is in attackingSector_Neighbourhood => true
        bool win();                                                                                 // checks, if one player is in possession in all regions
        std::vector <std::string> vectorOfSectorsPlayerPossess(std::string possessingPlayer);
        std::map <int, std::string> mapOfSectorsPlayerPossess(std::string possessingPlayer);
        std::map <int, std::string> mapOfNeighbouringSectors(std::string attackingSector);
        int reinforements(std::string playerNick);
        void squadEngagement(std::string attackingSector, std::string attackedSector, int numberOfAttackingSquads);
        int playerErasure();                                                                       // checks if player has been defeated
        void regionChecker();                                                                       // checks, if player is in possession of a whole region

        // Variables
        int defaultNumberOfReinforcementSquads = 3;
        std::string winner;
};