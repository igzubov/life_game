#include <asio/detail/shared_ptr.hpp>
#include "vector"

#ifndef WORLD_H
#define WORLD_H

using intMatrix = std::vector<std::vector<int>>;

class World {
public:
    int cntrAlive;
    int cntrDead;

    World(std::shared_ptr<intMatrix> map);
    intMatrix getCurrState();
    void liveOneGen();
    int getLength();
    int getWidth();
private:
    int length, width;
    std::shared_ptr<intMatrix> currMap;
    std::shared_ptr<intMatrix> newMap;
    int countLocalAlive(int i, int j);
};

#endif //WORLD_H