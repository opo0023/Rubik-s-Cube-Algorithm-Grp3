

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



#include "../include/Cube.h"
#include "../include/Solver.h"
#include "../include/Utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Test case structure
struct TestCase {
    std::string name;
    std::vector<std::string> scramble;
    int expectedMaxMoves;
    
    TestCase(const std::string& n, const std::vector<std::string>& s, int maxMoves = 20)
        : name(n), scramble(s), expectedMaxMoves(maxMoves) {}
};

// Load test cases from file
std::vector<TestCase> loadTestCases(const std::string& filename) {
    std::vector<TestCase> testCases;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open " << filename << ", using default test cases.\n";
        
        // Default test cases if file doesn't exist
        testCases.emplace_back("Simple", std::vector<std::string>{"R", "U", "R'", "U'"}, 4);
        testCases.emplace_back("Medium", std::vector<std::string>{"R", "U", "R'", "F", "R", "F'", "U", "F", "U'", "F'"}, 10);
        testCases.emplace_back("Complex", std::vector<std::string>{"R", "U2", "R'", "D", "R", "D'", "U2", "R", "U'", "R'"}, 15);
        testCases.emplace_back("Very Simple", std::vector<std::string>{"U"}, 1);
        testCases.emplace_back("Double Move", std::vector<std::string>{"R2", "U2", "F2"}, 3);
        
        return testCases;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        line = StringUtils::trim(line);
        if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments
        
        // Parse line format: "TestName: R U R' U' (expected_max_moves)"
        size_t colonPos = line.find(':');
        if (colonPos == std::string::npos) continue;
        
        std::string name = StringUtils::trim(line.substr(0, colonPos));
        std::string remaining = StringUtils::trim(line.substr(colonPos + 1));
        
        // Extract expected max moves if present
        int expectedMax = 20;
        size_t parenPos = remaining.find('(');
        if (parenPos != std::string::npos) {
            size_t closeParenPos = remaining.find(')', parenPos);
            if (closeParenPos != std::string::npos) {
                std::string maxStr = remaining.substr(parenPos + 1, closeParenPos - parenPos - 1);
                try {
                    expectedMax = std::stoi(maxStr);
                } catch (...) {
                    expectedMax = 20;
                }
                remaining = StringUtils::trim(remaining.substr(0, parenPos));
            }
        }
        
        // Parse moves
        try {
            std::vector<std::string> moves = MoveUtils::parseMovesFromString(remaining);
            testCases.emplace_back(name, moves, expectedMax);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing test case '" << name << "': " << e.what() << std::endl;
        }
    }
    
    return testCases;
}

// Run a single test case
bool runTestCase(const TestCase& testCase, Solver& solver) {
    std::cout << "\n=== Testing: " << testCase.name << " ===" << std::endl;
    
    // Create cube from scramble
    Cube cube(testCase.scramble);
    
    std::cout << "Scramble: ";
    CubeUtils::printMoveSequence(testCase.scramble);
    
    std::cout << "Initial state:" << std::endl;
    cube.printCube();
    
    // Solve
    Timer timer;
    timer.start();
    
    std::vector<std::string> solution = solver.solve(cube);
    
    double solveTime = timer.elapsed();
    
    // Check results
    bool success = false;
    if (solution.empty()) {
        std::cout << "❌ FAILED: No solution found" << std::endl;
    } else {
        // Verify solution
        if (CubeUtils::verifySolution(cube, solution)) {
            std::cout << "✅ SUCCESS: Solution verified" << std::endl;
            CubeUtils::printMoveSequence(solution);
            
            if (solution.size() <= static_cast<size_t>(testCase.expectedMaxMoves)) {
                std::cout << "✅ Move count within expected range (" << solution.size() 
                         << " ≤ " << testCase.expectedMaxMoves << ")" << std::endl;
            } else {
                std::cout << "⚠️  WARNING: Move count higher than expected (" << solution.size() 
                         << " > " << testCase.expectedMaxMoves << ")" << std::endl;
            }
            success = true;
        } else {
            std::cout << "❌ FAILED: Solution verification failed" << std::endl;
        }
    }
    
    // Print statistics
    std::cout << "Nodes explored: " << solver.getNodesExplored() << std::endl;
    std::cout << "Time taken: " << std::fixed << std::setprecision(2) << solveTime << " ms" << std::endl;
    
    return success;
}

