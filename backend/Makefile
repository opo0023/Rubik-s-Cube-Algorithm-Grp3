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