# LINUX 	g++ -Wall -Wextra -std=c++17 ./src/*.cpp -I ./include -o ./bin/main.o -fopenmp
# WINDOWS 	g++ -Wall -Wextra -std=c++17 ./src/*.cpp -I ./include -o ./bin/main.exe -fopenmp
CC		:= g++
C_FLAGS := -std=c++17 -Wall -Wextra

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main.o
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*
	$(CC) $(C_FLAGS) -I$(INCLUDE) -L$(LIB) $^ -o $@ $(LIBRARIES) -fopenmp
