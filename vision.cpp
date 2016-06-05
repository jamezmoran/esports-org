#include <cstdio>
#include <cmath>

#define PI 3.14159265

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 30;

char map[MAP_WIDTH][MAP_HEIGHT];

const int player_x = 16;
const int player_y = 12;

void build_map(){
  map[player_x][player_y] = 'o';
}

void build_vision(int obstr_x, int obstr_y){
  int rel_x = obstr_x - player_x;
  int rel_y = obstr_y - player_y;
  map[obstr_x][obstr_y] = 'x';
  if (rel_x == 0 and rel_y == 0)
    return;

  double left_edge = obstr_x - 0.5;
  double right_edge = obstr_x + 0.5;

  double angle = atan2(rel_y, rel_x);
  double rotation_angle = 0;
  if (angle < 0)
    rotation_angle = angle + PI/2;// + (angle>PI/2 ? PI/2 : 0);
  else if (angle > 0)
    rotation_angle = angle - PI/2;// + (angle>PI/2 ? PI/2 : 0);
  else if (rel_x > 0)
    rotation_angle = -PI/2;
  else if (rel_x < 0)
    rotation_angle = PI/2;
  double rot_x = 0.5*cos(rotation_angle);
  double rot_y = 0.5*sin(rotation_angle);
  if ((rot_x > 0 && rot_x < 0.001) || (rot_x < 0 && rot_x > -0.001))
    rot_x = 0;
  if ((rot_y > 0 && rot_y < 0.001) || (rot_y < 0 && rot_y > -0.001))
    rot_y = 0;
  double left_edge_x = obstr_x - rot_x;
  double right_edge_x = obstr_x + rot_x;
  double left_edge_y = obstr_y - rot_y;
  double right_edge_y = obstr_y + rot_y;
  double left_edge_angle = atan2(left_edge_y - player_y, left_edge_x - player_x);
  double right_edge_angle = atan2(right_edge_y - player_y, right_edge_x - player_x);

  if (angle != 0 && angle < PI && angle > -PI){
    for (int y = obstr_y;;){
      bool vertical = (obstr_x == player_x) ? true : false;
      for (int x = vertical ? obstr_x :  obstr_x + std::round((y - obstr_y) / tan(angle)); x >= 0; --x){
        if (x >= MAP_WIDTH)
          x = MAP_WIDTH-1;
        if (x == obstr_x && y == obstr_y)
          continue;
        double tile_angle_to_edge = atan2(y - left_edge_y, x - left_edge_x);
        if ((angle >= 0 && tile_angle_to_edge <= left_edge_angle && tile_angle_to_edge > 0)
          || (angle <= 0 && tile_angle_to_edge >= left_edge_angle && tile_angle_to_edge < 0)){
          map[x][y] = '@';
        } else {
          break;
        }
      }
      for (int x = vertical ? obstr_x : obstr_x + std::round((y - obstr_y) / tan(angle)); x < MAP_WIDTH; ++x){
        if (x < 0)
          x = 0;
        if (x == obstr_x && y == obstr_y)
          continue;
        double tile_angle_to_edge = atan2(y - right_edge_y, x - right_edge_x);
        if ((angle >= 0 && tile_angle_to_edge >= right_edge_angle)
          || (angle <= 0 && tile_angle_to_edge <= right_edge_angle)){
          map[x][y] = '@';
        } else {
          break;
        }
      }
      if (!((angle >= 0 && ++y < MAP_HEIGHT) || (angle <= 0 && --y >= 0)))
        break;
    }
  }
  if (rel_y == 0 && rel_x > 0){
    for (int x = obstr_x;;){
      for (int y = obstr_y; y >= 0; --y){
        if (y == obstr_y && x == obstr_x)
          continue;
        double tile_angle_to_edge = atan2(y - right_edge_y, x - right_edge_x);
        if ((rel_x > 0 && tile_angle_to_edge >= right_edge_angle)){
          map[x][y] = '@';
        } else {
          break;
        }
      }
      for (int y = obstr_y; y < MAP_HEIGHT; ++y){
        if (x == obstr_x && y == obstr_y)
          continue;
        double tile_angle_to_edge = atan2(y - left_edge_y, x - left_edge_x);
        if (tile_angle_to_edge <= left_edge_angle){
          map[x][y] = '@';
        } else {
          break;
        }
      }
      if (!((rel_x > 0 && ++x < MAP_WIDTH) || (rel_x < 0 && --x >= 0)))
        break;
    }
  }
  else if (rel_y == 0 && rel_x < 0){
    for (int x = obstr_x;;){
      for (int y = obstr_y; y >= 0; --y){
        if (y == obstr_y && x == obstr_x)
          continue;
        double tile_angle_to_edge = atan2(y - left_edge_y, x - left_edge_x);
        if (tile_angle_to_edge <= left_edge_angle || tile_angle_to_edge > 0){
          map[x][y] = '@';
        } else {
          break;
        }
      }
      for (int y = obstr_y; y < MAP_HEIGHT; ++y){
        if (x == obstr_x && y == obstr_y)
          continue;
        double tile_angle_to_edge = atan2(y - right_edge_y, x - right_edge_x);
        if (tile_angle_to_edge >= right_edge_angle || tile_angle_to_edge < 0){
          map[x][y] = '@';
        } else {
          break;
        }
      }
      if (!((rel_x > 0 && ++x < MAP_WIDTH) || (rel_x < 0 && --x >= 0)))
        break;
    }
  }
}

int main(){
  for (int i = 0; i < MAP_WIDTH; ++i){
    for (int j = MAP_HEIGHT-1; j >= 0; --j){
      map[i][j] = '.';
    }
  }

  build_map();
  build_vision(10,10);
  build_vision(4,4);
  build_vision(14,7);
  build_vision(23,10);
  build_vision(23,20);
  build_vision(15,14);


  for (int j = MAP_HEIGHT-1; j >= 0; --j){
    for (int i = 0; i < MAP_WIDTH; ++i){
      printf("%c ", map[i][j]);
    }
    printf("\n");
  }
}
