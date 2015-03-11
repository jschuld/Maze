#include "stdio.h"


char solStr[200];
unsigned char strPos = 0;

int startCol = 1;
int startRow = 0;

#define MAZE_ROW_SIZE 7
#define MAZE_COL_SIZE 11

unsigned char stepNext(int currCol, int currRow, char skipPos);

int maze[MAZE_ROW_SIZE][MAZE_COL_SIZE] = {
   {0,1,0,0,0,0,0,0,0,0,0},
   {0,1,1,1,1,1,1,0,0,0,0},
   {0,0,0,1,0,0,1,1,0,0,0},
   {0,0,1,1,0,0,1,0,0,0,0},
   {0,0,0,0,0,1,1,1,1,0,0},
   {0,0,1,1,1,1,0,0,1,0,0},
   {0,0,0,1,0,0,0,0,0,0,0},
};


void main(void)
{
  if(stepNext(startCol, startRow, 3))
   {
      printf("Solution:%s\n", solStr);
      printf("Exit at %s\n",&solStr[strPos-7]);
   }
   else
   {
      printf("No Solution Found!!!!\r\n");
   }
}

//returns 0, could not step further
//returns 1, reached exit
//skipPos: previous position (0=right, 1=down, 2=left, 3=up)
unsigned char stepNext(int currCol, int currRow, char skipPos)
{

   //return if given location a solid wall
   if(!maze[currRow][currCol]) return 0;

	//is given location the exit?
   //(skip if position is start)
   if((currRow != startRow) || (currCol != startCol))
   {
	  char exitFound=0;
      if(currCol == MAZE_COL_SIZE -1) exitFound = 1;
      else if(currRow == MAZE_ROW_SIZE -1) exitFound = 1;
      else if(currCol == 0) exitFound = 1;
      else if(currRow == 0) exitFound = 1;

      if(exitFound)
      {
    	  strPos += sprintf(&solStr[strPos], "(%02d,%02d)", currCol, currRow);
    	  return 1;
      }
   }

   //add curr step to solution string
   strPos += sprintf(&solStr[strPos], "(%02d,%02d)", currCol, currRow);

   //current locaion valid, try next (skip last position)
   //first try right
   if(skipPos!=0)
	   if(stepNext(currCol+1, currRow, 2)) return 1;
   //can't. try down
   if(skipPos!=1)
	   if(stepNext(currCol, currRow+1, 3)) return 1;
   //can't. try left
   if(skipPos!=2)
	   if(stepNext(currCol-1, currRow, 0)) return 1;
   //can't. try up
   if(skipPos!=3)
	   if(stepNext(currCol, currRow-1, 1)) return 1;


   //if reaches here, reached a dead end
   strPos -= 7; //remove previously added string (xx,yy)
   
   return 0;
}




