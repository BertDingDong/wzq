#include "ku.h"
// under time refers how deep the complex ban is
int ban(int x, int y, int n, int time);
int ChangLian(int x, int y, int n);
int SanSan(int x, int y, int n, int time);
int SiSi(int x, int y, int n, int time);
// under time refers to direction,time2 refers to how deep the complex ban is
int FormHuoSan(int time, int x, int y, int n, int time2);
int FormHuoSi(int time, int x, int y, int n, int time2);
int FormChongSi(int time, int x, int y, int n, int time2);
// this part was written long time before so it's ugly and I'm unwilling to update it
// in the true game I find the deepest complex ban rule is no more than 2 level
// so to avoid too much time waste in ban rule,I limit the level ban rule research
// when time2==1,in FormHuoSan FormHuoSi FormChongSi we don't thought complex ban rule
int ban(int x, int y, int n, int time)
{
    // n refers to current player
    int re = 1;
    if (n == 2)
    {
        return 0; // ban rule only used in black
    }
    if (arrayForInnerBoardLayout[x][y] == 0)
    {
        arrayForInnerBoardLayout[x][y] = 1;
        re = 0; // complex ban rule need complex regard
    }
    // under are three condition of ban rule
    if (ChangLian(x, y, n) == 1)
    {
        arrayForInnerBoardLayout[x][y] = re;
        return 1;
    }
    else if (SanSan(x, y, n, time) == 1)
    {
        arrayForInnerBoardLayout[x][y] = re;
        return 1;
    }
    else if (SiSi(x, y, n, time) == 1)
    {
        arrayForInnerBoardLayout[x][y] = re;
        return 1;
    }
    else
    {
        arrayForInnerBoardLayout[x][y] = re;
        return 0;
    }
}

int ChangLian(int x, int y, int n)
{
    // it's easy to find that we only need to find how much point we connect
    int i = 1, j = 1;
    while (y - j >= 0 && arrayForInnerBoardLayout[x][y - j] == n)
        j++;
    while (y + i <= 14 && arrayForInnerBoardLayout[x][y + i] == n)
        i++;
    if (i + j >= 7)
    {
        return 1;
    }
    i = 1;
    j = 1;
    while (x - j >= 0 && arrayForInnerBoardLayout[x - j][y] == n)
        j++;
    while (x + i <= 14 && arrayForInnerBoardLayout[x + i][y] == n)
        i++;
    if (i + j >= 7)
    {
        return 1;
    }
    i = 1;
    j = 1;
    while (x - j >= 0 && y - j >= 0 && arrayForInnerBoardLayout[x - j][y - j] == n)
        j++;
    while (x + i <= 14 && y + i <= 14 && arrayForInnerBoardLayout[x + i][y + i] == n)
        i++;
    if (i + j >= 7)
    {
        return 1;
    }
    i = 1;
    j = 1;
    while (x - j >= 0 && y + j <= 14 && arrayForInnerBoardLayout[x - j][y + j] == n)
        j++;
    while (x + i <= 14 && y - i >= 0 && arrayForInnerBoardLayout[x + i][y - i] == n)
        i++;
    if (i + j >= 7)
    {
        return 1;
    }
    return 0;
}

int SanSan(int x, int y, int n, int time)
{
    // the definition:form more than two live 3
    int count, i;
    count = 0;
    for (i = 0; i < 5; i++)
    {
        count += FormHuoSan(i, x, y, n, time);
    }
    if (count >= 2)
    {
        return 1;
    }
    return 0;
}

int SiSi(int x, int y, int n, int time)
{
    // the definition:form more than two live 4 or chong 4
    int count, i;
    count = 0;
    for (i = 0; i < 5; i++)
    {
        count += FormHuoSi(i, x, y, n, time);
    }
    for (i = 0; i < 5; i++)
    {
        count += FormChongSi(i, x, y, n, time);
    }
    if (count >= 2)
    {
        return 1;
    }
    return 0;
}

