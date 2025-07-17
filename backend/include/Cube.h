#ifndef CUBE_H
#define CUBE_H

#include <array>
#include <string>
#include <vector>

enum Color { WHITE, GREEN, RED, BLUE, ORANGE, YELLOW };
const std::vector<std::string> COLOR_NAMES = { "W", "G", "R", "B", "O", "Y" };

class Cube {
public:
    Cube();  // initialize solved cube
    std::string toString() const;
    bool isSolved() const;

    void move(const std::string& move);  // apply a single move (e.g., F, F')
    std::vector<std::string> getPossibleMoves() const;

    bool operator==(const Cube& other) const;
    bool operator!=(const Cube& other) const;

private:
    std::array<std::array<std::array<Color, 3>, 3>, 6> state;
    void rotateFaceClockwise(int face);
    void rotateFaceCounterClockwise(int face);
    void applyMove(const std::string& move);
};

#endif
