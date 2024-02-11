#include "ku.h"
#pragma GCC optimize(2)
void initRecordBorard(void);
void innerLayoutToDisplayArray(void);
void displayBoard(void);
// above are three main part of the game:show the situation and ensure the game can continue
int DecideWin(int x, int y, int n);
int DecideAiWin(int x, int y, int n);
// two judge win,Ai would not use ban rule to kill it self
int mygetline(char s[], int lim);
int ban(int x, int y, int, int time);
struct point AiLieDown(int n, int peoplex, int peopley);
void initscoreboard1(void);
void updatescore(int x, int y, int n);
// the use of score borad largely strengthen the ai
int score(int i, int j, int n);
char arrayForEmptyBoard[SIZE][SIZE * CHARSIZE + 1] =
    {
        "©³©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©Ó©·",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©Ä©à©à©à©à©à©à©à©à©à©à©à©à©à©Ì",
        "©»©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©Û©¿"};
char arrayForDisplayBoard[SIZE][SIZE * CHARSIZE + 1];
char play1Pic[] = "¡ñ";
char play1CurrentPic[] = "¡ø";

char play2Pic[] = "¡ò";
char play2CurrentPic[] = "¡÷";

int arrayForInnerBoardLayout[SIZE][SIZE];
int player;
int main()
{
    player = 1;
    char mode, modetype, aiy;
    int i;
    int liex(char s[]);
    int liey(char s[]);
    int current_player;
    char input[SIZE];
    struct point inputpoint;
    struct point Aipoint;
    initRecordBorard();
    initscoreboard1();
    innerLayoutToDisplayArray();
    displayBoard();
    printf("Work of Ding Tong\n");
    printf("choose:1 to pvp,2 to pvz\n");
    mygetline(input, SIZE);
    for (i = 0; input[i] != '1' && input[i] != '2'; i++)
        ;
    mode = input[i];
    // the main idea of the game is using a for circulation until the winner is defined
    if (mode == '1')
    {
        for (;;)
        {
            printf("input your position:");
            mygetline(input, SIZE);
            if (input[0] == 'q' && input[1] == 'u' && input[2] == 'i' && input[3] == 't')
            {
                exit(0);
            } // quit command
            inputpoint.x = liex(input);
            inputpoint.y = liey(input);
            if (arrayForInnerBoardLayout[inputpoint.x][inputpoint.y] != 0)
            {
                printf("place taken\n");
                continue;
            } // place with point is unavaiable
            if (inputpoint.x == -1 || inputpoint.y == -1)
            {
                printf("wrong position\n");
                continue;
            } // wrong input such as 9w
            arrayForInnerBoardLayout[inputpoint.x][inputpoint.y] = player;
            innerLayoutToDisplayArray();
            if (player == 1)
            {
                arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y] = play1CurrentPic[0];
                arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y + 1] = play1CurrentPic[1];
                // specially define the newest point
                current_player = 1;
                player = 2;
                // change player
            }
            else
            {
                arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y] = play2CurrentPic[0];
                arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y + 1] = play2CurrentPic[1];
                // specially define the newest point
                current_player = 2;
                player = 1;
                // change player
            }
            displayBoard();
            if (DecideWin(inputpoint.x, inputpoint.y, current_player) == 1)
            {
                exit(0);
                // decide wether the winner is confined
            };
        }
    }
    else if (mode == '2')
    {
        printf("input 1 to choose player1,input 2 to choose player2\n");
        scanf("%s", input);
        for (i = 0; input[i] != '1' && input[i] != '2'; i++)
            ;
        modetype = input[i];
        if (modetype == '1')
        {
            for (;;)
            {
                // alike to pvp,just after player input his point,use ai program to form ai's input
                printf("input your position:");
                mygetline(input, SIZE);
                if (input[0] == 'q' && input[1] == 'u' && input[2] == 'i' && input[3] == 't')
                {
                    exit(0);
                }
                inputpoint.x = liex(input);
                inputpoint.y = liey(input);
                if (arrayForInnerBoardLayout[inputpoint.x][inputpoint.y] != 0)
                {
                    printf("place taken\n");
                    continue;
                }
                if (inputpoint.x == -1 || inputpoint.y == -1)
                {
                    printf("wrong position\n");
                    continue;
                }
                arrayForInnerBoardLayout[inputpoint.x][inputpoint.y] = player;
                innerLayoutToDisplayArray();
                if (player == 1)
                {
                    updatescore(inputpoint.x, inputpoint.y, 1);
                    arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y] = play1CurrentPic[0];
                    arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y + 1] = play1CurrentPic[1];
                    // specially define the newest point
                    current_player = 1;
                    player = 2;
                }
                else
                {
                    updatescore(inputpoint.x, inputpoint.y, 2);
                    arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y] = play2CurrentPic[0];
                    arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y + 1] = play2CurrentPic[1];
                    // specially define the newest point
                    current_player = 2;
                    player = 1;
                }
                displayBoard();
                if (DecideWin(inputpoint.x, inputpoint.y, current_player) == 1)
                {
                    exit(0);
                }
                Aipoint = AiLieDown(player, inputpoint.x, inputpoint.y);
                arrayForInnerBoardLayout[Aipoint.x][Aipoint.y] = player;
                innerLayoutToDisplayArray();
                if (player == 1)
                {
                    updatescore(Aipoint.x, Aipoint.y, 1);
                    arrayForDisplayBoard[Aipoint.x][CHARSIZE * Aipoint.y] = play1CurrentPic[0];
                    arrayForDisplayBoard[Aipoint.x][CHARSIZE * Aipoint.y + 1] = play1CurrentPic[1];
                    // specially define the newest point
                    current_player = 1;
                    player = 2;
                }
                else
                {
                    updatescore(Aipoint.x, Aipoint.y, 2);
                    arrayForDisplayBoard[Aipoint.x][CHARSIZE * Aipoint.y] = play2CurrentPic[0];
                    arrayForDisplayBoard[Aipoint.x][CHARSIZE * Aipoint.y + 1] = play2CurrentPic[1];
                    // specially define the newest point
                    current_player = 2;
                    player = 1;
                }
                displayBoard();
                aiy = 'A' + Aipoint.y - 0;
                printf("Aipoint:%d %c\n", 15 - Aipoint.x, aiy);
                // print aipoint
                if (DecideAiWin(Aipoint.x, Aipoint.y, current_player) == 1)
                {
                    exit(0);
                }
            }
        }
        else if (modetype == '2')
        {
            // define the first step of ai,or there would be bug in the for circulation
            // the bug is:once the player counter the situation of "continue",the ai would lie one more point
            arrayForInnerBoardLayout[7][7] = player;
            innerLayoutToDisplayArray();
            if (player == 1)
            {
                arrayForDisplayBoard[7][CHARSIZE * 7] = play1CurrentPic[0];
                arrayForDisplayBoard[7][CHARSIZE * 7 + 1] = play1CurrentPic[1];
                // specially define the newest point
                current_player = 1;
                player = 2;
            }
            else
            {
                arrayForDisplayBoard[7][CHARSIZE * 7] = play2CurrentPic[0];
                arrayForDisplayBoard[7][CHARSIZE * 7 + 1] = play2CurrentPic[1];
                // specially define the newest point
                current_player = 2;
                player = 1;
            }
            updatescore(7, 7, 1);
            displayBoard();
            aiy = 'A' + 7 - 0;
            printf("Aipoint:%d %c\n", 8, aiy);
            if (DecideWin(7, 7, current_player) == 1)
            {
                exit(0);
            }
            i = 0;
            for (;;)
            {
                // alike to pvp,just after player input his point,use ai program to form ai's input
                i++;
                printf("input your position:");
                mygetline(input, SIZE);
                if (input[0] == 'q' && input[1] == 'u' && input[2] == 'i' && input[3] == 't')
                {
                    exit(0);
                }
                inputpoint.x = liex(input);
                inputpoint.y = liey(input);
                if (arrayForInnerBoardLayout[inputpoint.x][inputpoint.y] != 0)
                {
                    printf("place taken\n");
                    continue;
                }
                if (inputpoint.x == -1 || inputpoint.y == -1)
                {
                    printf("wrong position\n");
                    continue;
                }
                arrayForInnerBoardLayout[inputpoint.x][inputpoint.y] = player;
                innerLayoutToDisplayArray();
                if (player == 1)
                {
                    updatescore(inputpoint.x, inputpoint.y, 1);
                    arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y] = play1CurrentPic[0];
                    arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y + 1] = play1CurrentPic[1];
                    // specially define the newest point
                    current_player = 1;
                    player = 2;
                }
                else
                {
                    updatescore(inputpoint.x, inputpoint.y, 2);
                    arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y] = play2CurrentPic[0];
                    arrayForDisplayBoard[inputpoint.x][CHARSIZE * inputpoint.y + 1] = play2CurrentPic[1];
                    // specially define the newest point
                    current_player = 2;
                    player = 1;
                }
                displayBoard();
                if (DecideWin(inputpoint.x, inputpoint.y, current_player) == 1)
                {
                    exit(0);
                }
                Aipoint = AiLieDown(player, inputpoint.x, inputpoint.y);
                arrayForInnerBoardLayout[Aipoint.x][Aipoint.y] = player;
                innerLayoutToDisplayArray();
                if (player == 1)
                {
                    updatescore(Aipoint.x, Aipoint.y, 1);
                    arrayForDisplayBoard[Aipoint.x][CHARSIZE * Aipoint.y] = play1CurrentPic[0];
                    arrayForDisplayBoard[Aipoint.x][CHARSIZE * Aipoint.y + 1] = play1CurrentPic[1];
                    // specially define the newest point
                    current_player = 1;
                    player = 2;
                }
                else
                {
                    updatescore(Aipoint.x, Aipoint.y, 1);
                    arrayForDisplayBoard[Aipoint.x][CHARSIZE * Aipoint.y] = play2CurrentPic[0];
                    arrayForDisplayBoard[Aipoint.x][CHARSIZE * Aipoint.y + 1] = play2CurrentPic[1];
                    // specially define the newest point
                    current_player = 2;
                    player = 1;
                }
                displayBoard();
                aiy = 'A' + Aipoint.y - 0;
                printf("Aipoint:%d %c\n", 15 - Aipoint.x, aiy);
                // print aipoint
                if (DecideAiWin(Aipoint.x, Aipoint.y, current_player) == 1)
                {
                    exit(0);
                }
            }
        }
        else
        {
            printf("Wrong Choice\n");
        }
    }
    else
    {
        printf("Wrong choice!\n");
    }
    return 0;
}

