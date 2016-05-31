#include <vector>
#include <cstdio>
#include <unistd.h>


const int MAP_HEIGHT = 8;
const int MAP_WIDTH = 7;

const char &get_map_value(int x, int y){
  static const char map[MAP_HEIGHT][MAP_WIDTH] = {
    {'.','x','.','.','.','.','.'},
    {'.','x','.','.','x','x','.'},
    {'.','.','.','.','.','x','.'},
    {'.','.','.','.','.','x','x'},
    {'.','x','.','x','.','x','.'},
    {'x','x','.','x','.','x','.'},
    {'.','x','.','x','.','x','.'},
    {'.','.','.','.','.','.','.'}
  };
  return map[y][x];
}

struct player {
  player(int posx, int posy, int dirx, int diry):dead(false),x(posx),y(posy),direction_x(dirx), direction_y(diry) {}
  void act(){
    if (dead)
      return;
    int local_dirx = direction_x;
    int local_diry = direction_y;
    int local_x = x;
    int local_y = y;
    if (direction_x != 0){
      local_x += local_dirx;
      if (check_blocked(local_x, y)){
        local_x = x;
        local_dirx = 0;
        local_diry = 1;
        local_y = y+local_diry;
        if (check_blocked(x,local_y)){
          local_diry = -1;
          local_y = y+local_diry;
          if (check_blocked(x,local_y)){
            local_dirx = direction_x * -1;
            local_x = x + local_dirx;
            if (check_blocked(local_x,y)){
              return;
            } else {
              x = local_x;
              direction_x = local_dirx;
            }
          } else {
            direction_x = 0;
            direction_y = local_diry;
            y = local_y;
          }
        } else {
          direction_x = 0;
          direction_y = local_diry;
          y = local_y;
        }
      } 
      else {
        x = local_x;
      }
    }
    else if (direction_y != 0){
      local_y += direction_y;
      if (check_blocked(x, local_y)){
        local_y = y;
        local_diry = 0;
        local_dirx = 1;
        local_x = x+local_dirx;
        if (check_blocked(local_x,y)){
          local_dirx = -1;
          local_x = x+local_dirx;
          if (check_blocked(local_x,y)){
            local_diry = direction_y * -1;
            local_y = y + local_diry;
            if (check_blocked(x,local_y)){
              return;
            } else {
              y = local_y;
              direction_y = local_diry;
            }
          } else {
            direction_y = 0;
            direction_x = local_dirx;
            x = local_x;
          }
        } else {
          direction_y = 0;
          direction_x = local_dirx;
          x = local_x;
        }
      } else {
        y = local_y;
      }
    }
  }
  void reset_direction(){
    direction_x = 0;
    direction_y = 0;
  }
  bool check_blocked(int x, int y){
    if (x >= MAP_WIDTH || x < 0){
      return true;
    } else if (y >= MAP_HEIGHT || y < 0){
      return true;
    } else if (get_map_value(x,y) == 'x'){
      return true;
    } else {
      return false;
    }
  }
  int x;
  int y;
  int direction_x;
  int direction_y;
  bool dead;
};
std::vector<player> players;
player* &get_sprite_ptr(int x, int y){
  static player* sprite_map[MAP_HEIGHT][MAP_WIDTH] = { NULL };

  return sprite_map[y][x];
}


void add_player(const player& p){
  new player(p);
}

void draw_player(const player* p){
  if (p->dead){
    printf("%c ", 237);
  } 
  else if (p->direction_y < 0){
    printf("< ");
  }
  else if (p->direction_y > 0){
    printf("> ");
  }
  else if (p->direction_x < 0){
    printf("^ ");
  }
  else if (p->direction_x > 0){
    printf("v ");
  } 
  else {
    printf("o ");
  }
}

void build_world(){
  for (int i = 0; i < MAP_WIDTH; ++i){
    for (int j = 0; j < MAP_HEIGHT; ++j){
      get_sprite_ptr(i,j) = NULL;
    }
  }
  for (int i = 0; i < players.size(); ++i){
    players[i].act();
    get_sprite_ptr(players[i].x,players[i].y) = &players[i];
  }
}

void draw_world(){
  for (int i = 0; i < MAP_WIDTH; ++i){
    for (int j = 0; j < MAP_HEIGHT; ++j){
      if (NULL != get_sprite_ptr(i,j)){
        draw_player(get_sprite_ptr(i,j));
      } else {
        printf("%c ", get_map_value(i,j));
      }
    }
    printf("\n");
  }
  printf("\n");
}


int main(){
  players.push_back(player(3,6,0,1));
  players.push_back(player(4,0,1,-1));
  players.push_back(player(3,0,0,1));
  players.push_back(player(0,6,0,-1));
  while (true){
    build_world();
    draw_world();
    sleep(1);
  }
  return 0;  
}
