#ifndef CUBE_H
#define CUBE_H

#include <array>
#include <string>
#include <functional>
#include <map>

class RubiksCube {
private:
    std::array<char, 9> yellow, red, white, blue, green, orange;

    void rotateFaceCW(std::array<char, 9>& face);
    void rotateFaceCCW(std::array<char, 9>& face);

public:
    // Constructor
    RubiksCube();
    
    // Input methods
    void inputCube();
    
    // Move methods
    void frontClockwise();
    void frontCClockwise();
    void topClockwise();
    void topCClockwise();
    void rightClockwise();
    void rightCClockwise();
    void leftClockwise();
    void leftCClockwise();
    void backClockwise();
    void backCClockwise();
    void bottomClockwise();
    void bottomCClockwise();
    
    // Apply move by string
    void applyMove(const std::string& move);
    
    // State checking
    bool isSolved() const;
    std::string getStateHash() const;
    
    // Solving methods (from your original code)
    void makeYellowCrossCenter();
    void makeWhiteBottomCross();
    void solveRemainingCube();
    void solveCube();
    
    // Display
    void printCube() const;
    
    // Comparison operators for STL containers
    bool operator==(const RubiksCube& other) const;
    bool operator<(const RubiksCube& other) const;
    
    // Move mapping
    static std::map<std::string, std::function<void(RubiksCube&)>> moveActions;
    static void initializeMoveActions();
};

#endif // CUBE_H