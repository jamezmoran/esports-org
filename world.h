#ifndef _WORLD_H
#define _WORLD_H

class World {
  public:
    World(int width, int height);
    ~World();

    char &at(int x, int y);
    int width();
    int height();

  private:
    char **m_map;
    int m_map_width;
    int m_map_height;
    
};

#endif
