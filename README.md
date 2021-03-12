# Risk
**Introduction** <br />
This is final project in the Object Oriented Programming and Network Programming subjects. I was trying to make something, which will take me from the very beggining to a new level of C++. Final effect is a bundle of ideas, me testing out different approaches, starting from very simple, to quite complex structures, what ended up working but a mess. Now, I'd build it differently (these classes are just bad), but I treat it more like a battleground for my ideas, sorry for that. I plan to rework main program a bit, so it will be more readable and clear. **Currently, game has singleplayer (0.1) and multiplayer (0.2) versions separately, I want to merge them together in v0.3.**<br />
In classic Risk, main goal is to beat all players and be the only lasting player on the board. <br />
Note, that Risk v0.1 is designed for Windows (can be runned on Linux, although the screen won't be refreshed, depending on the phase), but Risk v0.2 is designed specificaly for Linux. 

**Game Structure** <br />
The game is separated to 2 phases (gonna rework it, read CHANGELOG v0.4 to learn more): Initialization Phase and Main Phase. 

**Initialization Phase** <br />
In initialization Phase, players place troops on the map.

**Main Phase** (main loop) <br />
The actual turn system. Structure: <br />
* Reinforcements placement phase (aka Beggining phase) - here player can place his reinforcements, he gets each turn. Base value is 3, for each additional possessing region, number of acquired reinforcements increases by the number of bonus squads for region possession (regions possessing at the beggining of his turn). *For example, if player possesses Europe and his turn just begun, he will get 3 + 5 = 8 squads to place on the map*
* Combat phase - here players fight for dominance. Player can attack other players and claim sectors. *Dice system will be improved in 0.3*
* Rearangement Phase - player can move his units from one sector to another. Now very basic functionality, but soon I will add A* algorithm to find sectors, where player actually can place his units *(planning to add that in v 0.3)*

Every time, player X finishes his turn, program checks, if any player was beaten by player X. If so, program announces this information and removes player from the game.

# Risk server - in cooperation with IngvarusK
Version 0.2 added server and client to Risk. It consists of:
* Main program (backend)
* Server TCP (mediates in communication between main program and clients)
* Server UDP multicast (allows clients to find available games)
* Client UDP (finding games) mixed with TCP (actual game)

Communication between servers and main program is carried out using pipes. Minor changes in main program, like randomized starting player
