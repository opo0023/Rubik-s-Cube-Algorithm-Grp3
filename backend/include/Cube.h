#ifndef CUBE_H
#define CUBE_H

#include <array>
#include <string>
#include <vector>

/*

  Faces (0..5):
    0 = U (Up, White)
    1 = R (Right, Red)
    2 = F (Front, Green)
    3 = D (Down, Yellow)
    4 = L (Left, Orange)
    5 = B (Back, Blue)

  Each face is a 3x3 grid stored row-major:
    index: 0 1 2
           3 4 5
           6 7 8
           

  Example: state_[0][0] is the top-left sticker of the Up face.

  PUBLIC METHODS:
    - move("U"), move("R'"), move("F2"), etc. (single move)
    - applyMoves(vector<string>) (many moves)
    - isSolved() -> true if every face is a single color
    - hash() -> 54-char string (good for hashing & quick print)

  INTERNAL HELPERS will do the rotating of stickers.
*/

class Cube {
public:
    using Face  = std::array<char, 9>;
    using State = std::array<Face, 6>;

    Cube();                     // create a SOLVED cube
    explicit Cube(const State &s);

    void move(const std::string &mv);                 // one move
    void applyMoves(const std::vector<std::string> &moves); // many moves

    bool isSolved() const;
    std::string hash() const;   // 54 characters

    const State& getState() const { return state_; }
    State&       getState()       { return state_; }

private:
    State state_{};

    // rotate one face (by index f) in place
    void rotateFaceCW(int f);
    void rotateFaceCCW(int f);
    void rotateFace180(int f);

    // 18 legal moves (quarter & half turns)
    void U();  void Up();  void U2();
    void R();  void Rp();  void R2();
    void F();  void Fp();  void F2();
    void D();  void Dp();  void D2();
    void L();  void Lp();  void L2();
    void B();  void Bp();  void B2();
};

#endif 
