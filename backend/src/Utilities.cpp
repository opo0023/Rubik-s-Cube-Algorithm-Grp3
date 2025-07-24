#include "Utilities.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <functional>

namespace Utilities {
    
    std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;
        
        while (std::getline(ss, token, delimiter)) {
            token = trim(token);
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        
        return tokens;
    }
    
    std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        
        size_t end = str.find_last_not_of(" \t\r\n");
        return str.substr(start, end - start + 1);
    }
    
    void Timer::start() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
    double Timer::getElapsedSeconds() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return duration.count() / 1000000.0;
    }
    
    void Timer::printElapsed(const std::string& label) const {
        double elapsed = getElapsedSeconds();
        if (!label.empty()) {
            std::cout << label << ": ";
        }
        std::cout << elapsed << " seconds" << std::endl;
    }
    
    std::size_t CubeHasher::operator()(const std::string& state) const {
        return std::hash<std::string>{}(state);
    }
    
    std::string moveSequenceToString(const std::vector<std::string>& moves) {
        if (moves.empty()) return "No moves needed (already solved)";
        
        std::string result;
        for (size_t i = 0; i < moves.size(); ++i) {
            if (i > 0) result += " ";
            result += moves[i];
        }
        return result;
    }
    
    std::vector<std::string> parseScramble(const std::string& scramble) {
        return split(scramble, ' ');
    }
    
    bool isValidMove(const std::string& move) {
        const std::vector<std::string> validMoves = {
            "F", "F'", "U", "U'", "R", "R'", 
            "L", "L'", "B", "B'", "D", "D'"
        };
        
        return std::find(validMoves.begin(), validMoves.end(), move) != validMoves.end();
    }
    
    bool isValidColor(char color) {
        const std::string validColors = "rwybgo";
        return validColors.find(std::tolower(color)) != std::string::npos;
    }
    
}