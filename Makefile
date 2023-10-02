all:
	gcc -Isrc/include -Lsrc/lib -o bin/main src/main.c -lmingw32 -lSDL3