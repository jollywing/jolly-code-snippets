
#ifndef __MAP_HPP__
#define __MAP_HPP__

// Map interfaces
class Map {
protected:
    short mapWidth;
    short mapHeight;
public:
    virtual void ShowMap() =0;
};

class TileMap: Map {
public:
    TileMap();
    virtual void ShowMap();
};

class PicMap: Map {
public:
    PicMap();
    virtual void ShowMap();
};

// abstract factory
class MapFactory {
public:
    virtual Map * CreateMap() =0;
};

class TileMapFactory {
public:
    virtual Map * CreateMap();
};

class PicMapFactory {
public:
    virtual Map * CreateMap();
};


class MapEngine {
private:
    MapFactory factory;
    
};
#endif
