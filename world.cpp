#include "world.h"
#include <cstring>

World::World(const int width, const int height) 
: m_map_width(width), m_map_height(height){
  m_map = new char*[height];
  for (int i = 0; i < width; ++i){
    m_map[i] = new char[height];
    memset(m_map[i], 0, height);
  }
}
World::~World(){
}
char &World::at(int x, int y){
  return m_map[x][y];
}
int World::width(){
  return m_map_width;
}
int World::height(){
  return m_map_height;
}
