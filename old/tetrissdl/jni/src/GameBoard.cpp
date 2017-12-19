#include "Master.h"
#include "GameBoard.h"
#include "Shape.h"

using namespace  std;

GameBoard::GameBoard()
{
}

void GameBoard::zero_map()
{
  for (int i=0;i<BLOCK_LENGTH;i++)
    for (int j=0;j<BLOCK_WIDTH;j++)
      map[i][j]=0;
}


bool GameBoard::is_full()
{
  bool full=false;
  int i=1;
  for (int j=0;j<BLOCK_WIDTH;j++)
    {
      if (map[i][j]!=0)
        full=true;
    }
  return full;
}



bool GameBoard::can_shape_move_left(Shape * current_shape)
{
  bool mov_possible = true;
  for(int i=0;i<NB_BLOCK;i++)
    {
      int cx=current_shape->block_v[i].get_x();
      int cy=current_shape->block_v[i].get_y();

      if( map[cy][cx-1] != 0   ||
          cx  == 0)
        mov_possible = false;
    }
  return mov_possible;
}

bool GameBoard::can_shape_move_down(Shape * current_shape)
{
  bool mov_possible = true;
  int py=current_shape->get_y();
  int px=current_shape->get_x();

  for(int i=0;i<NB_BLOCK;i++)
    {
      int cx=current_shape->block_v[i].get_x();
      int cy=current_shape->block_v[i].get_y();

      if( map[cy+1 ][cx] != 0   ||
          cy >= BLOCK_LENGTH-1)
        {
          mov_possible = false;
        }
    }
  return mov_possible;
}

bool GameBoard::can_shape_move_right(Shape * current_shape)
{
  bool mov_possible = true;
  for(int i=0;i<NB_BLOCK;i++)
    {
      int cx=current_shape->block_v[i].get_x();
      int cy=current_shape->block_v[i].get_y();

      if( map[cy][cx+1] != 0   ||
          cx  == BLOCK_WIDTH-1)
        mov_possible = false;
    }
  return mov_possible;
}

//Hugly
//TODO: a robust collision detection
bool GameBoard::can_shape_rotate(Shape * current_shape)
{
  bool can_rotate = true ;

  int px=current_shape->get_x();
  int py=current_shape->get_y();

  for(int i=0;i<NB_BLOCK;i++)
    {
      int cx=current_shape->block_v[i].get_x();
      int cy=current_shape->block_v[i].get_y();


      if(cx == px                                      &&
         (map[py][px + 3 + py - cy] != 0               ||
          (px + 3 + py - cy)>=BLOCK_WIDTH) )
	can_rotate = false;
      
      else if(cy == py                                 &&
              (map[py - px + cx][px + 3] != 0          ||
               py - px + cx <= 0                       ||
               px + 3 >= BLOCK_WIDTH  ))
	can_rotate = false;
      
      else if(cy ==  py+3                              &&
              (map[py - px + cx][px] != 0              ||
               py - px + cx >= BLOCK_LENGTH            ||
               px < 0 ) )
	can_rotate = false;


      else if(cx == px + 3                             &&
              ((map[py + 3][px + 3 - cy + py] != 0 ) ||
               (px + 3 - cy + py <0 ) ))
	can_rotate = false;

      else if( cx == px +1                             &&
               (cy == py +1)                           &&
               (map[py + 1][px + 2] != 0))
	can_rotate = false;

      else if(cx == px +2                              &&
              cy == py +1                              &&
              (map[py + 2][px + 2] !=0                 ||
               py +2 >= BLOCK_LENGTH ))
	can_rotate = false;

      else if(cx == px +1                              &&
              cy == py +2                              &&
              map[py +1][px + 1] !=0 )
	can_rotate = false;
      
      else if(cx == px +2                              &&
              cy == py +2                              &&
              map[py +2][px + 1] !=0)
	can_rotate = false;
      
    }
  return can_rotate;
}


bool GameBoard::insert_shape(Shape * current_shape)
{
  int py=current_shape->get_y();
  int px=current_shape->get_x();

  for(int i=0;i<NB_BLOCK;i++)
    {
      int cx=current_shape->block_v[i].get_x();
      int cy=current_shape->block_v[i].get_y();

      map[cy][cx] = current_shape->get_color();
    }
}


int GameBoard::clean_full_line(int & compteur)
{
  int nb=0;
  for(int j=BLOCK_LENGTH-1;j>0;j--)
    {
      bool full = true;
      for(int i=0;i < BLOCK_WIDTH;i++)
        {
          if(map[j][i] == 0)
            full = false;
        }

      if(full == true)
        {
          compteur+=100;
          nb = nb +1;

          for(int k=j;k>0;k--)
            for(int i=0;i<BLOCK_WIDTH;i++)
              map[k][i] = map[k-1][i];

          for(int i=0;i<BLOCK_WIDTH;i++)
              map[0][i] = 0;
        }
    }
  switch( nb )
    {
    case 2 :
      compteur += 100;
      break;

    case 3 :
      compteur+=100;
      break;

    case 4 :
      compteur+=400;
      break;
  }
  return nb;
}

void GameBoard::display_map()
{
  for (int i=0;i<BLOCK_LENGTH;i++)
    {
      for (int j=0;j<BLOCK_WIDTH;j++)
        {
          cout << "[" << map[i][j] << "]";
        }
      cout << endl;
    }
  cout << endl << endl;
}
