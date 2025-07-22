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
    auto rotate = [&](int face, bool clockwise, int times = 1) {
        for (int i = 0; i < times; ++i)
            clockwise ? rotateFaceClockwise(face) : rotateFaceCounterClockwise(face);
    };

    auto rotateRow = [&](int f1, int r1, int f2, int r2, int f3, int r3, int f4, int r4, bool row) {
        std::array<Color, 3> temp;
        for (int i = 0; i < 3; ++i)
            temp[i] = row ? state[f1][r1][i] : state[f1][i][r1];

        for (int i = 0; i < 3; ++i) {
            if (row) {
                state[f1][r1][i] = state[f2][r2][i];
                state[f2][r2][i] = state[f3][r3][i];
                state[f3][r3][i] = state[f4][r4][i];
                state[f4][r4][i] = temp[i];
            } else {
                state[f1][i][r1] = state[f2][i][r2];
                state[f2][i][r2] = state[f3][i][r3];
                state[f3][i][r3] = state[f4][i][r4];
                state[f4][i][r4] = temp[i];
            }
        }
    };

    if (move == "U") {
        rotate(0, true);
        rotateRow(2, 0, 5, 0, 3, 0, 4, 0, true);
    } else if (move == "U'") {
        rotate(0, false);
        rotateRow(2, 0, 4, 0, 3, 0, 5, 0, true);
    } else if (move == "U2") {
        rotate(0, true, 2);
        rotateRow(2, 0, 5, 0, 3, 0, 4, 0, true);
        rotateRow(2, 0, 5, 0, 3, 0, 4, 0, true);
    } else if (move == "D") {
        rotate(1, true);
        rotateRow(2, 2, 4, 2, 3, 2, 5, 2, true);
    } else if (move == "D'") {
        rotate(1, false);
        rotateRow(2, 2, 5, 2, 3, 2, 4, 2, true);
    } else if (move == "D2") {
        rotate(1, true, 2);
        rotateRow(2, 2, 4, 2, 3, 2, 5, 2, true);
        rotateRow(2, 2, 4, 2, 3, 2, 5, 2, true);
    } else if (move == "F") {
        rotate(2, true);
        for (int i = 0; i < 3; ++i) {
            Color temp = state[0][2][i];
            state[0][2][i] = state[4][2 - i][2];
            state[4][2 - i][2] = state[1][0][2 - i];
            state[1][0][2 - i] = state[5][i][0];
            state[5][i][0] = temp;
        }
    } else if (move == "F'") {
        rotate(2, false);
        for (int i = 0; i < 3; ++i) {
            Color temp = state[0][2][i];
            state[0][2][i] = state[5][i][0];
            state[5][i][0] = state[1][0][2 - i];
            state[1][0][2 - i] = state[4][2 - i][2];
            state[4][2 - i][2] = temp;
        }
    } else if (move == "F2") {
        applyMove("F");
        applyMove("F");
    } else if (move == "B") {
        rotate(3, true);
        for (int i = 0; i < 3; ++i) {
            Color temp = state[0][0][i];
            state[0][0][i] = state[5][i][2];
            state[5][i][2] = state[1][2][2 - i];
            state[1][2][2 - i] = state[4][2 - i][0];
            state[4][2 - i][0] = temp;
        }
    } else if (move == "B'") {
        rotate(3, false);
        for (int i = 0; i < 3; ++i) {
            Color temp = state[0][0][i];
            state[0][0][i] = state[4][2 - i][0];
            state[4][2 - i][0] = state[1][2][2 - i];
            state[1][2][2 - i] = state[5][i][2];
            state[5][i][2] = temp;
        }
    } else if (move == "B2") {
        applyMove("B");
        applyMove("B");
    } else if (move == "L") {
        rotate(4, true);
        for (int i = 0; i < 3; ++i) {
            Color temp = state[0][i][0];
            state[0][i][0] = state[3][2 - i][2];
            state[3][2 - i][2] = state[1][i][0];
            state[1][i][0] = state[2][i][0];
            state[2][i][0] = temp;
        }
    } else if (move == "L'") {
        rotate(4, false);
        for (int i = 0; i < 3; ++i) {
            Color temp = state[0][i][0];
            state[0][i][0] = state[2][i][0];
            state[2][i][0] = state[1][i][0];
            state[1][i][0] = state[3][2 - i][2];
            state[3][2 - i][2] = temp;
        }
    } else if (move == "L2") {
        applyMove("L");
        applyMove("L");
    } else if (move == "R") {
        rotate(5, true);
        for (int i = 0; i < 3; ++i) {
            Color temp = state[0][i][2];
            state[0][i][2] = state[2][i][2];
            state[2][i][2] = state[1][i][2];
            state[1][i][2] = state[3][2 - i][0];
            state[3][2 - i][0] = temp;
        }
    } else if (move == "R'") {
        rotate(5, false);
        for (int i = 0; i < 3; ++i) {
            Color temp = state[0][i][2];
            state[0][i][2] = state[3][2 - i][0];
            state[3][2 - i][0] = state[1][i][2];
            state[1][i][2] = state[2][i][2];
            state[2][i][2] = temp;
        }
    } else if (move == "R2") {
        applyMove("R");
        applyMove("R");
    } else {
        std::cerr << "[applyMove] Invalid move: " << move << "\\n";
    }
}


void Cube::rotateFaceClockwise(int face) {
    std::array<std::array<Color, 3>, 3> temp = state[face];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            state[face][j][2 - i] = temp[i][j];
}


void Cube::rotateFaceCounterClockwise(int face) {
    std::array<std::array<Color, 3>, 3> temp = state[face];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            state[face][2 - j][i] = temp[i][j];
}

