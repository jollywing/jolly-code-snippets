
import java.util.List;
// @opt types : show the parameters of operations
// * @opt all : show attributes, operations and types

/**
 * @opt visibility
 * @opt attributes
 * @opt operations
 * @opt types
 * @hidden
 */
class UMLOptions {}

/** @hidden */
class SDLRect {}

/** @hidden */
class Point {}

/** @hidden */
class SDLSurface {}

// How to show private attribute
class DirtyRect {
    SDLRect r;
    public DirtyRect();
    public void updateRect(Point from, Point to);
}

class Sprite {
    short glyph;
    int x;
    int y;
    public void draw();
}

/** @has - - - Fighter */
class Role extends Sprite {
    String _name;
    int _glyph;
    public void draw(int x, int y);
}

class Item extends Sprite {
    
}

class ItemFactory {
    List<Item> _items;
    public void loadItems(final String itemFile);
    public Item createItem();
}

/** @has - - - Fighter */
class Player extends Role {
}

class Fighter extends Role {}

class Path {
    List<Point> path;
    public void append(Point p);
    public void remove(Point p);
    public void clear();
    public boolean isEmpty();
}


/**
 * @has - - - DirtyRect
 * @has - - - Path
 * @has - - - Player
 * @has - 1..* - Item
 * @has - 1..* - Role
 * @depend - - - PathFinder
 * @depend - - - ItemFactory
 */
class Map {
    short _width;
    short _height;
    short [] _tiles;
    SDLSurface _tilePage;
    DirtyRect _rect;
    Path _path;
    Player _player;
    List<Item> _items;
    List<Role> _npcs;
    Map _map;
    public Map instance();
    public void draw();
    public void updateRect(Point from, Point to);
    void createTiles();
    void drawTiles();
    void createRoles();
    void drawRoles();
    void createItems();
    void drawItems();
    void drawPlayer();
    void findPath(PathFinder finder, Point target);
    void drawPath();
}

interface PathFinder {
    public void findPath(Map m, Point target);
}

class AStarPathFinder implements PathFinder {}

class GreedyPathFinder implements PathFinder {}

/**
 * @has - - - Map
 */
class Game {
    Map map;
    public void run();
}
