#ifndef ROTHBERG_MAP_HEADER
#define ROTHBERG_MAP_HEADER

#include "ysclass.h"
#include "Road.h"

enum MapSize {
    small, middle, large
    // small = 10 roads; middle = 25 road; large = 50 roads;
};

class Map {

private:
    int roadWidth = 10;
public:
    Map();
    Map(int rN);
    Map(MapSize mapSize);
    ~Map();
    bool isInMap(YsVec3 position);
    bool isInMap(int x, int y, int z);
    bool isInMap(int x, int y);
private:
    void initMap(int rN);
    int roadNum;
    std::vector<Road> roads;

public:
    void dbgPrintRoads();
};

    

#endif