int FormHuoSan(int time, int x, int y, int n, int time2)
{
    // time's more accurate definition is "direction",the four time refers to four direction,I'm unwilling to update it,so tiring
    // the main idea of live 3 is whether it can form live 4,so use the ForHuoSi program
    int i, j, leftX, rightX, leftY, rightY;
    if (time == 1)
    {
        i = 1;
        j = 1;
        while (y - j >= 0 && arrayForInnerBoardLayout[x][y - j] == n)
            j++;
        while (y + i <= 14 && arrayForInnerBoardLayout[x][y + i] == n)
            i++;
        // find how much point we connect and find the possible point to form live 3
        leftY = y - j + 1;
        rightY = y + i - 1;
        if (i + j == 4)
        {
            if ((leftY - 1 >= 0 && FormHuoSi(time, x, leftY - 1, n, time2)) || (rightY + 1 <= 14 && FormHuoSi(time, x, rightY + 1, n, time2)))
                return 1;
        }
        else if (i + j == 3)
        {
            if (leftY - 1 >= 0 && rightY + 1 <= 14 && arrayForInnerBoardLayout[x][leftY - 1] == 0 && arrayForInnerBoardLayout[x][rightY + 1] == 0)
            {
                if (leftY - 3 >= 0 && arrayForInnerBoardLayout[x][leftY - 3] == 0 && arrayForInnerBoardLayout[x][leftY - 2] == 1)
                {
                    if (FormHuoSi(time, x, leftY - 1, n, time2) == 1)
                    {
                        return 1;
                    }
                }
                else if (rightY + 3 <= 14 && arrayForInnerBoardLayout[x][rightY + 3] == 0 && arrayForInnerBoardLayout[x][rightY + 2] == 1)
                {
                    if (FormHuoSi(time, x, rightY + 1, n, time2) == 1)
                    {
                        return 1;
                    }
                }
            }
        }
        else if (i + j == 2)
        {
            if (y - 1 >= 0 && y + 1 <= 14 && arrayForInnerBoardLayout[x][y - 1] == 0 && arrayForInnerBoardLayout[x][y + 1] == 0)
            {
                if (y - 4 >= 0 && arrayForInnerBoardLayout[x][y - 4] == 0 && arrayForInnerBoardLayout[x][y - 3] == 1 && arrayForInnerBoardLayout[x][y - 2] == 1)
                {
                    if (FormHuoSi(time, x, y - 1, n, time2) == 1)
                    {
                        return 1;
                    }
                }
                else if (y + 4 <= 14 && arrayForInnerBoardLayout[x][y + 4] == 0 && arrayForInnerBoardLayout[x][y + 2] == 1 && arrayForInnerBoardLayout[x][y + 3] == 1)
                    if (FormHuoSi(time, x, y + 1, n, time2) == 1)
                    {
                        return 1;
                    }
            }
        }
    }
    else if (time == 2)
    {
        // the same as the former condition,just change the direction
        i = 1;
        j = 1;
        while (x - j >= 0 && arrayForInnerBoardLayout[x - j][y] == n)
            j++;
        while (x + i <= 14 && arrayForInnerBoardLayout[x + i][y] == n)
            i++;
        leftX = x - j + 1;
        rightX = x + i - 1;
        if (i + j == 4)
        {
            if ((leftX - 1 >= 0 && FormHuoSi(time, leftX - 1, y, n, time2)) || (rightX + 1 <= 14 && FormHuoSi(time, rightX + 1, y, n, time2)))
                return 1;
        }
        else if (i + j == 3)
        {
            if (leftX - 1 >= 0 && rightX + 1 <= 14 && arrayForInnerBoardLayout[leftX - 1][y] == 0 && arrayForInnerBoardLayout[rightX + 1][y] == 0)
            {
                if (leftX - 3 >= 0 && arrayForInnerBoardLayout[leftX - 3][y] == 0 && arrayForInnerBoardLayout[leftX - 2][y] == 1)
                {
                    if (FormHuoSi(time, leftX - 1, y, n, time2) == 1)
                    {
                        return 1;
                    }
                }
                else if (rightX + 3 <= 14 && arrayForInnerBoardLayout[rightX + 3][y] == 0 && arrayForInnerBoardLayout[rightX + 2][y] == 1)
                {
                    if (FormHuoSi(time, rightX + 1, y, n, time2) == 1)
                    {
                        return 1;
                    }
                }
            }
        }
        else if (i + j == 2)
        {
            if (x - 1 >= 0 && x + 1 <= 14 && arrayForInnerBoardLayout[x - 1][y] == 0 && arrayForInnerBoardLayout[x + 1][y] == 0)
            {
                if (x - 4 >= 0 && arrayForInnerBoardLayout[x - 4][y] == 0 && arrayForInnerBoardLayout[x - 3][y] == 1 && arrayForInnerBoardLayout[x - 2][y] == 1)
                {
                    if (FormHuoSi(time, x - 1, y, n, time2) == 1)
                    {
                        return 1;
                    }
                }
                else if (x + 4 <= 14 && arrayForInnerBoardLayout[x + 4][y] == 0 && arrayForInnerBoardLayout[x + 2][y] == 1 && arrayForInnerBoardLayout[x + 3][y] == 1)
                    if (FormHuoSi(time, x + 1, y, n, time2) == 1)
                    {
                        return 1;
                    }
            }
        }
    }
    else if (time == 3)
    {
        // the same as the former condition,just change the direction
        i = 1;
        j = 1;
        while (x - j >= 0 && y - j >= 0 && arrayForInnerBoardLayout[x - j][y - j] == n)
            j++;
        while (x + i <= 14 && y + i <= 14 && arrayForInnerBoardLayout[x + i][y + i] == n)
            i++;
        leftX = x - j + 1;
        leftY = y - j + 1;
        rightX = x + i - 1;
        rightY = y + i - 1;
        if (i + j == 4)
        {
            if ((leftX - 1 >= 0 && leftY - 1 >= 0 && FormHuoSi(time, leftX - 1, leftY - 1, n, time2)) || (rightX + 1 <= 14 && rightY + 1 <= 14 && FormHuoSi(time, rightX + 1, rightY + 1, n, time2)))
                return 1;
        }
        else if (i + j == 3)
        {
            if (leftX - 1 >= 0 && rightX + 1 <= 14 && leftY - 1 >= 0 && rightY + 1 <= 14 && arrayForInnerBoardLayout[leftX - 1][leftY - 1] == 0 && arrayForInnerBoardLayout[rightX + 1][rightY + 1] == 0)
            {
                if (leftX - 3 >= 0 && leftY - 3 >= 0 && arrayForInnerBoardLayout[leftX - 3][leftY - 3] == 0 && arrayForInnerBoardLayout[leftX - 2][leftY - 2] == 1)
                {
                    if (FormHuoSi(time, leftX - 1, leftY - 1, n, time2) == 1)
                    {
                        return 1;
                    }
                }
                else if (rightX + 3 <= 14 && rightY + 3 <= 14 && arrayForInnerBoardLayout[rightX + 3][rightY + 3] == 0 && arrayForInnerBoardLayout[rightX + 2][rightY + 2] == 1)
                {
                    if (FormHuoSi(time, rightX + 1, rightY + 1, n, time2) == 1)
                    {
                        return 1;
                    }
                }
            }
        }
        else if (i + j == 2)
        {
            if (x - 1 >= 0 && x + 1 <= 14 && y - 1 >= 0 && y + 1 <= 14 && arrayForInnerBoardLayout[x - 1][y - 1] == 0 && arrayForInnerBoardLayout[x + 1][y + 1] == 0)
            {
                if (x - 4 >= 0 && y - 4 >= 0 && arrayForInnerBoardLayout[x - 4][y - 4] == 0 && arrayForInnerBoardLayout[x - 3][y - 3] == 1 && arrayForInnerBoardLayout[x - 2][y - 2] == 1)
                {
                    if (FormHuoSi(time, x - 1, y - 1, n, time2) == 1)
                    {
                        return 1;
                    }
                }
                else if (x + 4 <= 14 && y + 4 <= 14 && arrayForInnerBoardLayout[x + 4][y + 4] == 0 && arrayForInnerBoardLayout[x + 2][y + 2] == 1 && arrayForInnerBoardLayout[x + 3][y + 3] == 1)
                    if (FormHuoSi(time, x + 1, y + 1, n, time2) == 1)
                    {
                        return 1;
                    }
            }
        }
    }
    else if (time == 4)
    {
        // the same as the former condition,just change the direction
        i = 1;
        j = 1;
        while (x - j >= 0 && y - j >= 0 && arrayForInnerBoardLayout[x - j][y + j] == n)
            j++;
        while (x + i <= 14 && y + i <= 14 && arrayForInnerBoardLayout[x + i][y - i] == n)
            i++;
        leftX = x - j + 1;
        leftY = y - i + 1;
        rightX = x + i - 1;
        rightY = y + j - 1;
        if (i + j == 4)
        {
            if ((leftX - 1 >= 0 && rightY + 1 <= 14 && FormHuoSi(time, leftX - 1, rightY + 1, n, time2)) || (rightX + 1 <= 14 && leftY - 1 >= 0 && FormHuoSi(time, rightX + 1, leftY - 1, n, time2)))
                return 1;
        }
        else if (i + j == 3)
        {
            if (leftX - 1 >= 0 && rightX + 1 <= 14 && leftY - 1 >= 0 && rightY + 1 <= 14 && arrayForInnerBoardLayout[leftX - 1][rightY + 1] == 0 && arrayForInnerBoardLayout[rightX + 1][leftY - 1] == 0)
            {
                if (leftX - 3 >= 0 && rightY + 3 <= 14 && arrayForInnerBoardLayout[leftX - 3][rightY + 3] == 0 && arrayForInnerBoardLayout[leftX - 2][rightY + 2] == 1)
                {
                    if (FormHuoSi(time, leftX - 1, rightY + 1, n, time2) == 1)
                    {
                        return 1;
                    }
                }
                else if (rightX + 3 <= 14 && leftY - 3 >= 0 && arrayForInnerBoardLayout[rightX + 3][leftY - 3] == 0 && arrayForInnerBoardLayout[rightX + 2][leftY - 2] == 1)
                {
                    if (FormHuoSi(time, rightX + 1, leftY - 1, n, time2) == 1)
                    {
                        return 1;
                    }
                }
            }
        }
        else if (i + j == 2)
        {
            if (x - 1 >= 0 && x + 1 <= 14 && y - 1 >= 0 && y + 1 <= 14 && arrayForInnerBoardLayout[x - 1][y + 1] == 0 && arrayForInnerBoardLayout[x + 1][y - 1] == 0)
            {
                if (x - 4 >= 0 && y + 4 <= 14 && arrayForInnerBoardLayout[x - 4][y + 4] == 0 && arrayForInnerBoardLayout[x - 3][y + 3] == 1 && arrayForInnerBoardLayout[x - 2][y + 2] == 1)
                {
                    if (FormHuoSi(time, x - 1, y + 1, n, time2) == 1)
                    {
                        return 1;
                    }
                }
                else if (x + 4 <= 14 && y - 4 >= 0 && arrayForInnerBoardLayout[x + 4][y - 4] == 0 && arrayForInnerBoardLayout[x + 2][y - 2] == 1 && arrayForInnerBoardLayout[x + 3][y - 3] == 1)
                    if (FormHuoSi(time, x + 1, y - 1, n, time2) == 1)
                    {
                        return 1;
                    }
            }
        }
    }
    return 0;
}

