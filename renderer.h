#ifndef _RENDERER_H
#define _RENDERER_H

#include <vector>
#include <memory>
#include "world.h"
#include "player.h"

class Renderer {
  public:
    Renderer(){}

    void set_world(std::shared_ptr<World> world);
    void set_players(std::shared_ptr<std::vector<Player> > players);
    virtual void draw_everything() = 0;

  protected:
    std::shared_ptr<World> m_world;
    std::shared_ptr<std::vector<Player> > m_players;
};

class DefaultRenderer : public Renderer {
  public:
    void draw_everything();
};

#endif
