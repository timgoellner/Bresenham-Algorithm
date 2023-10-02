all:
	gcc -Isrc/include -Lsrc/lib -o bin/Bresenham src/main.c -lmingw32 -lSDL3