#include "Map.hpp"

TileMap::TileMap()
{
}

PicMap::PicMap()
{
}

TileMapFactory::CreateMap()
{
  return new TileMap;
}

PicMapFactory::CreateMap()
{
  return new PicMap;
}
