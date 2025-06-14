# Setting up
Clone raylib into the libs directory (and create it):
```bash
mkdir src/libs
cd src/libs
git clone --depth 1 https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP
```
(or you can use any build method for raylib)
Create a build directory for your build files:
```bash
mkdir build
cd build
cmake .. # optional: add flag -DDEBUG_MODE=ON to turn on debug mode
cmake --build .
./Pac
```

