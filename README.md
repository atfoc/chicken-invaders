# RG126-chicken-invaders

**WARNING: BEFORE YOU CONTINUE** Code you are about to look may contain ugly and longer block of code
due the lack of time some parts may not be pretty and implemented in the best way.

## Project info
This is a project for my computer graphics course at university of Belgrade (Mathematical Faculty)
It's formed from two parts.
+ Part one: Game Engine

	set of classes that wrap sdl2 and opengl so it is easier to work with 
	this systems to create a game
+ Part two: Game code

	this is the actual game

## Dependencies
+ OpenGL
+ GLU
+ SDL2
+ Devil
+ Assimp
+ GLM

## Installation
	
```shell
git clone https://github.com/MATF-RG17/RG126-chicken-invaders
cd RG126-chicken-invaders
cd src/game
make
#sugested make -j8
./target
```

## How to play
First when you load a game you will see level selector like this:

![Image level selector](https://github.com/atfoc/chicken-invaders/blob/master/screenshots/level_selector.png)
You select levels on right and left arrow and enter level using enter(the key :P)
You will see loading screen(or not if your computer is too fast) wile the models are loading like this:
![Image level loading](https://github.com/atfoc/chicken-invaders/blob/master/screenshots/level_loader.png)
And when the level starts you can move using arrows shoot using space bar:
![Image level](https://github.com/atfoc/chicken-invaders/blob/master/screenshots/level.png)
First level has 1 wave
Second level has 2 waves
Third... well lets see how far you can get
You can use esc button to return to level selector at any point in game

## Future plans

## Todo
+ [ ] clean up the code and fix ugly parts
+ [ ] add nicer comments
+ [ ] add tutorial wiki page for the engine
+ [ ] add const to functions that dont change objects

## Known issues
+ To move player and shoot you have to repetitively press buttons you cant hold them
+ Rendering function was taken from assimp texture opengl example code and it is recursive and it is slow
+ Currently all models have an instance of Assimp loader but they should be copied to custom representation after being	loaded




