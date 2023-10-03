# Bresenham-Algorithm
The Rasterization of lines, circles, triangles and squares with the the Bresenham Algorithm

## Installation
1. Clone the repository
2. (Optional and requiers SDL to be installed and correctly linked) Build the project yourself with `make`
   (`gcc -Isrc/include -Lsrc/lib -o bin/Bresenham src/main.c -lmingw32 -lSDL3`)
3. Start `bin/Bresenham.exe` (problems may occur when not using powershell to start)

## Usage
Note: You can alter some settings in `src/constants.h` if you rebuild the project

- Switch between line, circle, triangle and square drawing mode with `SPACE` or `ENTER` 
- Draw shapes with setting two or three points using `LMB`
- Clear the screen and reset the points with `RMB`
- Exit with `ESC`, `q` or `Alt+F4`
