CXX=arm-rpizw-g++
EX=hello
LDFLAGS=-lpthread


all: ${EX}

${EX}:hello.o 
	${CXX} hello.o -o hello ${LDFLAGS}

hello.o:hello.cpp
	${CXX} -c hello.cpp

clean:
	rm *.o ${EX}

help:
	@echo "Available targets:"
	@echo " all             : Build the executable file (default target)"
	@echo " clean           : Remove all object files and the executable"
	@echo " help            : Display this help message"
