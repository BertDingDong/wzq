#ifndef _KU_H
#define _KU_H
// I forget why I use those ku program......
// It seems only stdio.h is used?you can try to delete some of them to find whether the code returns error
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// under are fundermental define of the board
#define SIZE 15
#define CHARSIZE 2
//under are the score of different type of point,according to some message in the web,those definition are best
#define WULIAN 100000
#define HUOSI 10000
#define LIANSI 1000
#define TIAOSI 1000
#define LIANHUOSAN 1000
#define TIAOHUOSAN 1000
#define JIAHUOSAN 100
#define MIANSAN 100
#define HUOER 100
#define MIANER 10
//struct point
struct point
{
      int x;
      int y;
};
//the two most important array,I put them in ku so that each part all can use them
int arrayForInnerBoardLayout[SIZE][SIZE];
int scoreboard[SIZE][SIZE];
#endif