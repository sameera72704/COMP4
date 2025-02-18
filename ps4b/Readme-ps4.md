# PS4: Sokoban

## Contact
Name: Sameera Sakinala  
Section: 202    
Time to Complete: 4~5 hours 


## Description
Explain what the project does.

This project implements a Sokoban game using C++ and SFML. Sokoban is a puzzle game where the player pushes crates to designated locations in a warehouse.
Given the resources from kenny folder we have to create the game. It takes a skill in UI designing for this part of the project and also right structure to further pass it down to the ps4b, where we actually implement the player movement and logic.
 The Sokoban class has a movePlayer method that handles the player movement. It
must take a single Direction enumeration constant as a parameter, chosen from the
set Up, Left, Down, Right.

### Features
Describe what your major decisions were and why you did things that way.

#### Part a

I implemented the basic structure of the Sokoban game, including:
-> Loading and displaying the game level from a file
-> Rendering the game board using SFML sprites
-> Implementing player movement and game state management

#### Part b
 The player can use the WASD and arrow keys to move.
 The Sokoban class has a movePlayer method that handles the player movement. It
must take a single Direction enumeration constant as a parameter, chosen from the
set Up, Left, Down, Right.
 The Sokoban class has a const isWon() method that determines if the player has won
the game.
 Walls block movement.
 Boxes can be pushed by the player if there is an open space to be moved into, otherwise
they block movement. The player can push only one box at a time.
 The player is trying to push a box into each storage area. When the player pushes a
box into each storage area, the game announces that they win.
 Pressing `R' will reset the level to its original state.

### Memory
Describe how you decided to store the level data including whether you used smart pointers.

I decided to store the level data using a 2D vector of characters (std::vector<std::vector<char>>). This approach allows for easy manipulation of the game grid and efficient access to individual tiles. I didn't use smart pointers for this implementation as the standard vector container manages memory allocation and deallocation automatically.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

    I used lambda expressions in the following contexts:
    In the loadTextures() function to iterate over texture paths and load them into the game:
        ```cpp
            std::vector<std::pair<char, std::string>> texturePaths = {
                {'#', "block_06.png"},
                {'A', "crate_03.png"},
                // ...
            };
            for (const auto& [key, path] : texturePaths) {
                // Lambda used here to load textures
            }
    For loading player textures:
        ```cpp
            std::vector<std::pair<Direction, std::string>> playerTextures = {
                            {Direction::Up, "player_20.png"},
                            {Direction::Down, "player_05.png"},
                            // ...
                        };
            for (const auto& [dir, path] : playerTextures) {
                // Lambda used here to load player textures
            }
            
    
    

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

my testcases are issues i am unable to solve them . 

for now :  Test Failed: 3 != 0 : ALSA lib confmisc.c:855:(parse_card) cannot find card '0'
level5 @ {5,1}: RRRRUUUULUR
ALSA lib confmisc.c:855:(parse_card) cannot find card '0'
ALSA lib conf.c:5178:(_snd_config_evaluate) function snd_func_card_inum returned error: No such file or directory
ALSA lib confmisc.c:422:(snd_func_concat) error evaluating strings
ALSA lib conf.c:5178:(_snd_config_evaluate) function snd_func_concat returned error: No such file or directory
ALSA lib confmisc.c:1334:(snd_func_refer) error evaluating name
ALSA lib conf.c:5178:(_snd_config_evaluate) function snd_func_refer returned error: No such file or directory
ALSA lib conf.c:5701:(snd_config_expand) Evaluate error: No such file or directory
ALSA lib pcm.c:2664:(snd_pcm_open_noupdate) Unknown PCM default
AL lib: (EE) ALCplaybackAlsa_open: Could not open playback device 'default': No such file or directory
Failed to open the audio device
An internal OpenAL call failed in SoundBuffer.cpp(46).
Expression:

### Extra Credit
Anything special you did.  This is required to earn bonus points.

1. Elapsed Time Display: I added a timer using sf::Clock in main.cpp to track the elapsed time since the start of the game.
2. The elapsed time is calculated each frame, converted to minutes and seconds, and displayed in MM:SS format in the top-left corner of the screen.
3. I used sf::Text and sf::Font (arial.ttf) to render the time on the screen, with arial.ttf loaded as the font.
4. undo ( button : Z) and redo ( button : Y) system to roll back the player's previous moves
5. Plays victory sound

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

SFML documentation for guidance on window management and sprite rendering
C++ reference for standard library functions and containers
Course materials and lectures for general game development concepts
Kenney Sokoban Pack (CC0) for game assets: https://kenney.nl/assets/sokoban
victory.wav : https://mixkit.co
move.wav : https://mixkit.co
