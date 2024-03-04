SOURCES=main.cpp data.cpp server.cpp connection.cpp
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)
EXE=prog
CXX=g++
CXXFLAGS=-I.

$(EXE): $(DEPS) $(OBJECTS) # << Check the $(DEPS) new dependency
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)
# Rule that describes how a .d (dependency) file is created from a .cpp file
# Similar to the assigment that you just completed %.cpp -> %.o
%.d: %.cpp
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@ # 
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@


-include $(DEPS)

clean:
	rm *.o ${EXE}

help:
	@echo "Available targets:"
	@echo " all		: Build the executable file (default target)"
	@echo " clean		: Remove all object files and the executable"
	@echo " help		: Display this help message"