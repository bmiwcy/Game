#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define TRUE  1
#define FLASE 2
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4

int x,y;

void drawBoard(int boardData[4][4]);
void initBoard();
int updateBoardData(int boardData[4][4], int x, int y);
int RandProduce(int boardData[4][4]);
int initGame(int boardData[4][4]);
void moveZeroes(int boardData[4][4], int col_row, int Direction);
void moveZeroes_column(int boardData[4][4], int column);
void moveZeroes_row(int boardData[4][4], int row);


int initCurses()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
}

int RandProduce(int boardData[4][4])
{
  int num=0,flag=0,loop=1;
  srand((unsigned)time(NULL));
  do {
  num = (rand()%2 + 1) * 2;
  x = rand()%4;          
  y = rand()%4;
  if(boardData[x][y] == 0)
    {
      boardData[x][y] = num;
      flag++;
      break;
    }
  } while (loop == 1);
  return flag;
}

int initGame(int boardData[4][4])
{
  int i,flag;
  RandProduce(boardData);
  RandProduce(boardData);
  drawBoard(boardData);
  return 0;
}

void drawBoard(int boardData[4][4])
{
  int i,j,k;
  int score = 0;
  erase();
  for(i=0;i<=32;i++)
    for(j=0;j<=16;j+=4)
      {
	mvaddch(j, i, '-');
      }
   for(i=0;i<=32;i+=8)
    for(j=1;j<=16;j++)
      {
	if(j%4 != 0)	
	mvaddch(j, i, '|');
      }
     for(i=1;i<=4;i++)
       for(j=1;j<=4;j++)
	 {
	   if(boardData[i-1][j-1] != 0)
	   updateBoardData(boardData, i, j);
	   score += boardData[i-1][j-1];
	 }
 mvprintw(18, 0, "Score: %d", score);
 refresh();
 
}

int playGame()
{
  int boardData[4][4]={0};
  int addCompare[4]={0};
  int inputChar;
  int i=0,j=0,k,flag,num,Direction;
  initGame(boardData);
  refresh();
  while(inputChar != 'q')
    {
      num = 0;
       for(i=0;i<4;i++)
	for(j=0;j<4;j++)
	  {
	    if(boardData[i][j]>0)
	      num++;
	  }
       if(num == 16)
	 {
      	   if(!canWin(boardData))
	     {
	       mvprintw(20, 0, "Failed!");
	       inputChar = getch();
	       erase();
	       return 1;
	     }
	 }
      inputChar = getch();
      switch(inputChar)
	{
	case KEY_UP:
	  {
	    Direction = UP;
	    for(k=0;k<4;k++)
	      {
		for(i=0;i<3;i++)
		  {
		    if(boardData[i][k] == boardData[i+1][k])
		      {
			boardData[i][k] += boardData[i+1][k];
			boardData[i+1][k] = 0;
			i = i + 2;
		      }
		    else if((boardData[i][k] == boardData[i+2][k]) && (boardData[i+1][k] == 0))
		      {
			boardData[i][k] += boardData[i+2][k];
			boardData[i+2][k] = 0;
		      }
		    else if((boardData[i+1][k] == 0) && (boardData[i+2][k] == 0) && (boardData[i][k] == boardData[i+3][k]))
		      {
			boardData[i][k] += boardData[i+3][k];
			boardData[i+3][k] = 0;
		      }
		  }
		    moveZeroes(boardData, k, Direction);
	      }
	  }break;
	  
	case KEY_DOWN:
	  {
	    Direction = DOWN;
	    for(k=0;k<4;k++)
	      {
		for(i=3;i>=0;i--)
		  {
		    if(boardData[i][k] == boardData[i-1][k])
		      {
			boardData[i][k] += boardData[i-1][k];
			boardData[i-1][k] = 0;
			i = i - 2;
		      }
		    else if((boardData[i][k] == boardData[i-2][k]) && (boardData[i-1][k] == 0))
		      {
			boardData[i][k] += boardData[i-2][k];
			boardData[i-2][k] = 0;
		      }
		    else if((boardData[i-1][k] == 0) && (boardData[i-2][k] == 0) && (boardData[i][k] == boardData[i-3][k]))
		      {
			boardData[i][k] += boardData[i-3][k];
			boardData[i-3][k] = 0;
		      }	    
		  }
		moveZeroes(boardData, k, DOWN);
	      }
	  }break;

	case KEY_LEFT:
	  {
	    Direction = LEFT;
	    for(k=0;k<4;k++)
	      {
		for(i=0;i<3;i++)
		  {
		    if(boardData[k][i] == boardData[k][i+1])
		      {
			boardData[k][i] += boardData[k][i+1];
			boardData[k][i+1] = 0;
			i = i + 2;
		      }
		    else if((boardData[k][i] == boardData[k][i+2]) && (boardData[k][i+1] == 0))
		      {
			boardData[k][i] += boardData[k][i+2];
			boardData[k][i+2] = 0;
		      }
		    else if((boardData[k][i+1] == 0) && (boardData[k][i+2] == 0) && (boardData[k][i] == boardData[k][i+3]))
		      {
			boardData[k][i] += boardData[k][i+3];
			boardData[k][i+3] = 0;
		      }
		  }
		moveZeroes(boardData, k, Direction);
	      }
	  }break;
  
	case KEY_RIGHT:
	  {
	    Direction = RIGHT;
	    for(k=0;k<4;k++)
	      {
		for(i=3;i>=0;i--)
		  {
		    if(boardData[k][i] == boardData[k][i-1])
		      {
			boardData[k][i] += boardData[k][i-1];
			boardData[k][i-1] = 0;
			i = i - 2;
		      }
		    else if((boardData[k][i] == boardData[k][i-2]) && (boardData[k][i-1] == 0))
		      {
			boardData[k][i] += boardData[k][i-2];
			boardData[k][i-2] = 0;
		      }
		    else if((boardData[k][i-1] == 0) && (boardData[k][i-2] == 0) && (boardData[k][i] == boardData[k][i-3]))
		      {
			boardData[k][i] += boardData[k][i-3];
			boardData[k][i-3] = 0;
		      }
		  }
		moveZeroes(boardData, k, Direction);
	      }
	  }break;  
	}
      num=0;
      for(i=0;i<4;i++)
	for(j=0;j<4;j++)
	  {
	    if(boardData[i][j]>0)
	      num++;
	  }
      if(num <16)
	{
	  RandProduce(boardData);
	}
      drawBoard(boardData);// switch
      move(20,0);
    }
  return 0;
}

