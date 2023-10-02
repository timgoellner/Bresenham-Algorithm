# Bresenham-Algorithm
The Rasterization of a line with the the Bresenham Algorithm

## Installation
1. Clone the repository
2. (Optional) Build the project yourself with `make` (`gcc -Isrc/include -Lsrc/lib -o bin/Bresenham src/main.c -lmingw32 -lSDL3`)
3. Start `bin/Bresenham.exe`

## Usage
- You can alter some settings in `src/constants.h` if you rebuild the project
- Draw the line with setting two points using `LMB`
- Clear the screen and reset the points with `RMB`
- Exit with `ESC`, `q` or `Alt+F4`
