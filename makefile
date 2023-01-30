program: main.o
	g++ main.o functionHeader.o -o main

main.o: main.cpp
	g++ -std=c++11 -c main.cpp functionHeader.cpp

clean:
	rm *.o main