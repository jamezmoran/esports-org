#include <cstdio>
#include <cmath>

#define PI 3.14159265

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 30;

char map[MAP_WIDTH][MAP_HEIGHT];

const int player_x = 14;
const int player_y = 27;
const int obstr_x = 13;
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

  if (gradient > 0 || vertical_up){
    for (double x = (obstr_x-1/gradient), y = obstr_y-1; y >= 0; --y, x = x-(double)1/gradient){
      int closest_x_index = std::round(x);
      map[closest_x_index][(int)y] = '@';
      for (int i = closest_x_index-1; i >= 0; --i){
        double tile_gradient = (double)(obstr_y - y) / (left_edge - i);
        if (tile_gradient >= left_edge_gradient){
          map[i][(int)y] = '@';
        } else break;
      }
      for (int i = closest_x_index+1; i <= obstr_x; ++i){
        double tile_gradient = (double)(obstr_y - y) / (right_edge - i);
        if (tile_gradient <= right_edge_gradient){
          map[i][(int)y] = '@';
        } else break;
      }
    }
    printf("\n");
  }


  /*
  for (int i = 0; i < MAP_WIDTH; ++i){
    for (int j = 0; j < MAP_HEIGHT; ++j){
      if (map[i][j] == 'x')
        continue;
      int relx = player_x - i;
      int rely = player_y - j;
      if (relx == 0){
        map[i][j] = '*';
      } else if (std::abs(atan(rely/relx)*180/PI) > 60) {
        map[i][j] = '*';
      }
    }
  }
  for (int i = 0; i < MAP_WIDTH; ++i){
    for (int j = 0; j < MAP_HEIGHT; ++j){
      if (map[i][j] == 'x'){
        double relx_l = player_x - i-0.5;
        double relx_r = player_x - i+0.5;
        double rely = player_y - j;
        if (relx_l == 0 || relx_r == 0){
          map[i][j] = '@';
        } else {
          double obs_angle_l = std::abs(atan(relx_l/rely)*180/PI);
          double obs_angle_r = std::abs(atan(relx_r/rely)*180/PI);
          for (int j = obstr_y-1; j >= 0; --j){
            for (double i = obstr_x+relx*j; i <= MAP_WIDTH; i+relx){
              double branch_relx = i - obstr_x - relx_l;
              double branch_rely = j - obstr_y;
              if (branch_relx == 0){
                map[std::round(i)][j] = '@';
              } else {
                double second_angle = std::abs(atan(branch_relx/branch_rely)*180/PI);
                if (second_angle <= obs_angle_l){
                  map[std::round(i)][j] = '@';
                }
                else 
                  break;
              }
            }
            for (int i = obstr_x; i >= 0; --i){
              double branch_relx = i - obstr_x - relx_r;
              double branch_rely = j - obstr_y;
              if (branch_relx == 0){
                map[i][j] = '@';
              } else {
                double second_angle = std::abs(atan(branch_relx/branch_rely)*180/PI);
                if (second_angle <= obs_angle_r){
                  map[i][j] = '@';
                }
                else 
                  break;
              }
            }
          }
        }
      }
    }
  }
  */
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
