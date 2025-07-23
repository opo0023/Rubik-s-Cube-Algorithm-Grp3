// test_runner.cpp
// Simple batch tester to confirm BFS solves given scrambles within a depth cap
// and to verify physical validity for raw 54-character states.

// File format: test/test_cases.txt
//   - If a line has exactly 54 characters from {W,R,G,Y,O,B}, it is treated as a raw state.
//   - Otherwise, treated as a scramble (space-separated moves).

#include "Cube.h"
#include "Solver_BFS.h"
#include "Utilities.h"
#include "Validator.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>

static bool isFaceletLine(const std::string& s);

int main() {
    std::ifstream file("test/test_cases.txt");
    if (!file) {
        std::cerr << "Could not open test/test_cases.txt\n";
        return 1;
    }

    std::string line;
    std::size_t caseNo = 1;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::cout << "Case " << caseNo++ << ":\n";

        Cube cube;
        std::string err;

        if (isFaceletLine(line)) {
            if (!parseCubeFromString(line, cube, err)) {
                std::cout << "  Invalid state: " << err << "\n\n";
                continue;
            }
            std::cout << "  54-char state parsed and validated.\n";
        } else {
            std::istringstream ss(line);
            std::string mv;
            while (ss >> mv) cube.move(mv);
            std::cout << "  Scramble applied: " << line << "\n";
        }

        Solver* solver = getBFSSolver(20);
        auto path = solver->solve(cube);
        delete solver;

        std::cout << "  Solution (" << path.size() << " moves): " << join(path) << "\n";

        cube.applyMoves(path);
        std::cout << (cube.isSolved() ? "  Solved ✅" : "  FAILED ❌") << "\n\n";
    }
}

static bool isFaceletLine(const std::string& s)
{
    if (s.size() != 54) return false;
    for (char ch : s)
        if (std::string("WRGYOB").find(std::toupper(ch)) == std::string::npos)
            return false;
    return true;
}
