#include "Cube.h"
#include <iostream>
#include <sstream>

Cube::Cube() {
    for (int face = 0; face < 6; ++face)
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                state[face][i][j] = static_cast<Color>(face);
}

std::string Cube::toString() const {
    std::ostringstream out;
    for (int face = 0; face < 6; ++face) {
        out << COLOR_NAMES[face] << " Face:\n";
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                out << COLOR_NAMES[state[face][i][j]] << " ";
            }
            out << "\n";
        }
        out << "\n";
    }
    return out.str();
}

bool Cube::isSolved() const {
    for (int face = 0; face < 6; ++face)
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                if (state[face][i][j] != state[face][1][1])
                    return false;
    return true;
}

bool Cube::operator==(const Cube& other) const {
    return state == other.state;
}

bool Cube::operator!=(const Cube& other) const {
    return !(*this == other);
}

std::vector<std::string> Cube::getPossibleMoves() const {
    return { "F", "F'", "B", "B'", "U", "U'", "D", "D'", "L", "L'", "R", "R'" };
}

void Cube::move(const std::string& move) {
    applyMove(move);
}

// TO DO: implement applyMove, rotateFaceClockwise, rotateFaceCounterClockwise
void Cube::applyMove(const std::string& move) {
    // Placeholder — logic for rotations to be filled in
    std::cout << "[applyMove] Applied move: " << move << "\n";
}

void Cube::rotateFaceClockwise(int face) {
    // TODO: Add rotation logic
}

void Cube::rotateFaceCounterClockwise(int face) {
    // TODO: Add rotation logic
}
