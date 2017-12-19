#include "Master.h"
#include "Shape.h"
#include "Block.h"


using namespace std;



Shape::Shape(int COLOR,int type)
{
  x = 5;
  y = 0;
  color=COLOR;

  Block block_0(x,y,color);
  Block block_1(x,y,color);
  Block block_2(x,y,color);
  Block block_3(x,y,color);

  block_v.push_back(block_0);
  block_v.push_back(block_1);
  block_v.push_back(block_2);
  block_v.push_back(block_3);

  switch(type)
    {	
    case F_O :
      this->O_O();
      break;
      
    case F_T :
      this->O_T();
      break;
      
    case F_I :
      this->O_I();
      break;
      
    case F_L :
      this->O_L();
      break;

    case F_iL :
      this->O_iL();
      break;
      
    case F_S :
      this->O_S();
      break;      
      
    case F_iS :
      this->O_iS();
      break;
    }    
}

void Shape::O_O()
{
  block_v[0].set_x(x + 2); 
  block_v[0].set_y(y + 2); 
  block_v[1].set_x(x + 1);
  block_v[1].set_y(y + 1);
  block_v[2].set_x(x + 1); 
  block_v[2].set_y(y + 2);
  block_v[3].set_x(x + 2); 
  block_v[3].set_y(y + 1);
}

void Shape::O_T()
{
  block_v[0].set_x(x + 1); 
  block_v[0].set_y(y + 2);
  block_v[1].set_x(x + 1); 
  block_v[1].set_y(y); 
  block_v[2].set_x(x + 1); 
  block_v[2].set_y(y + 1);
  block_v[3].set_x(x + 2); 
  block_v[3].set_y(y + 1);      
}

void Shape::O_I()
{
  block_v[0].set_x(x + 2); 
  block_v[0].set_y(y + 3);
  block_v[1].set_x(x + 2); 
  block_v[1].set_y(y); 
  block_v[2].set_x(x + 2); 
  block_v[2].set_y(y + 1);
  block_v[3].set_x(x + 2); 
  block_v[3].set_y(y + 2);
}

void Shape::O_L()
{
  block_v[0].set_x(x + 2); 
  block_v[0].set_y(y + 2);
  block_v[1].set_x(x + 1); 
  block_v[1].set_y(y    ); 
  block_v[2].set_x(x + 1); 
  block_v[2].set_y(y + 1);
  block_v[3].set_x(x + 1); 
  block_v[3].set_y(y + 2);

}

void Shape::O_iL()
{
  block_v[0].set_x(x + 1); 
  block_v[0].set_y(y + 2);
  block_v[1].set_x(x + 2); 
  block_v[1].set_y(y    ); 
  block_v[2].set_x(x + 2); 
  block_v[2].set_y(y + 1);
  block_v[3].set_x(x + 2); 
  block_v[3].set_y(y + 2);
}

void Shape::O_S()
{
  block_v[0].set_x(x + 3); 
  block_v[0].set_y(y + 2);
  block_v[1].set_x(x + 1); 
  block_v[1].set_y(y + 1); 
  block_v[2].set_x(x + 2); 
  block_v[2].set_y(y + 1);
  block_v[3].set_x(x + 2); 
  block_v[3].set_y(y + 2);
}

void Shape::O_iS()
{
  block_v[0].set_x(x + 1); 
  block_v[0].set_y(y + 2);
  block_v[1].set_x(x + 3); 
  block_v[1].set_y(y + 1); 
  block_v[2].set_x(x + 2); 
  block_v[2].set_y(y + 1);
  block_v[3].set_x(x + 2); 
  block_v[3].set_y(y + 2);
}


int Shape::get_color()
{
  return color;
}

int Shape::get_x()
{
  return x;
}
int Shape::get_y()
{
  return y;
}

void Shape::set_color(int COLOR)
{
  color=COLOR;
}

void Shape::set_x(int X)
{
  x=X;
}
void Shape::set_y(int Y)
{
  y=Y;
}



void Shape::move_right()
{   
  x ++;
  for(int i=0;i<NB_BLOCK;i++)
    block_v[i].move_right();
}

void Shape::move_left()
{  
  x--;                    
  for(int i=0;i<NB_BLOCK;i++)	
    block_v[i].move_left();
}

void Shape::move_down()
{ 		
  y ++;
  for(int i=0;i<NB_BLOCK;i++)	
    block_v[i].move_down();
}


//Hugly rotate
//TODO: need a matrix rotate
void Shape::rotate_clockwize()
{     
  bool rot_valid = true ;

  int py=this->get_y();
  int px=this->get_x();
    
  for(int i=0;i<NB_BLOCK;i++)
    {  
      int cx=block_v[i].get_x();
      int cy=block_v[i].get_y();

      if( cx == x)
	{   
	  cx = x+3+y-cy;
	  cy = y;
	}
      else if ( cy == y)
	{
	  cy = y-x+cx;
	  cx = x+3;
	}
      else if ( cy == y+3)
	{    
	  cy = y-x+cx;
	  cx = x;
	}
      else if ( cx == x+3)
	{  
	  cx = x+3-cy+y;
	  cy = y+3;
	}
      else if ( cx == x+1  && 
		cy == y+1)
	{
	  cx = x+2;
	}
      else if ( cx == x+1  && 
		cy == y+2)
	{
	  cy = y+1;
	  cx = x+1;
	}
      else if ( cx == x+2  && 
		cy == y+1)
	{
	  cy=cy+1;
	}
      else if ( cx == x+2  && 
		cy == y+2)
	{
	  cx = x+1;
	  cy = y+2;
	}
      block_v[i].set_x(cx);
      block_v[i].set_y(cy);
    }
}

void Shape::rotate_counterclockwize()
{
  this->rotate_clockwize();
  this->rotate_clockwize();
  this->rotate_clockwize();
}



