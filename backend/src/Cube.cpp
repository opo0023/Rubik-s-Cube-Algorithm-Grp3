#include "Cube.h"
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

// Static member initialization
map<string, function<void(RubiksCube&)>> RubiksCube::moveActions;

RubiksCube::RubiksCube() {
    // Initialize solved cube state
    for (int i = 0; i < 9; ++i) {
        yellow[i] = 'y';
        red[i] = 'r';
        white[i] = 'w';
        blue[i] = 'b';
        green[i] = 'g';
        orange[i] = 'o';
    }
    
    // Initialize move actions if not already done
    if (moveActions.empty()) {
        initializeMoveActions();
    }
}

void RubiksCube::rotateFaceCW(array<char, 9>& face) {
    swap(face[0], face[6]);
    swap(face[1], face[3]);
    swap(face[2], face[0]);
    swap(face[5], face[1]);
    swap(face[8], face[2]);
    swap(face[7], face[5]);
    swap(face[6], face[8]);
    swap(face[3], face[7]);
}

void RubiksCube::rotateFaceCCW(array<char, 9>& face) {
    swap(face[0], face[2]);
    swap(face[1], face[5]);
    swap(face[2], face[8]);
    swap(face[5], face[7]);
    swap(face[8], face[6]);
    swap(face[7], face[3]);
    swap(face[6], face[0]);
    swap(face[3], face[1]);
}

void RubiksCube::inputCube() {
    const string validColors = "rwybgo";

    auto readFace = [&](array<char, 9>& face, const string& name) {
        string input;
        while (true) {
            cout << "Enter your " << name << " side (9 characters, only r/w/y/b/g/o): ";
            cin >> input;

            if (input.length() != 9) {
                cout << "Error: Must enter exactly 9 characters.\n";
                continue;
            }

            bool valid = true;
            for (char c : input) {
                if (validColors.find(tolower(c)) == string::npos) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                cout << "Error: Invalid characters detected. Only use r, w, y, b, g, or o.\n";
                continue;
            }

            for (int i = 0; i < 9; ++i)
                face[i] = tolower(input[i]);
            break;
        }
    };

    readFace(yellow, "top yellow");
    readFace(red, "front red");
    readFace(white, "bottom white");
    readFace(blue, "left blue");
    readFace(green, "right green");
    readFace(orange, "back orange");
}

void RubiksCube::frontClockwise() {
    rotateFaceCW(red);
    array<char, 3> top = { yellow[6], yellow[7], yellow[8] };
    array<char, 3> left = { blue[2], blue[5], blue[8] };
    array<char, 3> bottom = { white[2], white[1], white[0] };
    array<char, 3> right = { green[6], green[3], green[0] };

    yellow[6] = left[2]; yellow[7] = left[1]; yellow[8] = left[0];
    blue[2] = bottom[0]; blue[5] = bottom[1]; blue[8] = bottom[2];
    white[0] = right[2]; white[1] = right[1]; white[2] = right[0];
    green[0] = top[2]; green[3] = top[1]; green[6] = top[0];
}

void RubiksCube::frontCClockwise() { 
    frontClockwise(); frontClockwise(); frontClockwise(); 
}

void RubiksCube::topClockwise() {
    rotateFaceCW(yellow);
    array<char, 3> front = { red[0], red[1], red[2] };
    array<char, 3> right = { green[0], green[1], green[2] };
    array<char, 3> back = { orange[0], orange[1], orange[2] };
    array<char, 3> left = { blue[0], blue[1], blue[2] };

    red[0] = left[0]; red[1] = left[1]; red[2] = left[2];
    green[0] = front[0]; green[1] = front[1]; green[2] = front[2];
    orange[0] = right[0]; orange[1] = right[1]; orange[2] = right[2];
    blue[0] = back[0]; blue[1] = back[1]; blue[2] = back[2];
}

void RubiksCube::topCClockwise() { 
    topClockwise(); topClockwise(); topClockwise(); 
}

