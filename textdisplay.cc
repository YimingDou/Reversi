#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "subject.h"

using namespace std;

TextDisplay::TextDisplay(int n):gridSize(n) {
    for (int i = 0; i < n; ++i) {
        vector<char> temp;
        for (int j = 0; j < n; ++j) {
            temp.push_back('-');
        }
        theDisplay.push_back(temp);
    }
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    State s = whoNotified.getState();
    Info info = whoNotified.getInfo();
    int r = info.row;
    int c = info.col;
    Colour colour = info.colour;
    theDisplay[r][c] = colour == Colour::White ? 'W' : 'B';
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    for (int i = 0; i < td.gridSize; ++i) {
        for (int j = 0; j < td.gridSize; ++j) {
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    return out;
}



