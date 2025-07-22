CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
INC = -Iinclude

SRC_COMMON = src/Cube.cpp src/Solver_BFS.cpp src/Utilities.cpp

all: solver test_runner

solver: $(SRC_COMMON) src/main.cpp
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $@

test_runner: $(SRC_COMMON) test/test_runner.cpp
	$(CXX) $(CXXFLAGS) $(INC) $^ -o $@

clean:
	rm -f solver test_runner *.o

.PHONY: all clean
