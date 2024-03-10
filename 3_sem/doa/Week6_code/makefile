CXX=g++
SOURCES=test_sort.cpp
OBJECTS=${SOURCES:.cpp=.o}
EX=output

all: ${EX} clean

${EX}: ${OBJECTS}
	${CXX} -o $@ $^

%.o: %.cpp
	${CXX} -c -o $@ $^

clean:
	rm -f *.o

clean-all:
	rm -f *.o $(EX)
