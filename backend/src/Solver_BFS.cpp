#include "Solver_BFS.h"
#include "Cube.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

/*
BFS strategy:
  - Node = cube state
  - Edge = legal move
  - Use queue for frontier, unordered_set for visited hash strings
  - Store parent hash + move for path reconstruction
  - Stop when isSolved() or maxDepth exceeded
*/

static const std::vector<std::string> ALL_MOVES = {
    "U","U'","U2","R","R'","R2","F","F'","F2",
    "D","D'","D2","L","L'","L2","B","B'","B2"
};

SolverBFS::SolverBFS(std::size_t maxDepth) : maxDepth_(maxDepth) {}

std::vector<std::string> SolverBFS::solve(const Cube &start){
    if(start.isSolved()) return {}; // already solved

    struct NodeInfo{
        std::string parentHash;
        std::string moveUsed; // move leading to this state
        std::size_t depth;
    };

    std::queue<Cube> q;
    std::unordered_map<std::string, NodeInfo> back;
    std::unordered_set<std::string> visited;

    std::string h0 = start.hash();
    q.push(start);
    visited.insert(h0);
    back[h0] = {"","",0};

    while(!q.empty()){
        Cube cur = q.front(); q.pop();
        const std::string curHash = cur.hash();
        std::size_t depth = back[curHash].depth;

        if(depth >= maxDepth_) continue;

        for(const auto &mv : ALL_MOVES){
            Cube nxt = cur;
            nxt.move(mv);
            std::string nh = nxt.hash();
            if(visited.count(nh)) continue;

            visited.insert(nh);
            back[nh] = {curHash, mv, depth + 1};

            if(nxt.isSolved()){
                // reconstruct path
                std::vector<std::string> path;
                std::string h = nh;
                while(h != h0){
                    const auto &info = back[h];
                    path.push_back(info.moveUsed);
                    h = info.parentHash;
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            q.push(nxt);
        }
    }
    return {}; // not found within depth limit
}

Solver* getBFSSolver(std::size_t maxDepth){
    return new SolverBFS(maxDepth);
}
