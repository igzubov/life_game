#include <iostream>
#include "world.h"
#include "fileVisualizer.h"
#include <vector>
#include <fstream>
#include <unistd.h>


using intMatrix = std::vector<std::vector<int>>;
size_t calcStateHash(const intMatrix &state);

class LifeGame {
public:
    LifeGame(std::shared_ptr<intMatrix> map) : world(map) {
        vis = new FileVisualizer("gameOutput.txt");
    }

    void play() {
        while (true) {
            vis->showState(world.getCurrState());
            std::cout << calcStateHash(world.getCurrState()) << std::endl;
            usleep(10000000);
            world.liveOneGen();
        }
    }

private:
    World world;
    Visualizer *vis;
};


// read length, width and correct matrix of points
std::shared_ptr<intMatrix> readInitialWorld(const std::string fileName) {
    std::fstream pointsStream(fileName, std::ios_base::in);
    int length = 0;
    int width = 0;
    pointsStream >> length >> width;
    // check if at least 2 points
    if (length < 2 || width < 2) {
        std::string errorMsg("Size of matrix " + std::to_string(length) + " " + std::to_string(width) +
                             " is incorrect, need at least 2x2 points");
        throw std::invalid_argument(errorMsg);
    }
    std::shared_ptr<intMatrix> map = std::make_shared<intMatrix>(length, std::vector<int>(width, 0));
    int val = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            pointsStream >> val;
            map->at(i).at(j) = val;
        }
    }
    return map;
}

size_t calcStateHash(const intMatrix &state) {
    size_t seedOuter = state.size();
    for(int i = 0; i < state.size(); i++) {
        size_t seedInner = state.at(0).size();
        for (int j = 0; j < state.at(0).size(); j++) {
            seedInner ^= state.at(i).at(j) + 0x9e3779b9 + (seedInner << 6) + (seedInner >> 2);
        }
        seedOuter ^= seedInner + 0x9e3779b9 + (seedOuter << 6) + (seedOuter >> 2);
    }
    return seedOuter;
}

int main() {
    auto map = readInitialWorld("points.txt");
    LifeGame *lf = new LifeGame(map);
    lf->play();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}