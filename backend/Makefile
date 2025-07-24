 Add this to your Cube.h:

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

cpp
void printCubeState(const Cube& cube);
void printMoveSequence(const std::vector<std::string>& moves);

void printCubeState(const Cube& cube) {
    std::cout << "Current cube state:\n";
    cube.printCube();
    std::cout << "Solved: " << (cube.isSolved() ? "Yes" : "No") << "\n\n";
}

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