CC = g++
CFLAGS = -I/usr/include/eigen3 -std=c++17 `pkg-config eigen3 --cflags` `root-config --cflags --libs`

algebra.exe: algebra.cpp
	$(CC) $(CFLAGS) algebra.cpp -o algebra.exe

run: algebra.exe
	./algebra.exe

clean:
	rm -f algebra.exe
