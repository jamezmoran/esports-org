#include "renderer.h"
#include <cstdio>

void Renderer::set_world(std::shared_ptr<World> world){
  m_world = world;
}
void Renderer::set_players(std::shared_ptr<std::vector<Player> > players){
  m_players = players;
}

void DefaultRenderer::draw_everything(){
  if (m_world){
    for (int j = 0; j < m_world->height(); ++j){
      for (int i = 0; i < m_world->width(); ++i){
        printf("%c", m_world->at(i,j));
      }
      printf("\n");
    }
    printf("\n");
  }
}
