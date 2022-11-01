# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall -pg

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLFER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/
OUTPUT_FOLFER = ./output/

# all sourcers, obs, and header files
MAIN = main
TARGET = poker.out
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

all: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLFER)$(TARGET) $(OBJ)

run:
	./bin/poker.out
	gprof ./bin/poker.out gmon.out > gprof.txt

clean: 
	@rm -rf $(OBJ_FOLDER)* $(BIN_FOLFER)* $(OUTPUT_FOLFER)*
	@rm gmon.out
	@rm memlog.out
	@rm gprof.txt
	clear