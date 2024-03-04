SOURCES=main.cpp part1.cpp part2.cpp
OBJECTS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
DEPS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.d))
EXE=$(addprefix $(BIN_DIR)/, prog)
CXXFLAGS=-I.

ARCH?=x86-64

# Making for x86-64 e.g. x86-64 (the architecture employed)
# > make ARCH=x86-64
ifeq (${ARCH},x86-64)
CXX=g++
BUILD_DIR=build/x86-64
BIN_DIR=bin/${ARCH}
endif

# making for architecture
# > make ARCH=arm
ifeq (${ARCH},arm)
CXX=arm-rpizw-g++
BUILD_DIR=build/arm
BIN_DIR=bin/${ARCH}
endif

$(shell mkdir -p ${BUILD_DIR})
$(shell mkdir -p ${BIN_DIR})

$(EXE): $(DEPS) $(OBJECTS) # << check the $(DEPS) new dependency
	@echo "linking "$@
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# %.cpp -> %.o needs to be added! target is not just %.o
${BUILD_DIR}/%.o: %.cpp
	@echo "compiling "$@
	${CXX} -c ${CXXFLAGS} $< -o $@

# rule that describes how a .d file is created from a .cpp file
# similar to the assignment the you just completed %.cpp -> %.o
$(BUILD_DIR)/%.d: %.cpp
	@echo "Generating dependency file for $<"
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.0) -MM $(CXXFLAGS) $< >> $@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif

clean:
	rm -rf ${OBJECTS} ${EXE} ${BUILD_DIR}

help:
	@echo "Available targets:"
	@echo " clean		: Remove all object files and the executable"
	@echo " help		: Display this help message"