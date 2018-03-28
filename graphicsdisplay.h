#ifndef __GD_H__
#define __GD_H__

#include "window.h"
#include "info.h"
#include "state.h"
#include "subject.h"
#include "observer.h"
class GraphicsDisplay : public Observer<Info, State> {

    std::vector<std::vector<char>> gd;
    int size;
    double edge;
    double fill = 1;
    Xwindow *xw;

    public:
    GraphicsDisplay(int n);
    void notify(Subject<Info, State> &a) override;

    ~GraphicsDisplay();

};

#endif
