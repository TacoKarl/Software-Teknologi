CXX = g++

output:hello.o main.o
	g++ main.o hello.o -o output

main.o:main.cpp
	g++ -c main.cpp

hello.o:hello.cpp
	g++ -c hello.cpp

clean:
	rm *.o output