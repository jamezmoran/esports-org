#ifndef _PLAYER_H
#define _PLAYER_H

#include <vector>
#include <memory>

#include "world.h"

class Player {
  public:
    Player(int x, int y);
    ~Player();

    void act();
    void set_world(const std::weak_ptr<World> world);
    void set_players(const std::weak_ptr<std::vector<Player> > players);

    int get_x();
    int get_y();
    int get_z();

  private:
    int m_pos_x;
    int m_pos_y;
    int m_pos_z;

    std::weak_ptr<std::vector<Player> > m_players;
    std::weak_ptr<World> m_world;
};

#endif
