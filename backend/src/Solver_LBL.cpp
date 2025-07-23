#include "Solver_LBL.h"
#include "Cube.h"
#include <vector>
#include <string>
#include <algorithm>

/*
  Layer-By-Layer (LBL) method.
  5 phases:

    1) Make WHITE CROSS on the Up face.
    2) Insert the WHITE CORNERS to finish the first layer.
    3) Solve the middle (second) layer edges.
    4) OLL = Orient Last Layer -> make the whole Down (Yellow) face yellow.
    5) PLL = Permute Last Layer -> move the last layer pieces around until solved.

    Not "shortest path" but straightforward
*/

static inline void add(std::vector<std::string> &dst,
                       const std::initializer_list<std::string> &seq){
    dst.insert(dst.end(), seq.begin(), seq.end());
}
static inline void apply(Cube &c, std::vector<std::string> &dst,
                         const std::initializer_list<std::string> &seq){
    for(const auto &m: seq){ c.move(m); dst.push_back(m); }
}

// tiny helpers to read stickers
static char f(const Cube& c,int face,int idx) [[maybe_unused]];
static char f(const Cube& c,int face,int idx){ return c.getState()[face][idx]; }

// PHASE CHECKERS

// White cross = white edges on U at positions 1,3,5,7
static bool whiteCrossDone(const Cube &c){
    const auto &u = c.getState()[0];
    return u[1]=='W' && u[3]=='W' && u[5]=='W' && u[7]=='W';
}

// Full first layer = whole Up face white
static bool firstLayerDone(const Cube &c){
    const auto &u=c.getState()[0];
    for(char x:u) if(x!='W') return false;
    return true;
}

// Quick check: middle edges are correct (middle row of side faces match center)
static bool secondLayerDone(const Cube &c){
    // faces 1=R,2=F,4=L,5=B, middle row = indices 3,4,5.
    for(int face: {1,2,4,5}){
        const auto &s = c.getState()[face];
        char center = s[4];
        if(s[3]!=center || s[5]!=center) return false;
    }
    return true;
}

// OLL done = entire Down face is Yellow
static bool OLL_Done(const Cube &c){
    const auto &d=c.getState()[3];
    for(char x:d) if(x!='Y') return false;
    return true;
}

//PHASE 1: WHITE CROSS
/*

    - Spin D to bring a white edge to front
    - Use F, R moves to lift it to the top.
      Repeat a simple alg until the cross is formed.
*/
static void makeWhiteCross(Cube &c, std::vector<std::string> &sol){
    int tries=0;
    while(!whiteCrossDone(c) && tries<25){
        // quick routine that often moves a white edge from bottom to top
        apply(c, sol, {"F","R","D","R'","F'"});
        tries++;
    }
}

/* --------------------- PHASE 2: WHITE CORNERS --------------------- */
/*
  Standard beginner corner insertion (Right / Left triggers):
    Right trigger:  R' D' R D
    Left  trigger:  L  D  L' D'
  We'll just keep doing these until all top is white.
*/
static void insertWhiteCorners(Cube &c, std::vector<std::string> &sol){
    int tries=0;
    while(!firstLayerDone(c) && tries<60){
        apply(c, sol, {"R'","D'","R","D"});
        apply(c, sol, {"L","D","L'","D'"});
        tries++;
    }
}

/* PHASE 3: SECOND LAYER EDGES */
/*
  Two basic algorithms:

  Edge goes to the right:
    U R U' R' U' F' U F

  Edge goes to the left:
    U' L' U L U F U' F'

  We just spam both with some U-turns to cycle pieces.
*/
static void solveSecondLayer(Cube &c, std::vector<std::string> &sol){
    int tries=0;
    while(!secondLayerDone(c) && tries<80){
        apply(c, sol, {"U","R","U'","R'","U'","F'","U","F"});
        apply(c, sol, {"U'","L'","U","L","U","F","U'","F'"});
        tries++;
    }
}

/* --------------------- PHASE 4: OLL --------------------- */
/*
  Two common OLL algs (make entire down face yellow):

    F R U R' U' F'           (edges)
    R U R' U R U2 R'         (corners)

  Repeat them until everything on D is yellow.
*/
static void OLL(Cube &c, std::vector<std::string> &sol){
    int tries=0;
    while(!OLL_Done(c) && tries<40){
        apply(c, sol, {"F","R","U","R'","U'","F'"});
        if(OLL_Done(c)) break;
        apply(c, sol, {"R","U","R'","U","R","U2","R'"});
        tries++;
    }
}

/* --------------------- PHASE 5: PLL --------------------- */
/*
  Two basic PLLs (move last layer pieces around):
    Ua perm: R U' R U R U R U' R' U' R2
    Ub perm: R2 U R U R' U' R' U' R' U R'
  We'll also spin the D face between tries to line things up.
*/
static void PLL(Cube &c, std::vector<std::string> &sol){
    int tries=0;
    while(!c.isSolved() && tries<50){
        apply(c, sol, {"R","U'","R","U","R","U","R","U'","R'","U'","R2"});
        if(c.isSolved()) break;
        apply(c, sol, {"R2","U","R","U","R'","U'","R'","U'","R'","U","R'"});
        if(c.isSolved()) break;
        apply(c, sol, {"D"}); // re-align
        tries++;
    }
}

// PUBLIC SOLVE

std::vector<std::string> SolverLBL::solve(const Cube &start){
    Cube cube = start;
    std::vector<std::string> sol;

    if(cube.isSolved()) return sol;

    makeWhiteCross(cube, sol);
    insertWhiteCorners(cube, sol);
    solveSecondLayer(cube, sol);
    OLL(cube, sol);
    PLL(cube, sol);

    return sol;
}

Solver* getLBLSolver(){ return new SolverLBL(); }
