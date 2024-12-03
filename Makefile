all: clean real 
real: main.cpp 
	clang++ -std=c++17 -Wall -o real main.cpp -lsqlite3
clean:
	rm -f real *.o