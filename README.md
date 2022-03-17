
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                                     //                                     
    // The player is Yarra, an adventurer who must traverse a one-dimensional array of random events from  //
    // right to left to fight a dragon. Combat is done through the use of a 6 sided die; the player        // 
    // rolls a die and if the number + the weapon modifier total more than the monster's HP,               //
    // they win. Otherwise, the game is over.                                                              // 
    //                                                                                                     //                                    
    // The player rolls a d6 to find out how many spaces they may move. Upon landing,                      //
    // one of three things happen:                                                                         //
    //                player finds a weapon,                                                               //                                    
    //                an enemy,                                                                            //                                    
    //                or nothing.                                                                          //                                    
    //                                                                                                     //                                    
    // From there, the player may dismount and engage the encounter or keep moving.                        //
    // When reaching the dragon, the player must have a minimum                                            //                                    
    // XP or else they lose.                                                                               //                                    
    //                                                                                                     //                                   
    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    
    
Map is a randomized one dimensional array of chars. Each space is assigned either a monster, loot, or nothing. The player navigates by rolling a d6. When a monster is encountered, the player may dismount and engage in combat, rolling another d6 for attack + a weapon modifier. When they pass over a weapon, it is automatically swapped out with the current one if it has a higher attack. When in an empty space, the player may dismount and rest for a small amount of XP. At the end of the array, the final space is the final boss, a dragon. Game interface is color-coded and user friendly, making it more pleasing to look at than white script on a black background.
