.PHONY: makefile

all: build/objects/./main.o build/objects/.\wm/SDLDisplay.o
	g++ build/objects/./main.o build/objects/.\wm/SDLDisplay.o -lSDL2 -o beans

run: all
	./beans

makefile:
	python build/generate-makefile.py

clean:
	python build/fs_util.py rmdir build/objects
	python build/fs_util.py rmfile beans.exe

build/objects/./main.o: ./main.cpp
	python build/fs_util.py mkdir build/objects/.
	g++ -c ./main.cpp -o build/objects/./main.o

build/objects/.\wm/SDLDisplay.o: .\wm/SDLDisplay.cpp .\wm/SDLDisplay.hpp
	python build/fs_util.py mkdir build/objects/.\wm
	g++ -c .\wm/SDLDisplay.cpp -o build/objects/.\wm/SDLDisplay.o

