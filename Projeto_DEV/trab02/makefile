CC = g++
CFLAGS = -std=c++17 -Wall

ROOT_INC = `root-config --cflags`
ROOT_LIBS = `root-config --libs`
EIGEN_INC = `pkg-config --cflags eigen3`
SRC_DIR = src
MAIN_DIR = main

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
HEADER_FILES = $(wildcard $(SRC_DIR)/*.hpp)
MAIN_SRC = $(MAIN_DIR)/rMapa_B.cpp
EXECUTABLE = project.exe

all: $(EXECUTABLE) run clean 

$(EXECUTABLE): $(SRC_FILES) $(HEADER_FILES) $(MAIN_SRC)
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(MAIN_SRC) $(SRC_FILES) $(EIGEN_INC) $(ROOT_INC) $(ROOT_LIBS) -o $(EXECUTABLE)

run:
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)