void moveZeroes(int boardData[4][4], int col_row, int Direction)
{
  int zero=0, i=0;
  switch(Direction)
    {
    case UP:
      {
	for(i=0; i<4; i++)
	  {
            if (boardData[i][col_row] == 0)
	      {
	        ++zero;
	      }
	    else
	      {
	        boardData[i-zero][col_row] = boardData[i][col_row];
	      }
	  }
	while (zero>0)
	  {
	    boardData[4-zero][col_row] = 0;
	    --zero;
          }
      }break;
      
    case DOWN:
      {
	for(i=3; i>=0; i--)
	  {
	    if(boardData[i][col_row] == 0)
	      {
		++zero;
	      }
	    else
	      {
		boardData[i+zero][col_row] = boardData[i][col_row];
	      }
	  }
	while(zero > 0)
	  {
	    boardData[zero-1][col_row] = 0;
	    --zero;
	  }
      }break;
      
     case LEFT:
      {
	for(i=0; i<4; i++)
	  {
            if (boardData[col_row][i] == 0)
	      {
	        ++zero;
	      }
	    else
	      {
	        boardData[col_row][i-zero] = boardData[col_row][i];
	      }
	  }
	while (zero>0)
	  {
	    boardData[col_row][4-zero] = 0;
	    --zero;
          }
      }break;
     
    case RIGHT:
      {
	for(i=3; i>=0; i--)
	  {
	    if(boardData[col_row][i] == 0)
	      {
		++zero;
	      }
	    else
	      {
		boardData[col_row][i+zero] = boardData[col_row][i];
	      }
	  }
	while(zero > 0)
	  {
	    boardData[col_row][zero-1] = 0;
	    --zero;
	  }
      }break;
    }
}

int canWin(int boardData[4][4])
{
  int i,j,flag=0;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      {
	if((boardData[i][j] == boardData[i+1][j]) || (boardData[i][j] == boardData[i][j+1]))
	  {
	    flag = 1;
	    return flag;
          }
      }
  return 0;
}

// Write the number into Board.
int updateBoardData(int boardData[4][4], int x, int y)
{
  if (x == 1)
    {
      if (y == 1)
	{
	      mvprintw(y+1, x+2, "%d", boardData[x-1][y-1]);	    
	      return 1;
	}
       else if (y == 2)
	{
	      mvprintw(y, x+10, "%d", boardData[x-1][y-1]);
	      return 1;
	}
       else if (y == 3)
	{
	      mvprintw(y-1, x+18, "%d", boardData[x-1][y-1]);
	      return 1;
	}
       else if (y == 4)
	{
	      mvprintw(y-2, x+26, "%d", boardData[x-1][y-1]);
	      return 1;
	}
    }
  if (x == 2)
    {
      if (y == 1)
	{
	      mvprintw(y+5, x+1, "%d", boardData[x-1][y-1]);
	      return 1;
	}
       else if (y == 2)
	{
	      mvprintw(y+4, x+9, "%d", boardData[x-1][y-1]);
	      return 1;
	}
       else if (y == 3)
	{
	      mvprintw(y+3, x+17, "%d", boardData[x-1][y-1]);
	      return 1;
	}
       else if (y == 4)
	{
	      mvprintw(y+2, x+25, "%d", boardData[x-1][y-1]);
	      return 1;
	}
    }
  if (x == 3)
    {
      if (y == 1)
	{
	      mvprintw(y+9, x, "%d", boardData[x-1][y-1]);
	      return 1;
	}
      else if (y == 2)
	{
	      mvprintw(y+8, x+8, "%d", boardData[x-1][y-1]);
	      return 1;
	}
       else if (y == 3)
	{
	      mvprintw(y+7, x+16, "%d", boardData[x-1][y-1]);
	      return 1;	    
	}
       else if (y == 4)
	{
	      mvprintw(y+6, x+24, "%d", boardData[x-1][y-1]);
	      return 1;
	}
    }
  if (x == 4)
    {
      if (y == 1)
	{
	      mvprintw(y+13, x-1, "%d", boardData[x-1][y-1]);
	      return 1;
	}
      else if (y == 2)
	{
	      mvprintw(y+12, x+7, "%d", boardData[x-1][y-1]);
	      return 1;
	}
       else if (y == 3)
	{
	      mvprintw(y+11, x+15, "%d", boardData[x-1][y-1]);
	      return 1;
	}
       else if (y == 4)
	{
	      mvprintw(y+10, x+23, "%d", boardData[x-1][y-1]);
	      return 1;
	}
    }
  return 0;
}

int main(int argc, char *argv[])
{
  do{
    initCurses();
  } while (playGame());
  endwin();
  return 0;
}

