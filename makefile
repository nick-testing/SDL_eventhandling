CC= g++
CPPFLAGS= -pedantic
SDLFLAGS= -lSDL2
SRC= ./src/
OBJ= $(SRC)main.o $(SRC)Game.o

all: game.out

game.out: $(OBJ)
	$(CC) $(OBJ) -o game.out $(SDLFLAGS)

%.o: $(SRC)%.cpp
	$(CC) $<  $(CPPFLAGS) -o $(OBJ)

clean:
	rm -f *.out $(SRC)*.o