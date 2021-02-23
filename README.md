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
*tested with version 2.5 <br/>
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
