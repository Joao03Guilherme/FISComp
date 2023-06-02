CC = g++
CFLAGS = -std=c++17 `root-config --cflags --libs`

projeto2.exe: projeto2.cpp
	$(CC) projeto2.cpp -o projeto2.exe $(CFLAGS)

run: projeto2.exe
	./projeto2.exe

clean:
	rm -f projeto2.exe
