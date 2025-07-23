// Validator.cpp
// Reads a 54-character sticker string, reorders faces automatically by center
// (faces may arrive in any order), then checks if the cube is physically valid
// (color counts, fixed centers, corner/edge orientation sums, and permutation parity).

#include "Validator.h"
#include <unordered_map>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include <cctype>

// ---------- Forward declarations ----------
static bool permutationParityEven(const std::vector<int>& p);
static int  modSum(const std::vector<int>& v, int mod);

static bool buildPieces(const Cube& c,
                        std::vector<int>& cornerPerm,
                        std::vector<int>& cornerOri,
                        std::vector<int>& edgePerm,
                        std::vector<int>& edgeOri,
                        std::string& errMsg);

static bool reorderByCenters(const std::string& in,
                             std::string& out,
                             std::string& errMsg);

// ---------- Public API ----------

bool parseCubeFromString(const std::string& s54, Cube& out, std::string& errMsg)
{
    // 1) Reorder faces based on their center stickers so input order is irrelevant.
    std::string fixed;
    if (!reorderByCenters(s54, fixed, errMsg)) {
        return false;                       // errMsg already populated
    }

    // 2) Sanity checks
    if (fixed.size() != 54) {
        errMsg = "Internal error: reordered string is not 54 characters.";
        return false;
    }
    const std::string allowed = "WRGYOB";
    for (char ch : fixed) {
        if (allowed.find(ch) == std::string::npos) {
            errMsg = "Illegal color detected after reorder (allowed: W R G Y O B).";
            return false;
        }
    }

    // 3) Construct Cube::State in the canonical order U,R,F,D,L,B
    Cube::State st{};
    for (int f = 0; f < 6; ++f)
        for (int i = 0; i < 9; ++i)
            st[f][i] = fixed[f*9 + i];

    out = Cube(st);

    // 4) Full legality check (orientation and parity constraints)
    return isPhysicallyValid(out, errMsg);
}

bool isPhysicallyValid(const Cube& c, std::string& errMsg)
{
    // 1) Color counts: exactly 9 of each sticker color
    std::unordered_map<char,int> counts;
    counts.reserve(6);
    const auto& st = c.getState();
    for (int f = 0; f < 6; ++f)
        for (int i = 0; i < 9; ++i)
            counts[st[f][i]]++;

    for (char col : {'W','R','G','Y','O','B'}) {
        if (counts[col] != 9) {
            std::ostringstream oss;
            oss << "Color '" << col << "' count = " << counts[col]
                << " (expected 9).";
            errMsg = oss.str();
            return false;
        }
    }

    // 2) Center stickers must match the fixed scheme: U=W, R=R, F=G, D=Y, L=O, B=B
    static const std::array<char,6> schema = {'W','R','G','Y','O','B'};
    for (int f = 0; f < 6; ++f) {
        if (st[f][4] != schema[f]) {
            std::ostringstream oss;
            oss << "Center mismatch on face " << f
                << ": got '" << st[f][4] << "', expected '" << schema[f] << "'.";
            errMsg = oss.str();
            return false;
        }
    }

    // 3) Build permutation and orientation arrays
    std::vector<int> cornerPerm(8), cornerOri(8);
    std::vector<int> edgePerm(12),   edgeOri(12);
    if (!buildPieces(c, cornerPerm, cornerOri, edgePerm, edgeOri, errMsg))
        return false;

    // Corner orientation sum must be divisible by 3
    if (modSum(cornerOri, 3) != 0) {
        errMsg = "Corner orientation sum % 3 != 0 (impossible single-corner twist).";
        return false;
    }
    // Edge orientation sum must be divisible by 2
    if (modSum(edgeOri, 2) != 0) {
        errMsg = "Edge orientation sum % 2 != 0 (impossible single-edge flip).";
        return false;
    }

    // Corner and edge permutation parity must match
    bool cornersEven = permutationParityEven(cornerPerm);
    bool edgesEven   = permutationParityEven(edgePerm);
    if (cornersEven != edgesEven) {
        errMsg = "Corner and edge permutation parities differ (impossible swap).";
        return false;
    }

    errMsg.clear();
    return true;
}

// ---------- Auto-reorder faces by center color ----------

