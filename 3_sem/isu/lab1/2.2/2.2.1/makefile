CXX = g++
EX=output
SOURCES=main.cpp part1.cpp part2.cpp
OBJECT=${SOURCES:.cpp=.o}

all: ${EX}

${EX}: ${OBJECT}
	${CXX} -o $@ $^

%.o: %.cpp
	${CXX} -c -o $@ $^ 

clean:
	rm *.o ${EX}

help:
	@echo "Available targets:"
	@echo " all		: Build the executable file (default target)"
	@echo " clean		: Remove all object files and the executable"
	@echo " help		: Display this help message"