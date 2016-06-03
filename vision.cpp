#include <cstdio>
#include <cmath>

#define PI 3.14159265

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 30;

char map[MAP_WIDTH][MAP_HEIGHT];

const int player_x = 15;
const int player_y = 2;
const int obstr_x = 14;
const int obstr_y = 3;

void build_map(){
  map[player_x][player_y] = 'o';
  map[obstr_x][obstr_y] = 'x';
}

void build_vision(){
  double gradient = 0;
  bool vertical_up = false, vertical_down = false;
  int rel_x = obstr_x - player_x;
  int rel_y = obstr_y - player_y;
  if (rel_x == 0 and rel_y == 0)
    return;

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

  double angle = atan2(rel_y, rel_x);
  double rotation_angle = angle;// + (angle>PI/2 ? PI/2 : 0);
  double left_edge_x = obstr_x + 0.5*cos(rotation_angle);
  double right_edge_x = obstr_x - 0.5*cos(rotation_angle);
  double left_edge_y = obstr_y - 0.5*sin(rotation_angle);
  double right_edge_y = obstr_y + 0.5*sin(rotation_angle);
  double left_edge_angle = atan2(left_edge_y - player_y, left_edge_x - player_x);
  double right_edge_angle = atan2(right_edge_y - player_y, right_edge_x - player_x);

  if (angle > 0 && angle < PI){
    for (int y = obstr_y+1; y < MAP_HEIGHT; ++y){
      bool vertical = (obstr_x == player_x) ? true : false;
      for (int x = vertical ? obstr_x :  obstr_x + std::round((y - obstr_y) / tan(angle)); x >= 0; --x){
        if (x >= MAP_WIDTH)
          x = MAP_WIDTH-1;
        double tile_angle_to_edge = atan2(y - left_edge_y, x - left_edge_x);
        printf("%G %i %i\n", tile_angle_to_edge, x, y);
        if (tile_angle_to_edge <= left_edge_angle){
          map[x][y] = '@';
        } else {
          break;
        }
      }
      for (int x = vertical ? obstr_x : obstr_x + std::round((y - obstr_y) / tan(angle)); x < MAP_WIDTH; ++x){
        if (x < 0)
          x = 0;
        double tile_angle_to_edge = atan2(y - right_edge_y, x - right_edge_x);
        if (tile_angle_to_edge >= right_edge_angle){
          map[x][y] = '@';
        } else {
          break;
        }
      }
    }
  }
/*
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
  */
}

int main(){
  for (int i = 0; i < MAP_WIDTH; ++i){
    for (int j = MAP_HEIGHT-1; j >= 0; --j){
      map[i][j] = '.';
    }
  }

  build_map();
  build_vision();


  for (int j = MAP_HEIGHT-1; j >= 0; --j){
    for (int i = 0; i < MAP_WIDTH; ++i){
      printf("%c ", map[i][j]);
    }
    printf("\n");
  }
}
