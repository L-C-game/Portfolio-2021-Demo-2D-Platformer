# 2D Platformer Demo "Zool in Demoland"


![CoverPicture](https://user-images.githubusercontent.com/67602355/141102007-1d6ac265-a6bd-4fdb-8fbb-2afcb49dd31f.png)



## Introduction
This platformer demo was created as part of the Sumo Digital Academy internship. 

"Zool in DemoLand" is a 2D platformer, the game consists of a title state, play state, win state and gameover state.

### Aim of the project
- To create a simple 2D game that implements the State Design Pattern as the Player's Finite State Machine (FSM).

## Technologies
Language: C++

Framework: PlayBuffer Ver. 1.1.21.07.02

IDE: Visual Studio 2019

Source Control: Initially Visual Studio, later SourceTree

## Launch
To launch the project; download the Repository code, open and build the solution in Visual Studio.

## Functionality

The game makes use of Object Oriented design principles, including; classes and inheritance,
the state design pattern, and the singleton design pattern.

In order to represent a variety of game objects with vastly differing functionality a class based system was devised.

Each of the object's within the game inherit from the base Game Object class.

This class contains variables and methods that are relevant to all Game Objects such as position, half size (half the full object dimensions),
and collision checking and resolution.

The Game Object class also stores virtual methods for drawing and updating the object's, these are overridden in the relevant child classes.

### State Pattern

The State Pattern was used to create the Player's FSM. 
This pattern uses Object Oriented principles, 
instead of using an enum and switch statements, 
and each of the separate states are represented as a class. 

#### Meyer's singleton

Each of the state classes were created as singleton’s, specifically Meyer’s singleton. This was to ensure that there was only a single instance of each state at a time. 
The singleton pattern was used to ensure that only a single instance of each state existed at once, as the player should only be in a single state at a time, this helps control access to the states. 
Singleton’s also provide global access to the single instance, however unlike static classes you are able to perform creation logic.

### Data Oriented design

Data oriented design principles were followed when implementing the objects which have multiples,
this made data entry more efficient, as each of the objects could be set up with their relevant data in an array,
the array could then be looped through, calling the spawn method for the relevant object for the number of objects.

## Sources

### State Design Pattern
https://gameprogrammingpatterns.com/state.html

### Meyer's Singleton
http://laristra.github.io/flecsi/src/developer-guide/patterns/meyers_singleton.html

#### Understanding the implementation of the State Pattern in conjunction with Meyer's singleton
https://www.aleksandrhovhannisyan.com/blog/finite-state-machine-fsm-tutorial-implementing-an-fsm-in-c/

### AABB Collision
https://gamedevelopment.tutsplus.com/tutorials/basic-2d-platformer-physics-part-1--cms-25799

### Camera Setup
http://lazyfoo.net/SDL_tutorials/lesson21/index.php

### PlayBuffer
Creative Commons Attribution-No Derivatives 4.0 International Public License

Sumo Digital Academy 

### Music 
CC0 License 

https://opengameart.org/users/celestialghost8

### Sound effects
Created using Bfxr

https://www.bfxr.net/

_________________________________________________________________________________________________________
PlayBuffer is the intellectual property of Sumo Digital Academy and is used under the,

Creative Commons Attribution-No Derivatives 4.0 International Public License.

Zool Redimensioned © 2021 Urbanscan Ltd. All rights reserved. 

Zool Redimensioned was developed by Sumo Digital Academy under licence from Ian Stewart’s Urbanscan Ltd.

Published and distributed by Secret Mode Limited. 

Sumo Digital Academy and Secret Mode Limited are part of Sumo Group plc.
_________________________________________________________________________________________________________



