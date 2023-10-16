# From the PDB
DATABASE_DIR=./db
DATABASE_BINARIES_DIR=./db/bin
DATABASE_DOWNLOAD_LIST=$(DATABASE_DIR)/list_file.txt
DATABASE_DOWNLOAD_SCRIPT=$(DATABASE_DIR)/pdb_batch_download.sh

# Name
PROJECT = MDGP

VERSION = 0.1

# source code folder
SRC_FOLDER=./src

# Objects

OBJECTS = main.o
DATA_FOLDER = $(SRC_FOLDER)/data
CONVERTER_FOLDER = $(DATA_FOLDER)/converter
DATA_FILES = $(DATA_FOLDER)/Distance.cpp $(DATA_FOLDER)/DistanceFrequency.cpp $(CONVERTER_FOLDER)/DistanceFrequencyToDistance.cpp $(CONVERTER_FOLDER)/LineToDistanceFrequency.cpp $(DATA_FOLDER)/Point.cpp 
PARSER_FILES = $(SRC_FOLDER)/parser/FileParser.cpp 

BIN = main

CPP_FLAGS = -march=native -O3 -Wall -lm
C_FLAGS = -I.
LD_FLAGS =
CC = g++ # gcc will not give access to c++ libraries
MAKE = make

# Other files to be distributed

EXTRADIST = 

# PHONY

.PHONY: clean download-db unpack-download

download-db:
	sh $(DATABASE_DOWNLOAD_SCRIPT) -f $(DATABASE_DOWNLOAD_LIST) -p -o $(DATABASE_BINARIES_DIR)

unpack-download: 
	gzip -d ./$(DATABASE_BINARIES_DIR)/*.gz	

all:
	@echo "TODO"

main: main.o
	./main.o

main-debug:$(DATA_FILES) $(PARSER_FILES) $(SRC_FOLDER)/main.cpp
	g++ $(CPP_FLAGS) -I ./src/headers -g -fdiagnostics-color=always $^ -o $@

main.o: $(DATA_FILES) $(PARSER_FILES) $(SRC_FOLDER)/main.cpp
	g++ $(CPP_FLAGS) -I ./src/headers  $^ -o $@

simple-main: ./src/data/Distance.cpp ./src/simple-main.cpp
	@echo $^
	g++ -march=native -O3 -I ./src/headers/ -Wall $^ -o simple-main.o 

clean:
	rm -f $(OBJECTS) $(BIN) 