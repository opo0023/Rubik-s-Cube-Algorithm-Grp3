#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <vector>
#include <chrono>

namespace Utilities {
    // String manipulation helpers
    std::vector<std::string> split(const std::string& str, char delimiter);
    std::string trim(const std::string& str);
    
    // Timing utilities
    class Timer {
    private:
        std::chrono::high_resolution_clock::time_point start_time;
        
    public:
        void start();
        double getElapsedSeconds() const;
        void printElapsed(const std::string& label = "") const;
    };
    
    // Hash function for cube states (if needed for custom containers)
    struct CubeHasher {
        std::size_t operator()(const std::string& state) const;
    };
    
    // Move sequence utilities
    std::string moveSequenceToString(const std::vector<std::string>& moves);
    std::vector<std::string> parseScramble(const std::string& scramble);
    
    // Validation helpers
    bool isValidMove(const std::string& move);
    bool isValidColor(char color);
}

#endif // UTILITIES_H