void initRecordBorard(void)
{
    // initally define the board:0 represent place with no point
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            arrayForInnerBoardLayout[i][j] = 0;
}

void initscoreboard1(void)
{
    // initally define the score board:0 represent no point in the board now
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            scoreboard[i][j] = 0;
        }
    }
}

void innerLayoutToDisplayArray(void)
{
    // draw the board
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE * 2 + 1; j++)
            arrayForDisplayBoard[i][j] = arrayForEmptyBoard[i][j];
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (arrayForInnerBoardLayout[i][j] == 1)
            {
                arrayForDisplayBoard[i][CHARSIZE * j] = play1Pic[0];
                arrayForDisplayBoard[i][CHARSIZE * j + 1] = play1Pic[1];
            }
            else if (arrayForInnerBoardLayout[i][j] == 2)
            {
                arrayForDisplayBoard[i][CHARSIZE * j] = play2Pic[0];
                arrayForDisplayBoard[i][CHARSIZE * j + 1] = play2Pic[1];
            }
        }
    }
}

void displayBoard(void)
{
    // print the board
    int i;
    system("clear");
    for (i = 0; i < SIZE; i++)
    {
        printf("%3d %s\n", SIZE - i, arrayForDisplayBoard[i]);
    }
    printf("   ");
    for (i = 0; i < SIZE; i++)
        printf("%2c", 'A' + i);
    printf("\n");
}