// Run all test cases
void runAllTests(const std::vector<TestCase>& testCases) {
    std::cout << "Running test suite with " << testCases.size() << " test cases...\n" << std::endl;
    
    // Test with BFS solver
    std::cout << "=== Testing BFS Solver ===" << std::endl;
    BFSSolver bfsSolver(15); // Use smaller depth for faster testing
    
    int bfsSuccesses = 0;
    double totalBfsTime = 0;
    int totalBfsNodes = 0;
    
    for (const auto& testCase : testCases) {
        bfsSolver.resetStats();
        if (runTestCase(testCase, bfsSolver)) {
            bfsSuccesses++;
        }
        totalBfsTime += 0; // We'd need to track this in the solver
        totalBfsNodes += bfsSolver.getNodesExplored();
    }
    
    // Test with A* solver
    std::cout << "\n=== Testing A* Solver ===" << std::endl;
    AStarSolver astarSolver(15, 1); // Misplaced tiles heuristic
    
    int astarSuccesses = 0;
    double totalAstarTime = 0;
    int totalAstarNodes = 0;
    
    for (const auto& testCase : testCases) {
        astarSolver.resetStats();
        if (runTestCase(testCase, astarSolver)) {
            astarSuccesses++;
        }
        totalAstarTime += 0; // We'd need to track this in the solver
        totalAstarNodes += astarSolver.getNodesExplored();
    }
    
    // Print summary
    std::cout << "\n=== TEST SUMMARY ===" << std::endl;
    std::cout << "Total test cases: " << testCases.size() << std::endl;
    std::cout << "\nBFS Results:" << std::endl;
    std::cout << "  Successes: " << bfsSuccesses << "/" << testCases.size() << std::endl;
    std::cout << "  Success rate: " << (100.0 * bfsSuccesses / testCases.size()) << "%" << std::endl;
    std::cout << "  Total nodes explored: " << totalBfsNodes << std::endl;
    std::cout << "  Average nodes per test: " << (totalBfsNodes / static_cast<double>(testCases.size())) << std::endl;
    
    std::cout << "\nA* Results:" << std::endl;
    std::cout << "  Successes: " << astarSuccesses << "/" << testCases.size() << std::endl;
    std::cout << "  Success rate: " << (100.0 * astarSuccesses / testCases.size()) << "%" << std::endl;
    std::cout << "  Total nodes explored: " << totalAstarNodes << std::endl;
    std::cout << "  Average nodes per test: " << (totalAstarNodes / static_cast<double>(testCases.size())) << std::endl;
    
    if (totalBfsNodes > 0 && totalAstarNodes > 0) {
        double efficiency = (static_cast<double>(totalBfsNodes) / totalAstarNodes);
        std::cout << "\nA* was " << std::fixed << std::setprecision(2) << efficiency 
                  << "x more efficient than BFS in terms of nodes explored" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    try {
        std::string testFile = "test/test_cases.txt";
        if (argc > 1) {
            testFile = argv[1];
        }
        
        std::cout << "Rubik's Cube Solver Test Runner" << std::endl;
        std::cout << "================================" << std::endl;
        std::cout << "Loading test cases from: " << testFile << std::endl;
        
        std::vector<TestCase> testCases = loadTestCases(testFile);
        
        if (testCases.empty()) {
            std::cerr << "No test cases loaded. Exiting." << std::endl;
            return 1;
        }
        
        runAllTests(testCases);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
