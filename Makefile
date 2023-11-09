.PHONY: clean

CC=g++

LIBS=-lSDL2main -lSDL2 -lm

CFLAGS=-g
OFLAGS=-I src

SRC=$(shell find src -type f -name '*.cpp')
OBJ=$(patsubst %.cpp, %.o, $(SRC))

all: game
	./make/bin/game

game: $(OBJ)
	$(CC) $(OFLAGS) -o make/bin/$@ make/build/*.o $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $^
	mv $@ make/build/

exec:
	./make/bin/game

clean:
	rm -f make/build/*.o make/bin/game
