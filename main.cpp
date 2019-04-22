#include <iostream>
#include "world.h"
#include "fileVisualizer.h"
#include <vector>
#include <fstream>
#include <unistd.h>


using intMatrix = std::vector<std::vector<int>>;

// delay between generations in microsedonds
const int generationDelay = 2000000;

size_t calcMatrixHash(const intMatrix &state);

class LifeGame {
public:
    LifeGame(std::shared_ptr<intMatrix> map, const int repeatStep = 2) : world(map), lastStates(repeatStep+1), lastStatesIndex(-1), genCount(0) {
        vis = new FileVisualizer("gameOutput.txt");
    }

    void play() {
        bool cycleRepeat = false;
        bool consRepeat = false;
        size_t stateHash = 0;
        while (!consRepeat && !cycleRepeat) {
            // visualize
            vis->showState(world.getCurrState());

            // calc hash for current world state & check end conditions
            stateHash = calcMatrixHash(world.getCurrState());
            saveState(stateHash);
            cycleRepeat = isStateRepeated(stateHash, lastStates.size()-1);
            consRepeat = isStateRepeated(stateHash, 1);

            usleep(generationDelay);
            world.liveOneGen();
            genCount++;
        }
    }

private:
    World world;
    Visualizer *vis;
    std::vector<size_t> lastStates;
    int lastStatesIndex;
    int genCount;

    bool isStateRepeated(size_t stateHash, int step) {
        int prevIndex = lastStatesIndex - step;
        if (prevIndex < 0) {
            prevIndex = lastStates.size() + prevIndex;
        }
        return stateHash == lastStates.at(prevIndex);
    }

    void saveState(size_t stateHash) {
        lastStatesIndex = (lastStatesIndex+1) % lastStates.size();
        lastStates.at(lastStatesIndex) = stateHash;
    }
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

size_t calcMatrixHash(const intMatrix &state) {
    size_t seedOuter = state.size();
    for (int i = 0; i < state.size(); i++) {
        size_t seedInner = state.at(0).size();
        for (int j = 0; j < state.at(0).size(); j++) {
            seedInner ^= state.at(i).at(j) + 0x9e3779b9 + (seedInner << 6) + (seedInner >> 2);
        }
        seedOuter ^= seedInner + 0x9e3779b9 + (seedOuter << 6) + (seedOuter >> 2);
    }
    return seedOuter;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        std::string fileName(argv[1]);
        try {
            auto map = readInitialWorld(fileName);
            LifeGame *lf = new LifeGame(map);
            lf->play();
            std::cout << "The end" << std::endl;

        }
        catch (std::invalid_argument &e) {
            std::cout << e.what();
            exit(1);
        }
    } else {
        std::cout << "No file with points was specified, exiting.." << std::endl;
    }
    return 0;
}