static bool reorderByCenters(const std::string& in,
                             std::string& out,
                             std::string& errMsg)
{
    if (in.size() != 54) {
        errMsg = "Input must be exactly 54 characters long.";
        return false;
    }

    // Split into 6 blocks of 9
    std::array<std::string,6> blocks;
    for (int f = 0; f < 6; ++f) blocks[f] = in.substr(f*9, 9);

    // Target order and required centers:
    // U,R,F,D,L,B -> W,R,G,Y,O,B
    std::unordered_map<char,int> need = {
        {'W',0}, {'R',1}, {'G',2}, {'Y',3}, {'O',4}, {'B',5}
    };

    std::array<std::string,6> ordered{};
    for (int f = 0; f < 6; ++f) {
        if (blocks[f].size() != 9) {
            errMsg = "One face block is not 9 characters.";
            return false;
        }
        // Normalize to uppercase
        for (char &ch : blocks[f]) ch = std::toupper(ch);

        char center = blocks[f][4];
        auto it = need.find(center);
        if (it == need.end()) {
            errMsg = "Unknown center color '" + std::string(1,center) +
                     "'. Allowed: W,R,G,Y,O,B.";
            return false;
        }
        int tgt = it->second;
        if (!ordered[tgt].empty()) {
            errMsg = "Duplicate center color '" + std::string(1,center) + "'.";
            return false;
        }
        ordered[tgt] = blocks[f];
    }

    // Ensure all 6 faces assigned
    for (int i = 0; i < 6; ++i) {
        if (ordered[i].empty()) {
            errMsg = "Missing face with center " + std::string(1, "WRGYOB"[i]) + ".";
            return false;
        }
    }

    // Concatenate in the correct order
    out.clear();
    out.reserve(54);
    for (int i = 0; i < 6; ++i) out += ordered[i];
    return true;
}

// ---------- Internal helpers for piece extraction ----------

static inline int gidx(int face, int offset) { return face*9 + offset; }

// Corner indices used here (UFR, URB, UBL, ULF, DFR, DRB, DBL, DLF)
static const int CORNERS[8][3] = {
    { gidx(0,2), gidx(1,0), gidx(2,2) }, // UFR
    { gidx(0,8), gidx(1,2), gidx(5,0) }, // URB
    { gidx(0,6), gidx(5,2), gidx(4,0) }, // UBL
    { gidx(0,0), gidx(4,2), gidx(2,0) }, // ULF
    { gidx(3,2), gidx(2,8), gidx(1,6) }, // DFR
    { gidx(3,8), gidx(1,8), gidx(5,6) }, // DRB
    { gidx(3,6), gidx(5,8), gidx(4,6) }, // DBL
    { gidx(3,0), gidx(4,8), gidx(2,6) }  // DLF
};

// Edge indices (UF, UR, UB, UL, FR, BR, BL, FL, DF, DR, DB, DL)
static const int EDGES[12][2] = {
    { gidx(0,5), gidx(2,1) }, // UF
    { gidx(0,7), gidx(1,1) }, // UR
    { gidx(0,3), gidx(5,1) }, // UB
    { gidx(0,1), gidx(4,1) }, // UL
    { gidx(2,5), gidx(1,3) }, // FR
    { gidx(5,3), gidx(1,5) }, // BR
    { gidx(5,5), gidx(4,3) }, // BL
    { gidx(2,3), gidx(4,5) }, // FL
    { gidx(3,5), gidx(2,7) }, // DF
    { gidx(3,7), gidx(1,7) }, // DR
    { gidx(3,3), gidx(5,7) }, // DB
    { gidx(3,1), gidx(4,7) }  // DL
};

// Solved piece color sets
static const std::array<std::array<char,3>,8> SOLVED_CORNERS = {{
    {'W','R','G'}, {'W','R','B'}, {'W','B','O'}, {'W','O','G'},
    {'Y','G','R'}, {'Y','R','B'}, {'Y','B','O'}, {'Y','O','G'}
}};
static const std::array<std::array<char,2>,12> SOLVED_EDGES = {{
    {'W','G'}, {'W','R'}, {'W','B'}, {'W','O'},
    {'G','R'}, {'B','R'}, {'B','O'}, {'G','O'},
    {'Y','G'}, {'Y','R'}, {'Y','B'}, {'Y','O'}
}};

