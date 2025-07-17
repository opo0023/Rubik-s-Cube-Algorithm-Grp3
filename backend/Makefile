CXX = g++
CXXFLAGS = -std=c++17 -Iinclude

SRC = src/Cube.cpp src/Solver_BFS.cpp src/Solver_AStar.cpp src/main.cpp
OBJ = $(SRC:.cpp=.o)

rubik: $(OBJ)
	$(CXX) $(CXXFLAGS) -o rubik $(OBJ)

test: test/test_runner.cpp src/Cube.cpp src/Solver_BFS.cpp
	$(CXX) $(CXXFLAGS) -o test_runner test/test_runner.cpp src/Cube.cpp src/Solver_BFS.cpp

clean:
	rm -f rubik test_runner *.o
