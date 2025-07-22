#include "Cube.h"
#include <stdexcept>
#include <unordered_map>

// Default colors per face (center defines face color)
static const char COLORS[6] = {'W','R','G','Y','O','B'};

Cube::Cube() {
    for (int f = 0; f < 6; ++f) state_[f].fill(COLORS[f]);
}

Cube::Cube(const State &s) : state_(s) {}

void Cube::move(const std::string &mv) {
    static const std::unordered_map<std::string, void(Cube::*)()> table = {
        {"U", &Cube::U}, {"U'", &Cube::Up}, {"U2", &Cube::U2},
        {"R", &Cube::R}, {"R'", &Cube::Rp}, {"R2", &Cube::R2},
        {"F", &Cube::F}, {"F'", &Cube::Fp}, {"F2", &Cube::F2},
        {"D", &Cube::D}, {"D'", &Cube::Dp}, {"D2", &Cube::D2},
        {"L", &Cube::L}, {"L'", &Cube::Lp}, {"L2", &Cube::L2},
        {"B", &Cube::B}, {"B'", &Cube::Bp}, {"B2", &Cube::B2},
    };
    auto it = table.find(mv);
    if (it == table.end()) throw std::invalid_argument("Illegal move: " + mv);
    (this->*(it->second))();
}

void Cube::applyMoves(const std::vector<std::string> &moves){
    for(const auto &m:moves) move(m);
}

bool Cube::isSolved() const {
    for(int f=0; f<6; ++f){
        char c = state_[f][4];
        for(int i=0;i<9;++i) if(state_[f][i]!=c) return false;
    }
    return true;
}

std::string Cube::hash() const {
    std::string s; s.reserve(54);
    for(int f=0; f<6; ++f)
        for(char c: state_[f]) s.push_back(c);
    return s;
}

// ---- low-level face rotations ----
static inline void rotCW(Cube::Face &f){
    Cube::Face t=f;
    f[0]=t[6]; f[1]=t[3]; f[2]=t[0];
    f[3]=t[7]; f[4]=t[4]; f[5]=t[1];
    f[6]=t[8]; f[7]=t[5]; f[8]=t[2];
}
static inline void rotCCW(Cube::Face &f){
    Cube::Face t=f;
    f[0]=t[2]; f[1]=t[5]; f[2]=t[8];
    f[3]=t[1]; f[4]=t[4]; f[5]=t[7];
    f[6]=t[0]; f[7]=t[3]; f[8]=t[6];
}

void Cube::rotateFaceCW(int f){ rotCW(state_[f]); }
void Cube::rotateFaceCCW(int f){ rotCCW(state_[f]); }
void Cube::rotateFace180(int f){ rotateFaceCW(f); rotateFaceCW(f); }

// Helper macro to cycle four 3-sticker groups
#define CYCLE3(a,b,c,d) { auto T=a; a=d; d=c; c=b; b=T; }

// ---- Moves ----
// NOTE: Sticker mapping assumes a standard orientation. Double-check indices if we change face order.

void Cube::U(){
    rotateFaceCW(0);
    auto &R=state_[1], &F=state_[2], &L=state_[4], &B=state_[5];
    CYCLE3(F[0], R[0], B[0], L[0]);
    CYCLE3(F[1], R[1], B[1], L[1]);
    CYCLE3(F[2], R[2], B[2], L[2]);
}
void Cube::Up(){ U(); U(); U(); }
void Cube::U2(){ U(); U(); }

void Cube::D(){
    rotateFaceCW(3);
    auto &R=state_[1], &F=state_[2], &L=state_[4], &B=state_[5];
    CYCLE3(F[6], L[6], B[6], R[6]);
    CYCLE3(F[7], L[7], B[7], R[7]);
    CYCLE3(F[8], L[8], B[8], R[8]);
}
void Cube::Dp(){ D(); D(); D(); }
void Cube::D2(){ D(); D(); }

void Cube::R(){
    rotateFaceCW(1);
    auto &U=state_[0], &F=state_[2], &D=state_[3], &B=state_[5];
    char t0=U[2], t1=U[5], t2=U[8];
    U[2]=F[2]; U[5]=F[5]; U[8]=F[8];
    F[2]=D[2]; F[5]=D[5]; F[8]=D[8];
    D[2]=B[6]; D[5]=B[3]; D[8]=B[0];
    B[6]=t0;   B[3]=t1;   B[0]=t2;
}
void Cube::Rp(){ R(); R(); R(); }
void Cube::R2(){ R(); R(); }

void Cube::L(){
    rotateFaceCW(4);
    auto &U=state_[0], &F=state_[2], &D=state_[3], &B=state_[5];
    char t0=U[0], t1=U[3], t2=U[6];
    U[0]=B[8]; U[3]=B[5]; U[6]=B[2];
    B[8]=D[0]; B[5]=D[3]; B[2]=D[6];
    D[0]=F[0]; D[3]=F[3]; D[6]=F[6];
    F[0]=t0;   F[3]=t1;   F[6]=t2;
}
void Cube::Lp(){ L(); L(); L(); }
void Cube::L2(){ L(); L(); }

void Cube::F(){
    rotateFaceCW(2);
    auto &U=state_[0], &R=state_[1], &D=state_[3], &L=state_[4];
    char t0=U[6], t1=U[7], t2=U[8];
    U[6]=L[8]; U[7]=L[5]; U[8]=L[2];
    L[8]=D[2]; L[5]=D[1]; L[2]=D[0];
    D[2]=R[0]; D[1]=R[3]; D[0]=R[6];
    R[0]=t0;   R[3]=t1;   R[6]=t2;
}
void Cube::Fp(){ F(); F(); F(); }
void Cube::F2(){ F(); F(); }

void Cube::B(){
    rotateFaceCW(5);
    auto &U=state_[0], &R=state_[1], &D=state_[3], &L=state_[4];
    char t0=U[0], t1=U[1], t2=U[2];
    U[0]=R[2]; U[1]=R[5]; U[2]=R[8];
    R[2]=D[8]; R[5]=D[7]; R[8]=D[6];
    D[8]=L[6]; D[7]=L[3]; D[6]=L[0];
    L[6]=t0;   L[3]=t1;   L[0]=t2;
}
void Cube::Bp(){ B(); B(); B(); }
void Cube::B2(){ B(); B(); }
