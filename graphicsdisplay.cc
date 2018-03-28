#include "graphicsdisplay.h"
#include "subject.h"
#include "state.h"
#include "window.h"

using namespace std;

GraphicsDisplay::GraphicsDisplay(int n) {
    xw = new Xwindow(500, 500);
    xw->fillRectangle(0, 0, 500, 500, Xwindow::Blue);
    edge = (500 - (n + 1) * fill) / n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int x = i * edge + (i + 1) * fill;
            int y = j * edge + (j + 1) * fill;
            xw->fillRectangle(x, y, edge, edge, Xwindow::Red);
        }
    }

}

void GraphicsDisplay::notify(Subject<Info, State> &a) {
    Info info = a.getInfo();
    int i = info.col;
    int j = info.row;
    int x = i * edge + (i + 1) * fill;
    int y = j * edge + (j + 1) * fill;
    if (info.colour == Colour::White) {
        xw->fillRectangle(x, y, edge, edge, Xwindow::White);
    }
    if (info.colour == Colour::Black) {
        xw->fillRectangle(x, y, edge, edge, Xwindow::Black);
    }

}

GraphicsDisplay::~GraphicsDisplay() {
    delete xw;
}


