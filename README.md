# Gomoku AI

Gomoku boardgame where you can play against an AI.
The AI is based on the MinMax algorithm optimized with alpha-beta pruning and multithreading.

<p align="center">
  <img src="https://github.com/mdugot/Gomoku-AI/blob/master/gomoku.gif" />
</p>


## Requirements

 * ### C++11 Compiler
Source code is written in C++11.

 * ### CMake
*tested with version 3.19* <br/>
[CMake](https://cmake.org/) is used to make the library.

 * ### SFML
*tested with version 2.5* <br/>
[SFML](https://www.sfml-dev.org/) is used for the graphics and audio.


## Installation

Install the requirements, clone the repository move at the root of the repository and install the module with `./build.sh`:

```
$> git clone https://github.com/mdugot/Gomoku-AI.git
$> cd Gomoku-AI
$> ./build.sh
```

It should have created the binary `gomoku`, run it to start the game.

```
$> ./gomoku
```

## Rules

Gomoku is a strategy board game raditionally played on a Go board with stones of two different colors.
Two players take turns placing their stones on an intersection of the board.
The goal is to align 5 or more of their stones. </br>
This version of Gomoku follows the 3 following rules :
 * *Capture* : A player can remove a pair of his opponent stones from the board by flanking them with his own stones. If a player manage to capture ten of his opponent's stones, he wins the game.
 * *Game-ending capture* : A player that manages to align five stones only wins if the opponent can not break this alignment by capturing a pair of if he has already lost four pairs, if the opponent can not capture one more.
 * *No double-threes* : It is forbiddent to play a move that introduce two free-three alignments, which would guarantee a win by alignment. A free three is an alignement of three stones that, if not immediately blocked, allows for an indefendable alignment of four stones (an alignement of four stones with two unobstructed extremities). Double-three can still be introduced by capturing a pair.

Additionaly, a special opening rule can be selected to make the game more fair between the first and the second player :
 * *classique* : No special opening rule
 * *pro* : The starting player (black) puts the first stone to the middle intersection of the board, this move is compulsory. The second player can put the second move anywhere on the board. Now it's black's turn and the third move has to be outside a 5x5 square from the centre of the board.
 * *long pro* : Same than the *pro* opening rule but with a square of 7x7.
 * *swap* : The starting player puts the first three stones anywhere on the board (two black stones and a white one). The second player can decide whether he wants to stay at white and put a fourth stone or he can swap and control the black stones.


