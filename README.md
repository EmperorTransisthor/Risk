# Risk v 0.1
Basic functionality:
*    Game initialization (not entirely finished, it will be updated soon, planning to add that in v 0.3)
*    Beggining Phase - player place 3 reinforcing squads in target sector he or she controls (gonna rework it, so player can place squads in different positions, that was made just to make input simpler, will be changed in v 0.3)
*    Combat Phase - player can attack other players and claim sectors (not entirely finished, need to add additional dices, so chances of winning for both defender and attacker aren't the same)
*    Rearangement Phase - player can move his units from one sector to another. Now very basic functionality, but soon I will add A* algorithm to find sectors, where player actually can place his units (planning to add that in v 0.3)

# Risk v 0.2 - in cooperation with IngvarusK
Added Multiplayer version (separate from singleplayer version):
* Main program (backend)
* Server TCP (mediates in communication between main program and clients)
* Server UDP multicast (allows clients to find available games)
* Client UDP (finding games) mixed with TCP (actual game)

Communication between servers and main program is carried out using pipes.
Minor changes in main program, like randomized starting player

# (in plans) Risk v 0.3
* *Finished initialization, allowing to set more units on the map for players, and customized game start*
* *Allowing players to put all squads at once or separately, but need to rethink, how to do it well*
* *Expansion of Combat Phase, so chances of attack aren't the same for all numbers of attacking/defending squads + possibility to disengage*
* *Implementation of A-star algorithm to check, if moving from sector A to B is possible*
* *Improved RNG*
* *Integration of singleplayer and multiplayer versions*

# (long-temp plans) Risk v 1.0
* *Added GUI*
* Tidy up the code
