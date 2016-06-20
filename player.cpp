#include "player.h"

Player::Player(int x, int y)
: m_pos_x(x), m_pos_y(y)
{
}
Player::~Player(){
}

void Player::act(){
}

int Player::get_x(){
  return m_pos_x;
}
int Player::get_y(){
  return m_pos_y;
}
int Player::get_z(){
  return m_pos_z;
}

void Player::set_world(const std::weak_ptr<World> world){
  m_world = world;
}
void Player::set_players(const std::weak_ptr<std::vector<Player> > players){
  m_players = players;
}
