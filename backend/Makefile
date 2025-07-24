

Page 1 of 4 CSCE 4410 Project – Graph-Based Algorithm Design Project Title: Solving the Rubik’s Cube Using Graph Search Algorithms in C++ with STL Project Objective: In this project, you will apply graph search techniques from CSCE 4410 (Algorithms) to programmatically solve a standard 3×3 R

pasted

This is my output how can i fix this. noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$ make clean && make
rm -f solver test_runner *.o
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/Cube.cpp src/Solver_BFS.cpp src/Utilities.cpp src/main.cpp -o solver
.g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/Cube.cpp src/Solver_BFS.cpp src/Utilities.cpp test/test_runner.cpp -o test_runner
noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$ ./solver
Enter scramble moves (space-separated). Empty line = solved cube.
> B' G R W O'
terminate called after throwing an instance of 'std::invalid_argument'
  what():  Illegal move: G
Aborted (core dumped)
noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$ ./solver
Enter scramble moves (space-separated). Empty line = solved cube.
> B' R W O
terminate called after throwing an instance of 'std::invalid_argument'
  what():  Illegal move: W
Aborted (core dumped)
noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$ ./solver
Enter scramble moves (space-separated). Empty line = solved cube.
> R' O B
terminate called after throwing an instance of 'std::invalid_argument'
  what():  Illegal move: O
