CC = g++
EIGEN_INC = `pkg-config eigen3 --cflags`
ROOT_INC = `root-config --cflags`
ROOT_LIBS = `root-config --libs`

SRC = $(wildcard src/*.cpp)

CFLAGS = -std=c++17 

%.exe: main/%.cpp
	@echo "Compiling $<"
	$(CC) $< -o $@ -I SRC $(CFLAGS) $(EIGEN_INC) $(ROOT_INC) $(ROOT_LIBS)

dump:
	@echo $(SRC)
	@echo $(CFLAGS)
	@echo $(EIGEN_INC)
	@echo $(ROOT_INC)
	@echo $(ROOT_LIBS)

