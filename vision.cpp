#include <cstdio>
#include <cmath>

#define PI 3.14159265

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 30;

char map[MAP_WIDTH][MAP_HEIGHT];

const int player_x = 14;
const int player_y = 29;
const int obstr_x = 14;
const int obstr_y = 25;

void build_map(){
  map[player_x][player_y] = 'o';
  map[obstr_x][obstr_y] = 'x';
}

void build_vision(){
  double gradient = 0;
  bool vertical_up = false, vertical_down = false;
  int rel_x = player_x - obstr_x;
  int rel_y = player_y - obstr_y;
  if (rel_x != 0)
    gradient = (double) rel_y / rel_x;
  else if (rel_y > 0)
    vertical_up = true;
  else if (rel_y < 0)
    vertical_down = true;
  else
    return;

  double left_edge = obstr_x - 0.5;
  double right_edge = obstr_x + 0.5;

  double left_edge_gradient = (double)rel_y / (player_x - left_edge);
  double right_edge_gradient = (double)rel_y / (player_x - right_edge);

  if (gradient > 0){
    for (double x = (obstr_x-1/gradient), y = obstr_y-1; y >= 0; --y, x -= 1/gradient){
      int closest_x_index = std::round(x);
      if (closest_x_index < 0)
        closest_x_index = 0;
      for (int i = closest_x_index-1; i >= 0; --i){
        double tile_gradient = (double)(obstr_y - y) / (left_edge - i);
        if (tile_gradient > 0 && tile_gradient >= left_edge_gradient){
          map[i][(int)y] = '@';
        } else break;
      }
      for (int i = closest_x_index; i <= MAP_WIDTH; ++i){
        double tile_gradient = (double)(obstr_y - y) / (right_edge - i);
        if (tile_gradient > 0 && tile_gradient <= right_edge_gradient){
          map[i][(int)y] = '@';
        } else break;
      }
    }
  }
  else if (vertical_up){
    for (int y = obstr_y-1; y >= 0; --y){
      map[obstr_x][y] = '@';
      for (int x = obstr_x-1; x >= 0; --x){
        double tile_gradient = (double)(obstr_y - y) / (left_edge - x);
        if (tile_gradient >= left_edge_gradient){
          map[x][y] = '@';
        } else break;
      }
      for (int x = obstr_x+1; x < MAP_WIDTH; ++x){
        double tile_gradient = (double)(obstr_y - y) / (right_edge - x);
        if (tile_gradient <= right_edge_gradient){
          map[x][y] = '@';
        } else break;
      }
    }
  }
  printf("\n");
}

int main(){
  for (int i = 0; i < MAP_WIDTH; ++i){
    for (int j = 0; j < MAP_HEIGHT; ++j){
      map[i][j] = '.';
    }
  }

  build_map();
  build_vision();


  for (int j = 0; j < MAP_HEIGHT; ++j){
    for (int i = 0; i < MAP_WIDTH; ++i){
      printf("%c ", map[i][j]);
    }
    printf("\n");
  }
}