Aborted (core dumped)
noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$ make clean
rm -f solver test_runner *.o
noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$ make clean && make
rm -f solver test_runner *.o
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/Cube.cpp src/Solver_BFS.cpp src/Utilities.cpp src/main.cpp -o solver
^[[A^[[A^[[Ag++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/Cube.cpp src/Solver_BFS.cpp src/Utilities.cpp test/test_runner.cpp -o test_runner
noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$ ./solver
Enter scramble moves (space-separated). Empty line = solved cube.
> U' R F D 
Max BFS depth (default 20)? 20
Solution (4 moves): D' F' R' U
Verified solved!
WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB
noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$

Looking at your output, the issue is clear: your Rubik's Cube solver is expecting standard Rubik's Cube notation (like U, R, F, D, L, B with optional prime marks), but you're entering color names (G for Green, W for White, O for Orange) instead of face rotation moves.

The Problem
In Rubik's Cube notation:

U, D, L, R, F, B represent the six faces (Up, Down, Left, Right, Front, Back)
Prime (') indicates a counterclockwise rotation
Colors (W, R, G, Y, O, B) are NOT valid moves - they're just the colors of the faces
The Fix
You have a few options to resolve this:

Option 1: Use Correct Notation (Recommended)
Simply use proper Rubik's Cube moves instead of color names:

bash
# Instead of: B' G R W O'
# Use: B' F R U D'

# Instead of: B' R W O  
# Use: B' R U D

# Instead of: R' O B
# Use: R' D B
Option 2: Add Color-to-Move Mapping (If Required by Assignment)
If your assignment specifically requires accepting color inputs, you'll need to modify your code to map colors to moves. Add this to your Cube.cpp or Utilities.cpp:

cpp
std::string translateColorToMove(const std::string& input) {
    std::map<std::string, std::string> colorToMove = {
        {"W", "U"},   // White -> Up
        {"Y", "D"},   // Yellow -> Down  
        {"R", "R"},   // Red -> Right
        {"O", "L"},   // Orange -> Left
        {"G", "F"},   // Green -> Front
        {"B", "B"}    // Blue -> Back
    };
    
    std::string move = input;
    std::string prime = "";
    
    // Check for prime notation
    if (move.back() == '\'') {
        prime = "'";
        move.pop_back();
    }
    
    if (colorToMove.find(move) != colorToMove.end()) {
        return colorToMove[move] + prime;
    }
    
    return input; // Return original if not a color
}
Option 3: Update Input Validation
Modify your move validation to provide clearer error messages:

cpp
void validateMove(const std::string& move) {
    std::set<std::string> validMoves = {
        "U", "U'", "D", "D'", "L", "L'", 
        "R", "R'", "F", "F'", "B", "B'"
    };
    
    if (validMoves.find(move) == validMoves.end()) {
        std::cerr << "Error: '" << move << "' is not a valid move.\n";
        std::cerr << "Valid moves are: U, U', D, D', L, L', R, R', F, F', B, B'\n";
        std::cerr << "Colors (W, G, R, Y, O, B) are not valid moves.\n";
        throw std::invalid_argument("Illegal move: " + move);
    }
}
Quick Test
Your solver works correctly with proper notation, as shown in your last successful run:

> U' R F D 
Solution (4 moves): D' F' R' U
The simplest fix is to use standard Rubik's Cube notation instead of color names. If you need to support color input for your specific assignment requirements, implement the color-to-move mapping as shown above.





this is my output does this mean its correct? noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$ ./solver
Enter scramble moves (space-separated). Empty line = solved cube.
> U' R F F' D D' L L' B' 
Max BFS depth (default 20)? 20
Solution (3 moves): B R' U
Verified solved!
WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB
noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$

Yes, this output indicates your solver is working correctly! Here's what each part means:

✅ What This Shows
Input Accepted: Your solver correctly parsed the scramble sequence U' R F F' D D' L L' B'
Efficient Solution Found:
Input: 9 moves to scramble
Solution: Only 3 moves to solve (B R' U)
This is excellent optimization!
Solution Verified: The "Verified solved!" message means your solver:
Applied the solution moves to the scrambled cube
Checked isSolved() and confirmed it returned true
Correct Solved State: The final string WWWWWWWWWRRRRRRRRRGGGGGGGGGYYYYYYYYYOOOOOOOOOBBBBBBBBB represents a solved cube where each face shows a single color (all W's for one face, all R's for another, etc.)
🔍 Why 3 Moves vs 9 Moves?
Your input sequence had redundant moves:

F F' cancels out (F followed by F-inverse)
D D' cancels out
L L' cancels out
So effectively you scrambled with: U' R B' And the solution B R' U is the exact inverse sequence, which is mathematically correct!

✅ This Demonstrates Your Solver is Working Because:
Correct parsing of Rubik's cube notation
Proper BFS implementation finding an optimal solution
Accurate state representation and move execution
Working verification system confirming the solution is valid
Efficient search (found 3-move solution quickly within depth 20)
Your Rubik's Cube solver appears to be implemented correctly and working as expected!




but isnt it not layering?

You're absolutely right to question this! The issue is with the scramble sequence you entered, not necessarily the solver itself.

The Problem: Ineffective Scrambling
Your input: U' R F F' D D' L L' B'

When we simplify this:

F F' = no movement (F cancels with F')
D D' = no movement (D cancels with D')
L L' = no movement (L cancels with L')
Effective scramble: U' R B'

This is only 3 moves, so it's not surprising the cube isn't really scrambled much. The solver just needs to reverse these 3 moves: B R' U.

Test with a Real Scramble
Try a proper scramble that doesn't have canceling moves:

bash
> R U R' F R F' U F U' F'
Or:

bash
> R U' R' D R D' U R U' R'
These sequences will actually scramble the cube significantly and force your BFS to work harder.

What "Layering" Means
In Rubik's cube solving, layering refers to solving the cube layer by layer (bottom → middle → top). Your BFS solver doesn't use layering - it tries all possible move combinations until it finds the shortest path to the solved state.

If you want to test whether your solver can handle properly scrambled cubes, try:

bash
./solver
> R U R U R U R U R U R U
This will create a real scramble that requires more complex solving, not just reversing 3 simple moves.

Your solver is likely correct - you just need to test it with scrambles that actually scramble the cube!





noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$ ./solver
Enter scramble moves (space-separated). Empty line = solved cube.
> > R U R' F R F' U F U' F'
terminate called after throwing an instance of 'std::invalid_argument'
  what():  Illegal move: >
Aborted (core dumped)
noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$

The issue is that you accidentally typed > as part of your input! The > is just the command prompt, not part of the moves.

What Happened
bash
> > R U R' F R F' U F U' F'
Your solver tried to parse > as a move, which isn't valid.

Correct Input
Just enter the moves without the >:

bash
noc0014@cell16-cse:~/Rubik-s-Cube-Algorithm-Grp3/backend$ ./solver
Enter scramble moves (space-separated). Empty line = solved cube.
> R U R' F R F' U F U' F'
Try These Test Scrambles
Here are some good scrambles to test your solver:

Simple scramble (should solve quickly):

R U R' U'
Medium scramble:

R U R' F R F' U F U' F'
More complex scramble:

R U2 R' D R D' U2 R U' R'
Very scrambled (may take longer):

R U R U R U R U R U R U
Just make sure to only type the moves after the > prompt, without including the > symbol itself!






#include <iostream> #include <string> #include <array> #include <algorithm> //lastest version using namespace std; class RubiksCube { private: array<char, 9> yellow, red, white, blue, green, orange; void rotateFaceCW(array<char, 9>& face) { swap(face[0], face[6]);

pasted

This is my friends code How can i implement some of this in mine to be better and what files should i put it in

Looking at your friend's code and comparing it to your project structure, here are the key improvements you can implement:

1. Enhanced Cube Representation (Add to Cube.h and Cube.cpp)
Your friend uses individual face arrays which is cleaner than a single vector. Add this to your Cube.h:

cpp
class Cube {
private:
    std::array<char, 9> up, down, left, right, front, back;
    
    // Helper methods for face rotation
    void rotateFaceCW(std::array<char, 9>& face);
    void rotateFaceCCW(std::array<char, 9>& face);
    
public:
    // Constructor from scramble moves
    Cube(const std::vector<std::string>& scrambleMoves = {});
    
    // Move methods
    void U(); void U_prime();
    void R(); void R_prime();
    void F(); void F_prime();
    void D(); void D_prime();
    void L(); void L_prime();
    void B(); void B_prime();
    
    // Your existing methods
    void applyMove(const std::string& move);
    bool isSolved() const;
    std::string getStateHash() const;
    
    // New utility methods
    void printCube() const;
    bool operator==(const Cube& other) const;
};
2. Better Face Rotation Logic (Add to Cube.cpp)
cpp
void Cube::rotateFaceCW(std::array<char, 9>& face) {
    std::array<char, 9> temp = face;
    face[0] = temp[6]; face[1] = temp[3]; face[2] = temp[0];
    face[3] = temp[7]; face[4] = temp[4]; face[5] = temp[1];
    face[6] = temp[8]; face[7] = temp[5]; face[8] = temp[2];
}

void Cube::rotateFaceCCW(std::array<char, 9>& face) {
    std::array<char, 9> temp = face;
    face[0] = temp[2]; face[1] = temp[5]; face[2] = temp[8];
    face[3] = temp[1]; face[4] = temp[4]; face[5] = temp[7];
    face[6] = temp[0]; face[7] = temp[3]; face[8] = temp[6];
}
3. Improved Move Implementation (Update Cube.cpp)
Instead of hardcoding moves, implement them systematically:

cpp
void Cube::U() {
    rotateFaceCW(up);
    // Rotate adjacent edges
    std::array<char, 3> temp = {front[0], front[1], front[2]};
    front[0] = right[0]; front[1] = right[1]; front[2] = right[2];
    right[0] = back[0]; right[1] = back[1]; right[2] = back[2];
    back[0] = left[0]; back[1] = left[1]; back[2] = left[2];
    left[0] = temp[0]; left[1] = temp[1]; left[2] = temp[2];
}

void Cube::U_prime() {
    U(); U(); U(); // Three clockwise = one counter-clockwise
}
4. Enhanced State Comparison (Add to Cube.cpp)
cpp
bool Cube::operator==(const Cube& other) const {
    return up == other.up && down == other.down && 
           left == other.left && right == other.right &&
           front == other.front && back == other.back;
}

bool Cube::isSolved() const {
    auto checkFace = [](const std::array<char, 9>& face) {
        char center = face[4];
        return std::all_of(face.begin(), face.end(), 
                          [center](char c) { return c == center; });
    };
    
    return checkFace(up) && checkFace(down) && checkFace(left) && 
           checkFace(right) && checkFace(front) && checkFace(back);
}
5. Better Debugging Output (Add to Utilities.h and Utilities.cpp)
cpp
// In Utilities.h
void printCubeState(const Cube& cube);
void printMoveSequence(const std::vector<std::string>& moves);

// In Utilities.cpp
void printCubeState(const Cube& cube) {
    std::cout << "Current cube state:\n";
    cube.printCube();
    std::cout << "Solved: " << (cube.isSolved() ? "Yes" : "No") << "\n\n";
}
6. Enhanced Input Validation (Update main.cpp)
cpp
// In main.cpp
bool isValidMove(const std::string& move) {
    static const std::set<std::string> validMoves = {
        "U", "U'", "R", "R'", "F", "F'", 
        "D", "D'", "L", "L'", "B", "B'"
    };
    return validMoves.count(move) > 0;
}

std::vector<std::string> parseInput(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> moves;
    std::string move;
    
    while (iss >> move) {
        if (!isValidMove(move)) {
            throw std::invalid_argument("Invalid move: " + move + 
                "\nValid moves: U, U', R, R', F, F', D, D', L, L', B, B'");
        }
        moves.push_back(move);
    }
    return moves;
}
7. File Organization Summary
Cube.h: Add face arrays, rotation methods, comparison operators
Cube.cpp: Implement systematic move functions and face rotations
Utilities.h/cpp: Add debugging and validation functions
main.cpp: Improve input parsing and error messages
Solver_BFS.cpp: Keep your existing BFS logic but use the improved Cube class
8. Key Improvements to Adopt
Cleaner face representation with individual arrays
Systematic move implementation instead of hardcoded matrices
Better debugging output to visualize cube states
Robust input validation with clear error messages
Proper face rotation logic that's easier to understand
The main advantage of your friend's approach is the clarity and maintainability - each face is separate, moves are implemented systematically, and the code is easier to debug. Your BFS algorithm can stay the same, but with a more robust underlying Cube class.





Okay put this code into these files include/ │ ├── Cube.h // Cube structure and state transitions │ ├── Solver.h // Base interface for all solvers │ └── Utilities.h // Helpers: hashing, string ops, etc. ├── src/ │ ├── Cube.cpp // Cube implementation: moves, comparison │ ├── Solver_BFS.cpp // BFS search algorithm │ ├── Solver_AStar.cpp // A* or IDA* with heuristics │ └── main.cpp // Command-line entry point ├── test/ │ ├── test_cases.txt // Scrambled inputs for testing │ └── test_runner.cpp // Validation of solver outputs ├── docs/ │ ├── Report.pdf // Final report │ └── Diagrams.md // Optional cube layout/flow diagrams ├── README.md // Instructions and usage guide └── Makefile // Build automation

I'll help you organize the improved code into your project structure. Here are the files:


include/Cube.h
Code 




#include <iostream> #include <string> #include <array> #include <algorithm> //lastest version using namespace std; class RubiksCube { private: array<char, 9> yellow, red, white, blue, green, orange; void rotateFaceCW(array<char, 9>& face) { swap(face[0], face[6]);

pasted

Okay put this code into these files include/ │ ├── Cube.h // Cube structure and state transitions │ ├── Solver.h // Base interface for all solvers │ └── Utilities.h // Helpers: hashing, string ops, etc. ├── src/ │ ├── Cube.cpp // Cube implementation: moves, comparison │ ├── Solver_BFS.cpp // BFS search algorithm │ ├── Solver_AStar.cpp // A* or IDA* with heuristics │ └── main.cpp // Command-line entry point ├── test/ │ ├── test_cases.txt // Scrambled inputs for testing │ └── test_runner.cpp // Validation of solver outputs ├── docs/ │ ├── Report.pdf // Final report │ └── Diagrams.md // Optional cube layout/flow diagrams ├── README.md // Instructions and usage guide └── Makefile // Build automation

I'll help you organize your friend's code into the proper project structure. Let me create all the necessary files:


include/Cube.h
Code 

include/Solver.h
Code 

include/Utilities.h
Code 

src/Cube.cpp
Code 

src/Utilities.cpp
Code 



Tell me what files to put each code into that you made

Here's the complete breakdown of which code goes into which files:

Header Files (include/ directory)
include/Cube.h
Use the code from artifact: cube_header_improved

Contains the Cube class definition with face arrays
Method declarations for moves and utilities
CubeHasher struct for STL containers
include/Solver.h
Use the code from artifact: solver_header

Abstract Solver base class
BFSSolver and AStarSolver class declarations
Virtual methods for different solving algorithms
include/Utilities.h
Use the code from artifact: utilities_header

Utility namespaces: StringUtils, MoveUtils, CubeUtils, HashUtils
Timer class for performance measurement
DebugUtils and IOUtils namespaces
Source Files (src/ directory)
src/Cube.cpp
Use the code from artifact: cube_implementation

All move implementations from your friend's code
Face rotation logic (rotateFaceCW, rotateFaceCCW)
Standard notation mapping (U, R, F, etc.)
State comparison and hashing methods
src/Utilities.cpp
Use the code from artifact: utilities_implementation (Note: This was cut off, I'll create the complete version)

Let me create the remaining files:


src/Utilities.cpp (Complete)
Code 
Now let me create the remaining source files:


src/Solver_BFS.cpp
Code 

src/Solver_AStar.cpp
Code 

src/main.cpp
Code 



Continue


src/main.cpp
Code 
Now let me create the remaining files:


test/test_runner.cpp
Code 

test/test_cases.txt
Code 

Makefile
Code 

README.md
Document 



# Makefile for Rubik's Cube Solver Project
# CSCE 4410 - Graph-Based Algorithm Design

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter
INCLUDES = -Iinclude
DEBUG_FLAGS = -g -DDEBUG

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = test
OBJ_DIR = obj

# Source files
SOURCES = $(SRC_DIR)/Cube.cpp $(SRC_DIR)/Solver_BFS.cpp $(SRC_DIR)/Solver_AStar.cpp $(SRC_DIR)/Utilities.cpp
MAIN_SRC = $(SRC_DIR)/main.cpp
TEST_SRC = $(TEST_DIR)/test_runner.cpp

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(OBJ_DIR)/main.o
TEST_OBJ = $(OBJ_DIR)/test_runner.o

# Executables
SOLVER = solver
TEST_RUNNER = test_runner

# Default target
all: $(SOLVER) $(TEST_RUNNER)

# Main solver executable
$(SOLVER): $(OBJECTS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Test runner executable
$(TEST_RUNNER): $(OBJECTS) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile test files to object files
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(SOLVER) $(TEST_RUNNER)

# Release build (optimized)
release: CXXFLAGS += -O3 -DNDEBUG
release: $(SOLVER) $(TEST_RUNNER)

# Run the solver
run: $(SOLVER)
	./$(SOLVER)

# Run tests
test: $(TEST_RUNNER)
	./$(TEST_RUNNER)

# Run specific test file
test-file: $(TEST_RUNNER)
	./$(TEST_RUNNER) $(TEST_DIR)/test_cases.txt

# Performance test with time measurement
perf-test: $(TEST_RUNNER)
	time ./$(TEST_RUNNER)

# Clean build files
clean:
	rm -f $(SOLVER) $(TEST_RUNNER)
	rm -rf $(OBJ_DIR)
	rm -f *.o

# Clean and rebuild
rebuild: clean all

# Install (copy to system directory)
install: $(SOLVER)
	cp $(SOLVER) /usr/local/bin/

# Create documentation directory structure
docs:
	mkdir -p docs
	@echo "# Rubik's Cube Solver Documentation" > docs/README.md
	@echo "Generated on $$(date)" >> docs/README.md

# Validate code (basic syntax check)
validate:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -fsyntax-only $(SOURCES) $(MAIN_SRC) $(TEST_SRC)

# Show compilation database for IDEs
compile-db:
	@echo "Generate compile_commands.json for better IDE support:"
	@echo "Use: bear -- make clean all"

# Memory check with valgrind (if available)
memcheck: $(SOLVER)
	@if command -v valgrind >/dev/null 2>&1; then \
		echo "Running memory check..."; \
		echo "R U R' U'" | valgrind --leak-check=full --show-leak-kinds=all ./$(SOLVER); \
	else \
		echo "Valgrind not available, skipping memory check"; \
	fi

# Code formatting (if clang-format is available)
format:
	@if command -v clang-format >/dev/null 2>&1; then \
		echo "Formatting code..."; \
		find $(SRC_DIR) $(INCLUDE_DIR) $(TEST_DIR) -name "*.cpp" -o -name "*.h" | xargs clang-format -i; \
	else \
		echo "clang-format not available, skipping formatting"; \
	fi

# Static analysis (if cppcheck is available)
analyze:
	@if command -v cppcheck >/dev/null 2>&1; then \
		echo "Running static analysis..."; \
		cppcheck --enable=all --std=c++17 $(INCLUDES) $(SRC_DIR)/ $(TEST_DIR)/; \
	else \
		echo "cppcheck not available, skipping static analysis"; \
	fi

# Help target
help:
	@echo "Available targets:"
	@echo "  all         - Build solver and test runner (default)"
	@echo "  solver      - Build only the main solver"
	@echo "  test_runner - Build only the test runner"
	@echo "  debug       - Build with debug flags"
	@echo "  release     - Build optimized release version"
	@echo "  run         - Build and run the solver"
	@echo "  test        - Build and run tests"
	@echo "  test-file   - Run tests with specific test file"
	@echo "  perf-test   - Run performance test with timing"
	@echo "  clean       - Remove all build files"
	@echo "  rebuild     - Clean and rebuild everything"
	@echo "  validate    - Check syntax without building"
	@echo "  memcheck    - Run memory leak detection (requires valgrind)"
	@echo "  format      - Format code (requires clang-format)"
	@echo "  analyze     - Run static analysis (requires cppcheck)"
	@echo "  help        - Show this help message"

# Dependency tracking
-include $(OBJECTS:.o=.d)
-include $(MAIN_OBJ:.o=.d)
-include $(TEST_OBJ:.o=.d)

# Generate dependency files
$(OBJ_DIR)/%.d: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MM -MT $(OBJ_DIR)/$*.o $< > $@

$(OBJ_DIR)/%.d: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MM -MT $(OBJ_DIR)/$*.o $< > $@

# Mark targets as phony
.PHONY: all debug release run test test-file perf-test clean rebuild install docs validate compile-db memcheck format analyze help
