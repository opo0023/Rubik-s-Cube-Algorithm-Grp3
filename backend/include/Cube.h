#ifndef CUBE_H
#define CUBE_H

#include <array>
#include <string>
#include <vector>

/*
 Faces (fixed order):
   0 = U (Up), 1 = R (Right), 2 = F (Front),
   3 = D (Down),4 = L (Left), 5 = B (Back)

Each face is 3x3 stored row-major: indexes 0..8
(face[0] top-left, face[8] bottom-right).

Public API:
  - move("U"), move("U'"), move("U2"), etc.
  - applyMoves(vector<string>)
  - isSolved()
  - hash(): 54-char state string for hashing/printing
*/

class Cube {
public:
    using Face  = std::array<char, 9>;
    using State = std::array<Face, 6>;

    Cube();                     
    explicit Cube(const State &s);

    void move(const std::string &mv);
    void applyMoves(const std::vector<std::string> &moves);

    bool isSolved() const;
    std::string hash() const;

    const State& getState() const { return state_; }

private:
    State state_{};

    // --- helpers: rotate a single face in place
    void rotateFaceCW(int f);
    void rotateFaceCCW(int f);
    void rotateFace180(int f);

    // --- individual quarter/half turns
    void U();  void Up();  void U2();
    void R();  void Rp();  void R2();
    void F();  void Fp();  void F2();
    void D();  void Dp();  void D2();
    void L();  void Lp();  void L2();
    void B();  void Bp();  void B2();
};

#endif 
