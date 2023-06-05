CC = g++
CFLAGS = -std=c++17 `root-config --cflags --libs`

.PHONY: all run clean

all: run clean

run: projeto2.exe
	./projeto2.exe

projeto2.exe: projeto2.cpp
	$(CC) projeto2.cpp -o projeto2.exe $(CFLAGS)

clean:
	rm -f projeto2.exe

cleanpdfs:
	rm -f total_power.pdf histogram.pdf
