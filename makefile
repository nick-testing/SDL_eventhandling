CC= g++
CPP_FLAGS= -pedantic
LINKER_FLAGS= -lSDL2
SRC_DIR= ./src/
OBJ_NAME= $(SRC_DIR)main.o $(SRC_DIR)Game.o

all: game.out

game.out: $(OBJ_NAME)
	$(CC) $(OBJ_NAME) -o game.out $(LINKER_FLAGS)

%.o: $(SRC_DIR)%.cpp
	$(CC) $<  $(CPP_FLAGS) -o $(OBJ_NAME)

clean:
	rm -f *.out $(SRC_DIR)*.o