// Corner orientation: 0 if W/Y sticker is on U/D; 1 if on R/L; 2 if on F/B
static int cornerOrientation(char c0, char c1, char c2, int pieceIdx)
{
    std::array<char,3> cols = {c0,c1,c2};
    int udPos = -1;
    for (int i = 0; i < 3; ++i)
        if (cols[i] == 'W' || cols[i] == 'Y') { udPos = i; break; }

    int faceUD = CORNERS[pieceIdx][udPos] / 9; // 0..5
    if (faceUD == 0 || faceUD == 3) return 0;
    if (faceUD == 1 || faceUD == 4) return 1;
    return 2;
}

// Edge orientation: simple scheme described in comments
static int edgeOrientation(char a, char b, int solvedIdx, int idxA, int idxB)
{
    int faceA = idxA / 9;
    int faceB = idxB / 9;

    if ((a == 'W' || a == 'Y') && (faceA == 0 || faceA == 3)) return 0;
    if ((b == 'W' || b == 'Y') && (faceB == 0 || faceB == 3)) return 0;

    if (solvedIdx >= 4 && solvedIdx <= 7) { // middle layer edges
        if ((a == 'G' || a == 'B') && (faceA == 2 || faceA == 5)) return 0;
        if ((b == 'G' || b == 'B') && (faceB == 2 || faceB == 5)) return 0;
        return 1;
    }
    return 1;
}

static int solvedCornerIndex(char a, char b, char c)
{
    std::array<char,3> in = {a,b,c};
    std::sort(in.begin(), in.end());
    for (int i = 0; i < 8; ++i) {
        auto ref = SOLVED_CORNERS[i];
        std::sort(ref.begin(), ref.end());
        if (ref == in) return i;
    }
    return -1;
}

static int solvedEdgeIndex(char a, char b)
{
    std::array<char,2> in = {a,b};
    std::sort(in.begin(), in.end());
    for (int i = 0; i < 12; ++i) {
        auto ref = SOLVED_EDGES[i];
        std::sort(ref.begin(), ref.end());
        if (ref == in) return i;
    }
    return -1;
}

static bool buildPieces(const Cube& c,
                        std::vector<int>& cornerPerm,
                        std::vector<int>& cornerOri,
                        std::vector<int>& edgePerm,
                        std::vector<int>& edgeOri,
                        std::string& errMsg)
{
    const auto& st = c.getState();

    // Corners
    for (int i = 0; i < 8; ++i) {
        int s0 = CORNERS[i][0], s1 = CORNERS[i][1], s2 = CORNERS[i][2];
        char c0 = st[s0/9][s0%9];
        char c1 = st[s1/9][s1%9];
        char c2 = st[s2/9][s2%9];

        int solvedIdx = solvedCornerIndex(c0,c1,c2);
        if (solvedIdx < 0) {
            errMsg = "Corner colors do not match any real corner cubie.";
            return false;
        }
        cornerPerm[i] = solvedIdx;
        cornerOri[i]  = cornerOrientation(c0,c1,c2,i);
    }

    // Edges
    for (int i = 0; i < 12; ++i) {
        int s0 = EDGES[i][0], s1 = EDGES[i][1];
        char a = st[s0/9][s0%9];
        char b = st[s1/9][s1%9];

        int solvedIdx = solvedEdgeIndex(a,b);
        if (solvedIdx < 0) {
            errMsg = "Edge colors do not match any real edge cubie.";
            return false;
        }
        edgePerm[i] = solvedIdx;
        edgeOri[i]  = edgeOrientation(a,b,solvedIdx,s0,s1);
    }

    return true;
}

// ---------- Generic math helpers ----------

static int modSum(const std::vector<int>& v, int mod)
{
    int sum = 0;
    for (int x : v) sum += x;
    return sum % mod;
}

// Returns true if permutation parity is even.
static bool permutationParityEven(const std::vector<int>& p)
{
    std::vector<bool> vis(p.size(), false);
    int swaps = 0;

    for (size_t i = 0; i < p.size(); ++i) {
        if (vis[i]) continue;
        int cycleLen = 0;
        int j = static_cast<int>(i);
        while (!vis[j]) {
            vis[j] = true;
            j = p[j];
            ++cycleLen;
        }
        if (cycleLen > 1) swaps += cycleLen - 1;
    }
    return (swaps % 2) == 0;
}
