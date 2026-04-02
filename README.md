# Gladiator-Fighting-Game
### By Gabe Lattanzi
---

*This project was made entirely in C++ and _should_ run on both Windows and Mac.

#### Project Summary
Originally built as a programming class project, this is a small, terminal-based fighting game that includes custom characters, weapons, and a parry system. 

Player and Enemy stats such as names, health, and weapon statistics, can be modified via the "player_config.txt" and "enemy_config.txt" files, respectively.

Weapons are created/customized within these files, and have a damage range which will be randomly rolled in game.

The parry system functions by causing a fighter who is within one blow of damage from their opponent to become "fatigued". This debuff creates a chance that said fighter's attacks will miss, dealing zero damage and causing their opponent to immediately riposte, winning the game. This chance to miss an attack grows stronger as their health dwindles in-game.

As for healing, the player has a limited supply of healing potions, which can be consumed to retrieve lost health, with the added cost of losing their turn. This is good if you're trying to cause a fatigued enemy to miss their attack, or if you can simply out-heal the damage they can produce

#### Additional Info

This project was made as an open-ended project for an advanced programming course. It lacks many of the features I wish it could have, so I hope to add to this and use it as a learning tool throughout the future, pushing into graphics/a more structured and advanced game.

#### Possible Future Content
- Graphical Interface
- Teams/Squads of fighters on each side, allowing for local multiplayer/singleplayer with multiple characters
- Progression, such as levels to get through, pre-made characters you can add to your ranks
- Shops for weapon upgrades, better potions, or support/utility items