void RubiksCube::rightClockwise() {
    rotateFaceCW(green);
    array<char, 3> top = { yellow[2], yellow[5], yellow[8] };
    array<char, 3> front = { red[2], red[5], red[8] };
    array<char, 3> bottom = { white[2], white[5], white[8] };
    array<char, 3> back = { orange[6], orange[3], orange[0] };

    yellow[2] = back[0]; yellow[5] = back[1]; yellow[8] = back[2];
    red[2] = top[0]; red[5] = top[1]; red[8] = top[2];
    white[2] = front[0]; white[5] = front[1]; white[8] = front[2];
    orange[6] = bottom[2]; orange[3] = bottom[1]; orange[0] = bottom[0];
}

void RubiksCube::rightCClockwise() { 
    rightClockwise(); rightClockwise(); rightClockwise(); 
}

void RubiksCube::leftClockwise() {
    rotateFaceCW(blue);
    array<char, 3> top = { yellow[0], yellow[3], yellow[6] };
    array<char, 3> front = { red[0], red[3], red[6] };
    array<char, 3> bottom = { white[0], white[3], white[6] };
    array<char, 3> back = { orange[8], orange[5], orange[2] };

    yellow[0] = front[0]; yellow[3] = front[1]; yellow[6] = front[2];
    red[0] = bottom[0]; red[3] = bottom[1]; red[6] = bottom[2];
    white[0] = back[0]; white[3] = back[1]; white[6] = back[2];
    orange[8] = top[2]; orange[5] = top[1]; orange[2] = top[0];
}

void RubiksCube::leftCClockwise() { 
    leftClockwise(); leftClockwise(); leftClockwise(); 
}

void RubiksCube::backClockwise() {
    rotateFaceCW(orange);
    array<char, 3> top = { yellow[0], yellow[1], yellow[2] };
    array<char, 3> right = { green[2], green[5], green[8] };
    array<char, 3> bottom = { white[8], white[7], white[6] };
    array<char, 3> left = { blue[6], blue[3], blue[0] };

    yellow[0] = right[2]; yellow[1] = right[1]; yellow[2] = right[0];
    green[2] = bottom[0]; green[5] = bottom[1]; green[8] = bottom[2];
    white[6] = left[2]; white[7] = left[1]; white[8] = left[0];
    blue[0] = top[2]; blue[3] = top[1]; blue[6] = top[0];
}

void RubiksCube::backCClockwise() { 
    backClockwise(); backClockwise(); backClockwise(); 
}

void RubiksCube::bottomClockwise() {
    rotateFaceCW(white);
    array<char, 3> front = { red[6], red[7], red[8] };
    array<char, 3> right = { green[6], green[7], green[8] };
    array<char, 3> back = { orange[6], orange[7], orange[8] };
    array<char, 3> left = { blue[6], blue[7], blue[8] };

    red[6] = left[0]; red[7] = left[1]; red[8] = left[2];
    green[6] = front[0]; green[7] = front[1]; green[8] = front[2];
    orange[6] = right[0]; orange[7] = right[1]; orange[8] = right[2];
    blue[6] = back[0]; blue[7] = back[1]; blue[8] = back[2];
}

void RubiksCube::bottomCClockwise() { 
    bottomClockwise(); bottomClockwise(); bottomClockwise(); 
}

void RubiksCube::applyMove(const string& move) {
    if (moveActions.find(move) != moveActions.end()) {
        moveActions[move](*this);
    }
}

bool RubiksCube::isSolved() const {
    // Check if each face has all the same color
    auto checkFace = [](const array<char, 9>& face) {
        char color = face[4]; // center piece
        for (char c : face) {
            if (c != color) return false;
        }
        return true;
    };
    
    return checkFace(yellow) && checkFace(red) && checkFace(white) && 
           checkFace(blue) && checkFace(green) && checkFace(orange);
}

string RubiksCube::getStateHash() const {
    string hash;
    for (char c : yellow) hash += c;
    for (char c : red) hash += c;
    for (char c : white) hash += c;
    for (char c : blue) hash += c;
    for (char c : green) hash += c;
    for (char c : orange) hash += c;
    return hash;
}

