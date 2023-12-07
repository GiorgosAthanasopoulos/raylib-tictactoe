# Raylib TicTacToe

A simple implementation of tictactoe in raylib.

# REQUIREMENTS - Linux/Windows

- Git:
  - Windows: ```winget install git.git```
  - Linux(ubuntu-based): ```sudo apt install git```

# USAGE - LINUX

- ```git clone https://github.com/GiorgosAthanasopoulos/raylib-tictactoe```
- ```cd raylib-tictactoe```
- ```chmod +x bootstrap.sh```
- ```./bootstrap.sh```

# USAGE - Windows (Just use linux, and make your life ez...Anyway here goes...)

- Lets call the directory that we will use to clone the repositories in ```$PROJECTS```.
- ```cd $PROJECTS```
- Start by cloning [raylib-tictactoe](https://github.com/GiorgosAthanasopoulos/raylib-tictactoe) (the actual game): ```git clone https://github.com/giorgosathanasopoulos/raylib-tictactoe```
- We need a compiler - lets use [W64Devkit](https://github.com/skeeto/w64devkit/):
  - Download the w64devkit zip from the [W64Devkit Releases](https://github.com/skeeto/w64devkit/releases) page.
  - Extract the folder in $PROJECTS.
  - So far the $PROJECTS directory should contain: ```raylib-tictactoe``` and ```w64devkit``` sub-directories.
- Finally we need the raylib library. To make everything easy we will use a raylib game template that comes with makefiles out of the box (and that will automatically download raylib):
  - ```git clone https://github.com/raylib-extras/game-premake```
- That's all for the dependencies. Our ```$PROJECTS``` directory should contain ```raylib-tictactoe```, ```w64devkit``` and ```game-premake``` sub-directories.
Lets configure and build/run our project:
-  Run the executable ```$PROJECTS/w64devkit/w64devkit/w64devkit.exe```
In the new terminal run:
- ```cd $PROJECTS/game-premake```
- ```premake-mingw.bat``` (This will download raylib for us - along with creating a makefile for our project).
Now lets copy raylib-tictactoe in the game-premake src directory:
- ```rm ./game/src/*```
- ```cp ../raylib-tictactoe/src/* ./game/src/```
- ```cp ../raylib-tictactoe/_build/game-premake.make ./_build/```
- ```make```(You should see the raylib library being compiled),
- ```_bin/Debug/game-premake.exe```
