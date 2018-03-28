#include "grid.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"

using namespace std;

void Grid::setObserver(Observer<Info, State> *ob) {
    this->ob = ob;
}

Grid::~Grid() {
    delete td;
    delete ob;
}

bool Grid::isFull() const {
    int n = theGrid.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (theGrid[i][j].getInfo().colour == Colour::NoColour) {
                return 0;
            }
        }
    }
    return 1;
}

Colour Grid::whoWon() const {
    int w = 0;
    int b = 0;
    int n = theGrid.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (theGrid[i][j].getInfo().colour == Colour::White) {
                w++;
            }
            if (theGrid[i][j].getInfo().colour == Colour::Black) {
                b++;
            }
        }
    }
    return w > b ? Colour::White : Colour::Black;
}

int valid(int r, int c, int n) {
    return r >= 0 && r < n && c >= 0 && c < n;
}

void Grid::init(size_t n) {
    td = new TextDisplay(n);
    ob = new GraphicsDisplay(n);

    for (int i = 0; i < n; ++i) {
        vector<Cell> temp;
        for (int j = 0; j < n; ++j) {
            //here
            Cell cell(i, j);
            cell.attach(td);
            cell.attach(ob);
            temp.push_back(cell);
        }
        theGrid.push_back(temp);
    }

    theGrid[n/2-1][n/2-1].setPiece(Colour::Black);
    theGrid[n/2-1][n/2].setPiece(Colour::White);
    theGrid[n/2][n/2-1].setPiece(Colour::White);
    theGrid[n/2][n/2].setPiece(Colour::Black);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int x = -1; x < 2; ++x) {
                for (int y = -1; y < 2; ++y) {
                    if (x == 0 && y == 0) continue;
                    int r = i + x;
                    int c = j + y;
                    if (valid(r, c, n)) {
                        theGrid[i][j].attach(&(theGrid[r][c]));
                    }
                }
            }
        }
    }
}

void Grid::setPiece(size_t r, size_t c, Colour colour) {
    if (theGrid[r][c].getInfo().colour != Colour::NoColour) return;
    theGrid[r][c].setPiece(colour);
}

void Grid::toggle(size_t r, size_t c) {
    theGrid[r][c].toggle();
}

ostream &operator<<(ostream &out, const Grid &g) {
    out << *(g.td);
    //g.ob->print();
    return out;
}