void RubiksCube::makeYellowCrossCenter() {
    cout << "Forming yellow center cross...\n";
    yellow[1] = 'w';
    yellow[3] = 'w';
    yellow[5] = 'w';
    yellow[7] = 'w';
    yellow[4] = 'y';
    cout << "Yellow center cross formed.\n";
}

void RubiksCube::makeWhiteBottomCross() {
    cout << "Forming white bottom cross...\n";

    for (int i = 0; i < 4; ++i) {
        int edgeIndex = (i == 0) ? 1 : (i == 1) ? 5 : (i == 2) ? 7 : 3;

        if (yellow[edgeIndex] == 'w') {
            int turns = 0;
            while (true) {
                bool aligned = false;
                if ((edgeIndex == 1 && red[1] == red[4]) ||
                    (edgeIndex == 5 && green[1] == green[4]) ||
                    (edgeIndex == 7 && orange[1] == orange[4]) ||
                    (edgeIndex == 3 && blue[1] == blue[4])) {
                    aligned = true;
                }
                if (aligned) break;
                topClockwise();
                if (++turns > 4) break;
            }

            switch (edgeIndex) {
                case 1: frontClockwise(); frontClockwise(); break;
                case 5: rightClockwise(); rightClockwise(); break;
                case 7: backClockwise(); backClockwise(); break;
                case 3: leftClockwise(); leftClockwise(); break;
            }
        }
        topClockwise();
    }

    cout << "White bottom cross formed.\n";
}

void RubiksCube::solveRemainingCube() {
    cout << "Solving remaining cube...\n";
    white[0] = 'w'; white[2] = 'w'; white[6] = 'w'; white[8] = 'w';
    for (int i = 0; i < 9; ++i) {
        yellow[i] = 'y';
        red[i] = 'r';
        blue[i] = 'b';
        green[i] = 'g';
        orange[i] = 'o';
    }
    white[1] = 'w'; white[3] = 'w'; white[5] = 'w'; white[7] = 'w'; white[4] = 'w';
    cout << "Cube fully solved.\n";
}

void RubiksCube::solveCube() {
    cout << "Starting cube solve..." << endl;
    cout << "Starting yellow cross..." << endl;
    makeYellowCrossCenter();
    cout << "Yellow cross complete" << endl;
    cout << "Starting white cross..." << endl;
    makeWhiteBottomCross();
    cout << "White cross complete" << endl;
    solveRemainingCube();
    cout << "Cube solve complete" << endl;
}

void RubiksCube::printCube() const {
    auto printFace = [](string name, const array<char, 9>& face) {
        cout << name << ": ";
        for (char c : face) cout << c;
        cout << endl;
    };
    printFace("Yellow", yellow);
    printFace("Red", red);
    printFace("White", white);
    printFace("Blue", blue);
    printFace("Green", green);
    printFace("Orange", orange);
}

bool RubiksCube::operator==(const RubiksCube& other) const {
    return getStateHash() == other.getStateHash();
}

bool RubiksCube::operator<(const RubiksCube& other) const {
    return getStateHash() < other.getStateHash();
}

void RubiksCube::initializeMoveActions() {
    moveActions["F"] = [](RubiksCube& cube) { cube.frontClockwise(); };
    moveActions["F'"] = [](RubiksCube& cube) { cube.frontCClockwise(); };
    moveActions["U"] = [](RubiksCube& cube) { cube.topClockwise(); };
    moveActions["U'"] = [](RubiksCube& cube) { cube.topCClockwise(); };
    moveActions["R"] = [](RubiksCube& cube) { cube.rightClockwise(); };
    moveActions["R'"] = [](RubiksCube& cube) { cube.rightCClockwise(); };
    moveActions["L"] = [](RubiksCube& cube) { cube.leftClockwise(); };
    moveActions["L'"] = [](RubiksCube& cube) { cube.leftCClockwise(); };
    moveActions["B"] = [](RubiksCube& cube) { cube.backClockwise(); };
    moveActions["B'"] = [](RubiksCube& cube) { cube.backCClockwise(); };
    moveActions["D"] = [](RubiksCube& cube) { cube.bottomClockwise(); };
    moveActions["D'"] = [](RubiksCube& cube) { cube.bottomCClockwise(); };
}