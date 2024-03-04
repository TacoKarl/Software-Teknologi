CXX = arm-rpizw-g++
EX=output

all: ${EX}

${EX}:hello.o main.o
	${CXX} main.o hello.o -o output

main.o:main.cpp
	${CXX} -c main.cpp

hello.o:hello.cpp
	${CXX} -c hello.cpp

clean:
	rm *.o output

help:
	@echo "Available targets:"
	@echo " all		: Build the executable file (default target)"
	@echo " clean		: Remove all object files and the executable"
	@echo " help		: Display this help message"