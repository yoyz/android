#include "Master.h"
#include "Block.h"

using namespace  std;

Block::Block(int X,int Y,int COLOR)
{
  x = X;
  y = Y;
  color = COLOR;
}


void Block::move_up()
{       
  y--;
}

void Block::move_down()
{ 
  y++;
}

void Block::move_right()
{  
  x++;
}

void Block::move_left()
{
  x--;
}

int Block::get_x()
{
  return x;
}

int Block::get_y()
{
  return y;
}

int Block::get_color()
{
  return color;
}


void Block::set_x(int X)
{
  x=X;
}

void Block::set_y(int Y)
{
  y=Y;
}

void Block::set_color(int COLOR)
{
  color=COLOR;
}

