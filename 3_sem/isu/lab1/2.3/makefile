EXE=prog
CXX=g++
OBJECT=server.o data.o connection.o main.o

all: ${EXE}

$(EXE): $(OBJECT)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -c -o $@ $^

clean:
	rm *.o ${EXE}

help:
	@echo "Available targets:"
	@echo " all		: Build the executable file (default target)"
	@echo " clean		: Remove all object files and the executable"
	@echo " help		: Display this help message"