#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"

static Pixel blend(Pixel oldPixel, Pixel newPixel)
{
    newPixel.r = newPixel.a / 255.0 * (newPixel.r - oldPixel.r) + oldPixel.r;
    newPixel.g = newPixel.a / 255.0 * (newPixel.g - oldPixel.g) + oldPixel.g;
    newPixel.b = newPixel.a / 255.0 * (newPixel.b - oldPixel.b) + oldPixel.b;
    newPixel.a = 255;
    return newPixel;
}

enum class MovementDir
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct Player
{

    Point coords {.x = 10, .y = 10};
    Point old_coords {.x = 10, .y = 10};
    Point health_pos = {.x = 0, .y = 992};
    int mode = 0; // 1 - right 2 - left, 3 - damaged, 4-attack
    int hp = 3;
    bool immune = false;
    bool break_wall = false;
    Point break_wall_coords {.x = 0, .y = 0};
    GLfloat immune_count;
    GLfloat attack_time = 0;

    void Switch_status(GLfloat currentFrame);
    void Check_trap(char *card, bool &check_trap);
    void Switch_pos(int delta);
    int Level_pos(){ return level_pos; }
    Point Get_coords() { return Point{.x = coords.x, .y = coords.y};}
    explicit Player(Point pos = {.x = 10, .y = 10}, int level_pos = 0) :
                 coords(pos), old_coords(coords),  level_pos(level_pos) {};
    bool Moved() const;
    void ProcessInput(MovementDir dir, char *card, int &switch_mode);
    void Draw(Image &screen,  GLfloat currentFrame);
    void Draw_player(Image &screen, Image &img, int offset);

private:
    GLfloat player_count = 0;
    int player_status = 1;
    int level_pos = 0;
    Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};
    int move_speed = 2;
};

#endif //MAIN_PLAYER_H
