CXX = arm-rpizw-g++
EX=output

${EX}:hello.o main.o
	${CXX} main.o hello.o -o output

main.o:main.cpp
	${CXX} -c main.cpp

hello.o:hello.cpp
	${CXX} -c hello.cpp

clean:
	rm *.o output