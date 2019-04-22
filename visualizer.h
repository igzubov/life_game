#include "vector"

#ifndef VISUALIZER_H
#define VISUALIZER_H

using intMatrix = std::vector<std::vector<int>>;

class Visualizer {
public:
    virtual void showState(const intMatrix &state) = 0;
};

#endif //VISUALIZER_H