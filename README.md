# About
This is a project that emulates neural learning. The way I designed this project was with 0 external information on these topics (e.g. NN design, ...). This means that I reinvented the wheel for pretty much anything from NN structure design and usage to collision logic. I hoped this workflow would have interesting results.
## Installation
Clone raylib into the libs directory (and create it):
```bash
mkdir src/libs
cd src/libs
git clone --depth 1 https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP
```
(or you can use any build method for raylib)
## Building
Create a build directory for your build files:
```bash
mkdir build
cd build
cmake .. # optional: add flag -DDEBUG_MODE=ON to turn on debug mode
cmake --build .
./Pac
```