int FormHuoSi(int time, int x, int y, int n, int time2)
{
    if (arrayForInnerBoardLayout[x][y] == 2)
    {
        return 0;
    }
    int i = 1, j = 1, leftX, leftY, rightX, rightY, remember = 1;
    if (arrayForInnerBoardLayout[x][y] == 0)
    {
        remember = 0;
    }
    arrayForInnerBoardLayout[x][y] = 1;
    // to judge the complex ban need we define if we lie here what would happen
    if (time == 1)
    {
        while (y - j >= 0 && arrayForInnerBoardLayout[x][y - j] == n)
            j++;
        while (y + i <= 14 && arrayForInnerBoardLayout[x][y + i] == n)
            i++;
        leftY = y - j + 1;
        rightY = y + i - 1;
        // only connect 3 point can form live 4,it's apparent
        if (i + j != 5)
        {
            arrayForInnerBoardLayout[x][y] = remember;
            return 0;
        }
        else
        {
            if ((time2 == 0 && leftY - 1 >= 0 && arrayForInnerBoardLayout[x][leftY - 1] == 0 && ban(x, leftY - 1, n, 1) == 0 &&
                 rightY + 1 <= 14 && arrayForInnerBoardLayout[x][rightY + 1] == 0 && ban(x, rightY + 1, n, 1) == 0) ||
                (time2 == 1 && leftY - 1 >= 0 && arrayForInnerBoardLayout[x][leftY - 1] == 0 &&
                 rightY + 1 <= 14 && arrayForInnerBoardLayout[x][rightY + 1] == 0))
            // thought complex ban rule
            {
                arrayForInnerBoardLayout[x][y] = remember;
                return 1;
            }
        }
    }
    else if (time == 2)
    {
        // just as the former,change the direction
        i = 1;
        j = 1;
        while (x - j >= 0 && arrayForInnerBoardLayout[x - j][y] == n)
            j++;
        while (x + i <= 14 && arrayForInnerBoardLayout[x + i][y] == n)
            i++;
        leftX = x - j + 1;
        rightX = x + i - 1;
        if (i + j != 5)
        {
            arrayForInnerBoardLayout[x][y] = remember;
            return 0;
        }
        else
        {
            if ((time2 == 0 && leftX - 1 >= 0 && arrayForInnerBoardLayout[leftX - 1][y] == 0 && ban(leftX - 1, y, n, 1) == 0 &&
                 rightX + 1 <= 14 && arrayForInnerBoardLayout[rightX + 1][y] == 0 && ban(rightX + 1, y, n, 1) == 0) ||
                (time2 == 1 && leftX - 1 >= 0 && arrayForInnerBoardLayout[leftX - 1][y] == 0 && rightX + 1 <= 14 && arrayForInnerBoardLayout[rightX + 1][y] == 0))
            {
                arrayForInnerBoardLayout[x][y] = remember;
                return 1;
            }
        }
    }
    else if (time == 3)
    {
        // just as the former,change the direction
        i = 1;
        j = 1;
        while (x - j >= 0 && y - j >= 0 && arrayForInnerBoardLayout[x - j][y - j] == n)
            j++;
        while (x + i <= 14 && y + i <= 14 && arrayForInnerBoardLayout[x + i][y + i] == n)
            i++;
        leftX = x - j + 1;
        leftY = y - j + 1;
        rightX = x + i - 1;
        rightY = y + i - 1;
        if (i + j != 5)
        {
            arrayForInnerBoardLayout[x][y] = remember;
            return 0;
        }
        else
        {
            if ((time2 == 0 && leftX - 1 >= 0 && leftY - 1 >= 0 && arrayForInnerBoardLayout[leftX - 1][leftY - 1] == 0 && ban(leftX - 1, leftY - 1, n, 1) == 0 &&
                 rightX + 1 <= 14 && rightY + 1 <= 14 && arrayForInnerBoardLayout[rightX + 1][rightY + 1] == 0 && ban(rightX + 1, rightY + 1, n, 1) == 0) ||
                (time2 == 1 && leftX - 1 >= 0 && leftY - 1 >= 0 && arrayForInnerBoardLayout[leftX - 1][leftY - 1] == 0 &&
                 rightX + 1 <= 14 && rightY + 1 <= 14 && arrayForInnerBoardLayout[rightX + 1][rightY + 1] == 0))
            {
                arrayForInnerBoardLayout[x][y] = remember;
                return 1;
            }
        }
    }
    else if (time == 4)
    {
        // just as the former,change the direction
        i = 1;
        j = 1;
        while (x - j >= 0 && y + j <= 14 && arrayForInnerBoardLayout[x - j][y + j] == n)
            j++;
        while (x + i <= 14 && y - i >= 0 && arrayForInnerBoardLayout[x + i][y - i] == n)
            i++;
        leftX = x - j + 1;
        leftY = y - i + 1;
        rightX = x + i - 1;
        rightY = y + j - 1;
        if (i + j != 5)
        {
            arrayForInnerBoardLayout[x][y] = remember;
            return 0;
        }
        else
        {
            if ((time2 == 0 && leftX - 1 >= 0 && leftY - 1 >= 0 && arrayForInnerBoardLayout[leftX - 1][rightY + 1] == 0 && ban(leftX - 1, rightY + 1, n, 1) == 0 &&
                 rightX + 1 <= 14 && rightY + 1 <= 14 && arrayForInnerBoardLayout[rightX + 1][leftY - 1] == 0 && ban(rightX + 1, leftY - 1, n, 1) == 0) ||
                (time2 == 1 && leftX - 1 >= 0 && leftY - 1 >= 0 && arrayForInnerBoardLayout[leftX - 1][rightY + 1] == 0 &&
                 rightX + 1 <= 14 && rightY + 1 <= 14 && arrayForInnerBoardLayout[rightX + 1][leftY - 1] == 0))
            {
                arrayForInnerBoardLayout[x][y] = remember;
                return 1;
            }
        }
    }
    arrayForInnerBoardLayout[x][y] = remember;
    return 0;
}

