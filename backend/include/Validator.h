#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include "Cube.h"

/*
  Functions for reading a 54-character facelet string and for checking whether
  a Cube state could occur on a real, mechanically legal 3×3 cube.

  parseCubeFromString:
      Input  : 54-character string ("WWWWWWWWW...BBBBBBBBB").
      Output : Cube object (filled state) and an error message if something fails.
      Checks basic constraints and then calls isPhysicallyValid.

  isPhysicallyValid:
      1) Exactly 9 stickers of each color (W,R,G,Y,O,B).
      2) Center stickers match the fixed color scheme used by this project
         (U=W, R=R, F=G, D=Y, L=O, B=B).
      3) Sum of corner orientations modulo 3 equals 0.
      4) Sum of edge orientations modulo 2 equals 0.
      5) Parity of corner permutation equals parity of edge permutation
         ie if one is odd and the other is even, then invalid
*/

bool parseCubeFromString(const std::string& s54, Cube& out, std::string& errMsg);
bool isPhysicallyValid(const Cube& c, std::string& errMsg);

#endif // VALIDATOR_H
