#include "cell.h"
#include <iostream>

using namespace std;

Cell::Cell(size_t r, size_t c): r(r), c(c) {}

void Cell::setPiece(Colour colour) {
    this->colour = colour;
    this->setState(State{StateType::NewPiece, colour, Direction::NW});
    this->notifyObservers();
}

void Cell::toggle() {
    this->colour = colour == Colour::White? Colour::Black : Colour::White;
}

Direction getD(int i, int j) {
    Direction d;
    if (i == -1 && j == -1) {
        d = Direction::NW;
    }
    if (i == -1 && j == 0) {
        d = Direction::N;
    }
    if (i == -1 && j == 1) {
        d = Direction::NE;
    }
    if (i == 0 && j == 1) {
        d = Direction::E;
    }
    if (i == 1 && j == 1) {
        d = Direction::SE;
    }
    if (i == 1 && j == 0) {
        d = Direction::S;
    }
    if (i == 1 && j == -1) {
        d = Direction::SW;
    }
    if (i == 0 && j == -1) {
        d = Direction::W;
    }
    return d;
}

void Cell::notify(Subject<Info, State> &whoFrom) {
    State s = whoFrom.getState();
    Info info = whoFrom.getInfo();
    int i = r - info.row;
    int j = c - info.col;
    if (s.type == StateType::NewPiece) {
        if (colour == Colour::NoColour || colour == s.colour) return;
        Direction d = getD(i, j);
        setState(State{StateType::Relay, colour, d});
        notifyObservers();
        return;
    }
    if (s.type == StateType::Relay) {
        Direction d = getD(i, j);
        if (d != s.direction || colour == Colour::NoColour) return;
        if (s.colour == colour) {
            setState(s);
            notifyObservers();
            return;
        }
        d = getD(i * -1, j * -1);
        setState(State{StateType::Reply, colour, d});
        notifyObservers();
        return;
    }
    if (s.type == StateType::Reply) {
        Direction d = getD(i, j);
        if (d != s.direction || colour == Colour::NoColour) return;
        if (getState().type == StateType::NewPiece) {
            return;
        }
        toggle();
        setState(s);
        notifyObservers();
        return;
    }
}

Info Cell::getInfo() const {
    return Info{r, c, colour};
}