int FormChongSi(int time, int x, int y, int n, int time2)
{
    if (arrayForInnerBoardLayout[x][y] == 2)
    {
        return 0;
    }
    int i = 1, j = 1, leftX, leftY, rightX, rightY, remember = 1;
    if (arrayForInnerBoardLayout[x][y] == 0)
    {
        remember = 0;
    }
    arrayForInnerBoardLayout[x][y] = 1;
    int count = 0;
    if (time == 1)
    {
        while (y - j >= 0 && arrayForInnerBoardLayout[x][y - j] == n)
            j++;
        while (y + i <= 14 && arrayForInnerBoardLayout[x][y + i] == n)
            i++;
        leftY = y - j + 1;
        rightY = y + i - 1;
        // chong 4 don't need connect certain number of point,so regard it in different condition
        if (i + j == 2)
        {
            if (leftY - 4 >= 0 && arrayForInnerBoardLayout[x][leftY - 3] == n && arrayForInnerBoardLayout[x][leftY - 2] == n && arrayForInnerBoardLayout[x][leftY - 4] == n && arrayForInnerBoardLayout[x][leftY - 1] == 0)
            {
                if (time2 == 1 || ban(x, leftY - 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightY + 4 <= 14 && arrayForInnerBoardLayout[x][rightY + 4] == n && arrayForInnerBoardLayout[x][rightY + 3] == n && arrayForInnerBoardLayout[x][rightY + 2] == n && arrayForInnerBoardLayout[x][rightY + 1] == 0)
            {
                if (time2 == 1 || ban(x, rightY + 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 3)
        {
            if (leftY - 3 >= 0 && arrayForInnerBoardLayout[x][leftY - 3] == n && arrayForInnerBoardLayout[x][leftY - 2] == n && arrayForInnerBoardLayout[x][leftY - 1] == 0)
            {
                if (time2 == 1 || ban(x, leftY - 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightY + 3 <= 14 && arrayForInnerBoardLayout[x][rightY + 3] == n && arrayForInnerBoardLayout[x][rightY + 2] == n && arrayForInnerBoardLayout[x][rightY + 1] == 0)
            {
                if (time2 == 1 || ban(x, rightY + 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 4)
        {
            if (leftY - 2 >= 0 && arrayForInnerBoardLayout[x][leftY - 2] == n && arrayForInnerBoardLayout[x][leftY - 1] == 0)
            {
                if (time2 == 1 || ban(x, leftY - 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightY + 2 <= 14 && arrayForInnerBoardLayout[x][rightY + 2] == n && arrayForInnerBoardLayout[x][rightY + 1] == 0)
            {
                if (time2 == 1 || ban(x, rightY + 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 5)
        {
            if (((time2 == 0 && leftY - 1 >= 0 && arrayForInnerBoardLayout[x][leftY - 1] == 0 && ban(x, leftY - 1, n, 1) == 0) ||
                 (time2 == 1 && leftY - 1 >= 0 && arrayForInnerBoardLayout[x][leftY - 1] == 0)) ^
                ((time2 == 0 && rightY + 1 <= 14 && arrayForInnerBoardLayout[x][rightY + 1] == 0 && ban(x, rightY + 1, n, 1) == 0) ||
                 (time2 == 1 && rightY + 1 <= 14 && arrayForInnerBoardLayout[x][rightY + 1] == 0)))
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return 1;
            }
        }
        arrayForInnerBoardLayout[x][y] == remember;
        return 0;
    }
    if (time == 2)
    {
        // just change the direction,boring action
        i = 1;
        j = 1;
        while (x - j >= 0 && arrayForInnerBoardLayout[x - j][y] == n)
            j++;
        while (x + i <= 14 && arrayForInnerBoardLayout[x + i][y] == n)
            i++;
        leftX = x - j + 1;
        rightX = x + i - 1;
        if (i + j == 2)
        {
            if (leftX - 4 >= 0 && arrayForInnerBoardLayout[leftX - 4][y] == n && arrayForInnerBoardLayout[leftX - 3][y] == n && arrayForInnerBoardLayout[leftX - 2][y] == n && arrayForInnerBoardLayout[leftX - 1][y] == 0)
            {
                if (time2 == 1 || ban(leftX - 1, y, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightX + 4 <= 14 && arrayForInnerBoardLayout[rightX + 4][y] == n && arrayForInnerBoardLayout[rightX + 3][y] == n && arrayForInnerBoardLayout[rightX + 2][y] == n && arrayForInnerBoardLayout[rightX + 1][y] == 0)
            {
                if (time2 == 1 || ban(rightX + 1, y, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 3)
        {
            if (leftX - 3 >= 0 && arrayForInnerBoardLayout[leftX - 3][y] == n && arrayForInnerBoardLayout[leftX - 2][y] == n && arrayForInnerBoardLayout[leftX - 1][y] == 0)
            {
                if (time2 == 1 || ban(leftX - 1, y, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightX + 3 <= 14 && arrayForInnerBoardLayout[rightX + 3][y] == n && arrayForInnerBoardLayout[rightX + 2][y] == n && arrayForInnerBoardLayout[rightX + 1][y] == 0)
            {
                if (time2 == 1 || ban(rightX + 1, y, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 4)
        {
            if (leftX - 2 >= 0 && arrayForInnerBoardLayout[leftX - 2][y] == n && arrayForInnerBoardLayout[leftX - 1][y] == 0)
            {
                if (time2 == 1 || ban(leftX - 1, y, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightX + 2 <= 14 && arrayForInnerBoardLayout[rightX + 2][y] == n && arrayForInnerBoardLayout[rightX + 1][y] == 0)
            {
                if (time2 == 1 || ban(rightX + 1, y, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 5)
        {
            if (((time2 == 0 && leftX - 1 >= 0 && arrayForInnerBoardLayout[leftX - 1][y] == 0 && ban(leftX - 1, y, n, 1) == 0) ||
                 (time2 == 1 && leftX - 1 >= 0 && arrayForInnerBoardLayout[leftX - 1][y] == 0)) ^
                (time2 == 0 && rightX + 1 <= 14 && arrayForInnerBoardLayout[rightX + 1][y] == 0 && ban(rightX + 1, y, n, 1) == 0 ||
                 (time2 == 1 && rightX + 1 <= 14 && arrayForInnerBoardLayout[rightX + 1][y] == 0)))
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return 1;
            }
        }
        arrayForInnerBoardLayout[x][y] == remember;
        return 0;
    }
    if (time == 3)
    {
        // just change the direction,boring action
        i = 1;
        j = 1;
        while (x - j >= 0 && y - j >= 0 && arrayForInnerBoardLayout[x - j][y - j] == n)
            j++;
        while (x + i <= 14 && y + i <= 14 && arrayForInnerBoardLayout[x + i][y + i] == n)
            i++;
        leftX = x - j + 1;
        leftY = y - j + 1;
        rightX = x + i - 1;
        rightY = y + i - 1;
        if (i + j == 2)
        {
            if (leftX - 4 >= 0 && leftY - 4 >= 0 && arrayForInnerBoardLayout[leftX - 4][leftY - 4] == n && arrayForInnerBoardLayout[leftX - 3][leftY - 3] == n && arrayForInnerBoardLayout[leftX - 2][leftY - 2] == n && arrayForInnerBoardLayout[leftX - 1][leftY - 1] == 0)
            {
                if (time2 == 1 || ban(leftX - 1, leftY - 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightX + 4 <= 14 && rightY + 4 <= 14 && arrayForInnerBoardLayout[rightX + 4][rightY + 4] == n && arrayForInnerBoardLayout[rightX + 3][rightY + 3] == n && arrayForInnerBoardLayout[rightX + 2][rightY + 2] == n && arrayForInnerBoardLayout[rightX + 1][rightY + 1] == 0)
            {
                if (time2 == 1 || ban(rightX + 1, rightY + 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 3)
        {
            if (leftX - 3 >= 0 && leftY - 3 >= 0 && arrayForInnerBoardLayout[leftX - 3][leftY - 3] == n && arrayForInnerBoardLayout[leftX - 2][leftY - 2] == n && arrayForInnerBoardLayout[leftX - 1][leftY - 1] == 0)
            {
                if (time2 == 1 || ban(leftX - 1, leftY - 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightX + 3 <= 14 && rightY + 3 <= 14 && arrayForInnerBoardLayout[rightX + 3][rightY + 3] == n && arrayForInnerBoardLayout[rightX + 2][rightY + 2] == n && arrayForInnerBoardLayout[rightX + 1][rightY + 1] == 0)
            {
                if (time2 == 1 || ban(rightX + 1, rightY + 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 4)
        {
            if (leftX - 2 >= 0 && leftY - 2 >= 0 && arrayForInnerBoardLayout[leftX - 2][leftY - 2] == n && arrayForInnerBoardLayout[leftX - 1][leftY - 1] == 0)
            {
                if (time2 == 1 || ban(leftX - 1, leftY - 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightX + 2 <= 14 && rightY + 2 <= 14 && arrayForInnerBoardLayout[rightX + 2][rightY + 2] == n && arrayForInnerBoardLayout[rightX + 1][rightY + 1] == 0)
            {
                if (time2 == 1 || ban(rightX + 1, rightY + 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 5)
        {
            if (((time2 == 0 && leftX - 1 >= 0 && leftY - 1 >= 0 && arrayForInnerBoardLayout[leftX - 1][leftY - 1] == 0 && ban(leftX - 1, leftY - 1, n, 1) == 0) ||
                 (time2 == 1 && leftX - 1 >= 0 && leftY - 1 >= 0 && arrayForInnerBoardLayout[leftX - 1][leftY - 1] == 0)) ^
                ((time2 == 0 && rightX + 1 <= 14 && rightY + 1 <= 14 && arrayForInnerBoardLayout[rightX + 1][rightY + 1] == 0 && ban(rightX + 1, rightY + 1, n, 1) == 0) ||
                 (time2 == 1 && rightX + 1 <= 14 && rightY + 1 <= 14 && arrayForInnerBoardLayout[rightX + 1][rightY + 1] == 0)))
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return 1;
            }
        }
        arrayForInnerBoardLayout[x][y] == remember;
        return 0;
    }
    if (time == 4)
    {
        // just change the direction,boring action
        i = 1;
        j = 1;
        while (x - j >= 0 && y + j <= 14 && arrayForInnerBoardLayout[x - j][y + j] == n)
            j++;
        while (x + i <= 14 && y - i >= 0 && arrayForInnerBoardLayout[x + i][y - i] == n)
            i++;
        leftX = x - j + 1;
        leftY = y - i + 1;
        rightX = x + i - 1;
        rightY = y + j - 1;
        if (i + j == 2)
        {
            if (leftX - 4 >= 0 && rightY + 4 <= 14 && arrayForInnerBoardLayout[leftX - 4][rightY + 4] == n && arrayForInnerBoardLayout[leftX - 3][rightY + 3] == n && arrayForInnerBoardLayout[leftX - 2][rightY + 2] == n && arrayForInnerBoardLayout[leftX - 1][rightY + 1] == 0)
            {
                if (time2 == 1 || ban(leftX - 1, rightY + 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightX + 4 <= 14 && leftY - 4 >= 0 && arrayForInnerBoardLayout[rightX + 4][leftY - 4] == n && arrayForInnerBoardLayout[rightX + 3][leftY - 3] == n && arrayForInnerBoardLayout[rightX + 2][leftY - 2] == n && arrayForInnerBoardLayout[rightX + 1][leftY - 1] == 0)
            {
                if (time2 == 1 || ban(rightX + 1, leftY - 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 3)
        {
            if (leftX - 3 >= 0 && rightY + 3 <= 14 && arrayForInnerBoardLayout[leftX - 3][rightY + 3] == n && arrayForInnerBoardLayout[leftX - 2][rightY + 2] == n && arrayForInnerBoardLayout[leftX - 1][rightY + 1] == 0)
            {
                if (time2 == 1 || ban(leftX - 1, rightY + 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightX + 3 <= 14 && leftY - 3 >= 0 && arrayForInnerBoardLayout[rightX + 3][leftY - 3] == n && arrayForInnerBoardLayout[rightX + 2][leftY - 2] == n && arrayForInnerBoardLayout[rightX + 1][leftY - 1] == 0)
            {
                if (time2 == 1 || ban(rightX + 1, leftY - 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 4)
        {
            if (leftX - 2 >= 0 && rightY + 2 <= 14 && arrayForInnerBoardLayout[leftX - 2][rightY + 2] == n && arrayForInnerBoardLayout[leftX - 1][rightY + 1] == 0)
            {
                if (time2 == 1 || ban(leftX - 1, rightY + 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (rightX + 2 <= 14 && leftY - 2 >= 0 && arrayForInnerBoardLayout[rightX + 2][leftY - 2] == n && arrayForInnerBoardLayout[rightX + 1][leftY - 1] == 0)
            {
                if (time2 == 1 || ban(rightX + 1, leftY - 1, n, 1) == 0)
                {
                    count++;
                }
            }
            if (count != 0)
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return count;
            }
        }
        else if (i + j == 5)
        {
            if (((time2 == 0 && leftX - 1 >= 0 && rightY + 1 <= 14 && arrayForInnerBoardLayout[leftX - 1][rightY + 1] == 0 && ban(leftX - 1, rightY + 1, n, 1) == 0) ||
                 (time2 == 1 && leftX - 1 >= 0 && rightY + 1 <= 14 && arrayForInnerBoardLayout[leftX - 1][rightY + 1] == 0)) ^
                ((time2 == 0 && rightX + 1 <= 14 && leftY - 1 >= 0 && arrayForInnerBoardLayout[rightX + 1][leftY - 1] == 0 && ban(rightX + 1, leftY - 1, n, 1) == 0) ||
                 (time2 == 1 && rightX + 1 <= 14 && leftY - 1 >= 0 && arrayForInnerBoardLayout[rightX + 1][leftY - 1] == 0)))
            {
                arrayForInnerBoardLayout[x][y] == remember;
                return 1;
            }
        }
        arrayForInnerBoardLayout[x][y] == remember;
        return 0;
    }
    arrayForInnerBoardLayout[x][y] == remember;
    return 0;
}