int mygetline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

int liey(char s[])
{
    // form alpha to position
    int i;
    for (i = 0; (s[i] < 'A' || s[i] > 'O') && (s[i] < 'a' || s[i] > 'o') && s[i] != '\0'; i++)
        ;
    if (s[i] >= 'A' && s[i] <= 'O')
        return s[i] - 'A';
    else if (s[i] >= 'a' && s[i] <= 'o')
        return s[i] - 'a';
    else
        return -1;
}

int liex(char s[])
{
    // form number to position
    int i;
    for (i = 0; (s[i] < '1' || s[i] > '9') && s[i] != '\0'; i++)
        ;
    if (s[i + 1] <= '5' && s[i + 1] >= '0')
    {
        return 5 - (s[i + 1] - '0');
    }
    else if (s[i] == '\0')
    {
        return -1;
    }
    else
    {
        return 14 - (s[i] - '1');
    }
}

int DecideWin(int x, int y, int n)
{
    // decidewin:the five connection
    int i, j;
    if (player == 2)
    {
        // the black only form five is win,or would touch changlian ban rule
        for (i = 1; x + i < 15 && arrayForInnerBoardLayout[x + i][y] == 1; i++)
            ;
        for (j = 1; x - j >= 0 && arrayForInnerBoardLayout[x - j][y] == 1; j++)
            ;
        if (i + j == 6)
        {
            printf("player1 win!!!\n");
            return 1;
        }
        for (i = 1; y + i < 15 && arrayForInnerBoardLayout[x][y + i] == 1; i++)
            ;
        for (j = 1; y - j >= 0 && arrayForInnerBoardLayout[x][y - j] == 1; j++)
            ;
        if (i + j == 6)
        {
            printf("player1 win!!!\n");
            return 1;
        }
        for (i = 1; x + i < 15 && y + i < 15 && arrayForInnerBoardLayout[x + i][y + i] == 1; i++)
            ;
        for (j = 1; x - j >= 0 && y - j >= 0 && arrayForInnerBoardLayout[x - j][y - j] == 1; j++)
            ;
        if (i + j == 6)
        {
            printf("player1 win!!!\n");
            return 1;
        }
        for (i = 1; x - i >= 0 && y + i <= 14 && arrayForInnerBoardLayout[x - i][y + i] == 1; i++)
            ;
        for (j = 1; x + j <= 14 && y - j >= 0 && arrayForInnerBoardLayout[x + j][y - j] == 1; j++)
            ;
        if (i + j == 6)
        {
            printf("player1 win!!!\n");
            return 1;
        }
        if (ban(x, y, 1, 0) == 1)
        {
            printf("forbidden location:player2 win!!!\n");
            return 1;
        }
        return 0;
    }
    else
    {
        // the white can connect more than five point
        for (i = 1; x + i < 15 && arrayForInnerBoardLayout[x + i][y] == 2; i++)
            ;
        for (j = 1; x - j >= 0 && arrayForInnerBoardLayout[x - j][y] == 2; j++)
            ;
        if (i + j >= 6)
        {
            printf("player2 win!!!\n");
            return 1;
        }
        for (i = 1; y + i < 15 & arrayForInnerBoardLayout[x][y + i] == 2; i++)
            ;
        for (j = 1; y - j >= 0 && arrayForInnerBoardLayout[x][y - j] == 2; j++)
            ;
        if (i + j >= 6)
        {
            printf("player2 win!!!\n");
            return 1;
        }
        for (i = 1; x + i < 15 && y + i < 15 && arrayForInnerBoardLayout[x + i][y + i] == 2; i++)
            ;
        for (j = 1; x - j >= 0 && y - j >= 0 && arrayForInnerBoardLayout[x - j][y - j] == 2; j++)
            ;
        if (i + j >= 6)
        {
            printf("player2 win!!!\n");
            return 1;
        }
        for (i = 1; x - i >= 0 && y + i < 15 && arrayForInnerBoardLayout[x - i][y + i] == 2; i++)
            ;
        for (j = 1; x + j < 15 && y - j >= 0 && arrayForInnerBoardLayout[x + j][y - j] == 2; j++)
            ;
        if (i + j >= 6)
        {
            printf("player2 win!!!\n");
            return 1;
        }
        return 0;
    }
}

