#include "game.h"
#include "renderer.h"
#include <memory>

int main(){
  Game game;
  game.set_renderer(std::shared_ptr<Renderer>(new DefaultRenderer()));
  game.start();
  return 0;
}
