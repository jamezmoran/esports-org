#ifndef GAME_H
#define GAME_H

#include <memory>
#include "renderer.h"

class Game {
  public:
    Game();
    ~Game(){};

    void start();
    void set_renderer(const std::shared_ptr<Renderer> renderer);

  private:
    void handle_input();
    std::shared_ptr<Renderer> m_renderer;
    std::shared_ptr<World> m_world;
    std::shared_ptr<std::vector<Player> > m_players;
};

#endif
