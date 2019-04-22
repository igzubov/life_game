#include "world.h"


World::World(const std::shared_ptr<intMatrix> map) : cntrAlive(0), cntrDead(0) {
    length = map->size();
    width = length > 0 ? map->at(0).size() : 0;

    currMap = map;
    newMap = std::make_shared<intMatrix>(length, std::vector<int>(width, 0));
}

intMatrix World::getCurrState() {
    return *currMap;
}

// update all cells
void World::liveOneGen() {
    int locAliveCnt = 0;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            locAliveCnt = countLocalAlive(i, j);
            if (currMap->at(i).at(j) && (locAliveCnt == 2 || locAliveCnt == 3)) {
                newMap->at(i).at(j) = 1;
            }
            else if (!currMap->at(i).at(j) && locAliveCnt == 3) {
                newMap->at(i).at(j) = 1;
            }
            else {
                newMap->at(i).at(j) = 0;
            }
        }
    }
    currMap.swap(newMap);
}

int World::getLength() {
    return length;
}

int World::getWidth() {
    return width;
}

// count all alive cells around given cell index
int World::countLocalAlive(int i, int j) {
    int count = 0;
    count += i > 0 ? currMap->at(i - 1).at(j) : 0;
    count += (i > 0 && j < width - 1) ? currMap->at(i - 1).at(j + 1) : 0;
    count += j < width - 1 ? currMap->at(i).at(j + 1) : currMap->at(i).at(0);
    count += (i < length - 1 && j < width - 1) ? currMap->at(i + 1).at(j + 1) : 0;
    count += i < length - 1 ? currMap->at(i + 1).at(j) : currMap->at(0).at(j);
    count += (i < length - 1 && j > 0) ? currMap->at(i + 1).at(j - 1) : 0;
    count += j > 0 ? currMap->at(i).at(j - 1) : currMap->at(i).at(length - 1);
    count += (i > 0 && j > 0) ? currMap->at(i - 1).at(j - 1) : 0;

    return count;
}