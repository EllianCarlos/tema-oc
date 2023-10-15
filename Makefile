DATABASE_DIR=./db
DATABASE_BINARIES_DIR=./db/bin
DATABASE_DOWNLOAD_LIST=$(DATABASE_DIR)/list_file.txt
DATABASE_DOWNLOAD_SCRIPT=$(DATABASE_DIR)/pdb_batch_download.sh

# Name

PROJECT = MDGP

VERSION = 0.1

# source code prefix

PREFIX=.
DIST=dist
SRC_FOLDER=src

# Objects

OBJECTS = main.o

BIN = main

CPP_FLAGS = -march=native -O3 -Wall
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

# ./src/data/converter/LineToDistanceFrequency.cpp

main.o: ./src/data/Distance.cpp ./src/data/DistanceFrequency.cpp ./src/data/converter/DistanceFrequencyToDistance.cpp ./src/parser/FileParser.cpp ./src/main.cpp
	g++ -march=native -O3 -I ./src/headers -Wall  $^ -o $@

simple-main: ./src/data/Distance.cpp ./src/simple-main.cpp
	g++ -march=native -O3 -I ./src/headers/ -Wall $^ -o simple-main.o 

clean:
	rm -f $(OBJECTS) $(BIN) 