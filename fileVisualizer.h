#include "visualizer.h"
#include "fstream"

#ifndef FILEVISUALIZER_H
#define FILEVISUALIZER_H

class FileVisualizer : public Visualizer {
public:
    std::fstream fileStream;
    FileVisualizer (std::string fileName);
    void showState(const intMatrix &state);
private:
    std::string stateToString(const intMatrix &state);
};

#endif //FILEVISUALIZER_H