int DecideAiWin(int x, int y, int n)
{
    // to avoid ai use ban rule to define itself lose,I write a decidewin for ai
    // this part didn't contain ban rule,once the opponent didn't write ban rule
    // I would get the chance to live again
    int i, j;
    if (player == 2)
    {
        for (i = 1; x + i < 15 && arrayForInnerBoardLayout[x + i][y] == 1; i++)
            ;
        for (j = 1; x - j >= 0 && arrayForInnerBoardLayout[x - j][y] == 1; j++)
            ;
        if (i + j >= 6)
        {
            printf("player1 win!!!\n");
            return 1;
        }
        for (i = 1; y + i < 15 && arrayForInnerBoardLayout[x][y + i] == 1; i++)
            ;
        for (j = 1; y - j >= 0 && arrayForInnerBoardLayout[x][y - j] == 1; j++)
            ;
        if (i + j >= 6)
        {
            printf("player1 win!!!\n");
            return 1;
        }
        for (i = 1; x + i < 15 && y + i < 15 && arrayForInnerBoardLayout[x + i][y + i] == 1; i++)
            ;
        for (j = 1; x - j >= 0 && y - j >= 0 && arrayForInnerBoardLayout[x - j][y - j] == 1; j++)
            ;
        if (i + j >= 6)
        {
            printf("player1 win!!!\n");
            return 1;
        }
        for (i = 1; x - i >= 0 && y + i <= 14 && arrayForInnerBoardLayout[x - i][y + i] == 1; i++)
            ;
        for (j = 1; x + j <= 14 && y - j >= 0 && arrayForInnerBoardLayout[x + j][y - j] == 1; j++)
            ;
        if (i + j >= 6)
        {
            printf("player1 win!!!\n");
            return 1;
        }
        return 0;
    }
    else
    {
        for (i = 1; x + i < 15 && arrayForInnerBoardLayout[x + i][y] == 2; i++)
            ;
        for (j = 1; x - j >= 0 && arrayForInnerBoardLayout[x - j][y] == 2; j++)
            ;
        if (i + j >= 6)
        {
            printf("player2 win!!!\n");
            return 1;
        }
        for (i = 1; y + i < 15 & arrayForInnerBoardLayout[x][y + i] == 2; i++)
            ;
        for (j = 1; y - j >= 0 && arrayForInnerBoardLayout[x][y - j] == 2; j++)
            ;
        if (i + j >= 6)
        {
            printf("player2 win!!!\n");
            return 1;
        }
        for (i = 1; x + i < 15 && y + i < 15 && arrayForInnerBoardLayout[x + i][y + i] == 2; i++)
            ;
        for (j = 1; x - j >= 0 && y - j >= 0 && arrayForInnerBoardLayout[x - j][y - j] == 2; j++)
            ;
        if (i + j >= 6)
        {
            printf("player2 win!!!\n");
            return 1;
        }
        for (i = 1; x - i >= 0 && y + i < 15 && arrayForInnerBoardLayout[x - i][y + i] == 2; i++)
            ;
        for (j = 1; x + j < 15 && y - j >= 0 && arrayForInnerBoardLayout[x + j][y - j] == 2; j++)
            ;
        if (i + j >= 6)
        {
            printf("player2 win!!!\n");
            return 1;
        }
        return 0;
    }
}