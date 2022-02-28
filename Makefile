.PHONY: makefile

all: build/objects/./main.o
	g++ build/objects/./main.o -o beans

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

