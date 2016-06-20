#include <cstdio>
#include <unistd.h>
#include "game.h"

const int FRAMERATE = 1;

namespace {
  int framerate_to_usec(int fps){
    return (int)(1000000/fps + 0.5);
  }
  int WORLD_WIDTH = 30;
  int WORLD_HEIGHT = 30;
}


Game::Game()
: m_players(new std::vector<Player>()), m_world(new World(WORLD_WIDTH, WORLD_HEIGHT))
{
  for (int j = 0; j < WORLD_HEIGHT; ++j){
    for (int i = 0; i < WORLD_WIDTH; ++i){
      m_world->at(i, j) = '.';
    }
  }
}

void Game::set_renderer(std::shared_ptr<Renderer> renderer){
  m_renderer = renderer;
  m_renderer->set_world(m_world);
  m_renderer->set_players(m_players);
}


void Game::start(){
  bool quit = false;
  int frame = 0;
  while (!quit){
    m_renderer->draw_everything();

    usleep(framerate_to_usec(FRAMERATE));
    if (++frame == FRAMERATE){
      printf("Frame %i\n", frame);
      frame = 0;
    }
  }
}
