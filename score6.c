#include "ku.h"
#define LEN 9
int score(int x, int y, int n)
{
    //the score I use the idea of lnode which we learned in last class
    struct lnode
    {
        int arr[LEN];
        struct lnode *next;
    };
    if (arrayForInnerBoardLayout[x][y] == n || arrayForInnerBoardLayout[x][y] == 3 - n)
    {
        return -1;
        //place with point is unneccessary to consider
    }
    int i, l4, t4, lh3, th3, jh3, m3, h2, m2, num, bound, score = 0;//from left to right is:lian 4,tiao 4,lian huo 3,tiao huo 3,jia huo 3,mian 3,huo 2,mian 2,num is how many points connected,bound is whether the point is bounded by board or opponent
    struct lnode leftnode, upnode, leftupnode, rightupnode;
    //under are record the condition around the point to four array
    for (i = -4; i <= 4; i++)
    {
        if (x - i > 14 || x - i < 0)
        {
            upnode.arr[4 + i] = 3 - n;
        }
        else if (arrayForInnerBoardLayout[x - i][y] == 0)
        {
            upnode.arr[4 + i] = 0;
        }
        else if (arrayForInnerBoardLayout[x - i][y] == 1)
        {
            upnode.arr[4 + i] = 1;
        }
        else if (arrayForInnerBoardLayout[x - i][y] == 2)
        {
            upnode.arr[4 + i] = 2;
        }
    }
    for (i = -4; i <= 4; i++)
    {
        if (y - i > 14 || y - i < 0)
        {
            leftnode.arr[4 + i] = 3 - n;
        }
        else if (arrayForInnerBoardLayout[x][y - i] == 0)
        {
            leftnode.arr[4 + i] = 0;
        }
        else if (arrayForInnerBoardLayout[x][y - i] == 1)
        {
            leftnode.arr[4 + i] = 1;
        }
        else if (arrayForInnerBoardLayout[x][y - i] == 2)
        {
            leftnode.arr[4 + i] = 2;
        }
    }
    for (i = -4; i <= 4; i++)
    {
        if (x - i > 14 || x - i < 0 || y - i > 14 || y - i < 0)
        {
            leftupnode.arr[4 + i] = 3 - n;
        }
        else if (arrayForInnerBoardLayout[x - i][y - i] == 0)
        {
            leftupnode.arr[4 + i] = 0;
        }
        else if (arrayForInnerBoardLayout[x - i][y - i] == 1)
        {
            leftupnode.arr[4 + i] = 1;
        }
        else if (arrayForInnerBoardLayout[x - i][y - i] == 2)
        {
            leftupnode.arr[4 + i] = 2;
        }
    }
    for (i = -4; i <= 4; i++)
    {
        if (x - i > 14 || x - i < 0 || y + i > 14 || y + i < 0)
        {
            rightupnode.arr[4 + i] = 3 - n;
        }
        else if (arrayForInnerBoardLayout[x - i][y + i] == 0)
        {
            rightupnode.arr[4 + i] = 0;
        }
        else if (arrayForInnerBoardLayout[x - i][y + i] == 1)
        {
            rightupnode.arr[4 + i] = 1;
        }
        else if (arrayForInnerBoardLayout[x - i][y + i] == 2)
        {
            rightupnode.arr[4 + i] = 2;
        }
    }
    struct lnode *p;
    int *a;
    leftnode.next = &upnode;
    upnode.next = &leftupnode;
    leftupnode.next = &rightupnode;
    rightupnode.next = NULL;
    //above are forming a lnode table
    for (p = &leftnode; p != NULL; p = p->next)
    {
        //search each node of lnode table
        //consider different type of point and their score,boring task
        l4 = t4 = lh3 = th3 = jh3 = m3 = h2 = m2 = num = bound = 0;//from left to right is:lian 4,tiao 4,lian huo 3,tiao huo 3,jia huo 3,mian 3,huo 2,mian 2,num is how many points connected,bound is whether the point is bounded by board or opponent
        a = p->arr + 4;
        // normal condition
        for (i = 1; i <= 4 && (*(a + i) == n); i++)
        {
            num++;
        }
        if ( *(a + i) == 3 - n)
        {
            bound++;
        }
        for (i = 1; i <= 4 && (*(a - i) == n); i++)
        {
            num++;
        }
        if ( *(a - i) == 3 - n)
        {
            bound++;
        }
        // huo 2
        if (a[-2] == 0 && a[-1] == 0 && a[1] == n && a[2] == 0 && a[3] == 0)
        {
            ++h2;
        }
        if (a[-3] == 0 && a[-2] == 0 && a[-1] == n && a[1] == 0 && a[2] == 0)
        {
            ++h2;
        }
        if (a[-1] == 0 && a[1] == n && a[2] == 0 && a[3] == 0 && a[4] == 0)
        {
            ++h2;
        }
        if (a[-2] == 0 && a[-1] == n && a[1] == 0 && a[2] == 0 && a[3] == 0)
        {
            ++h2;
        }
        if (a[-4] == 0 && a[-3] == 0 && a[-2] == 0 && a[-1] == n && a[1] == 0)
        {
            ++h2;
        }
        if (a[-2] == 0 && a[-1] == 0 && a[1] == 0 && a[2] == n && a[3] == 0)
        {
            ++h2;
        }
        if (a[-4] == 0 && a[-3] == 0 && a[-2] == n && a[-1] == 0 && a[1] == 0)
        {
            ++h2;
        }
        if (a[-3] == 0 && a[-2] == n && a[-1] == 0 && a[1] == 0 && a[2] == 0)
        {
            ++h2;
        }
        if (a[-1] == 0 && a[1] == 0 && a[2] == n && a[3] == 0 && a[4] == 0)
        {
            ++h2;
        }
        if (a[-1] == 0 && a[1] == 0 && a[2] == 0 && a[3] == n && a[4] == 0)
        {
            ++h2;
        }
        if (a[-4] == 0 && a[-3] == n && a[-2] == 0 && a[-1] == 0 && a[1] == 0)
        {
            ++h2;
        }
        // mian 2
        if (a[-1] == 3 - n && a[1] == n && a[2] == 0 && a[3] == 0 && a[4] == 0)
        {
            ++m2;
        }
        if (a[-2] == 3 - n && a[-1] == n && a[1] == 0 && a[2] == 0 && a[3] == 0)
        {
            ++m2;
        }
        if (a[-4] == 0 && a[-3] == 0 && a[-2] == 0 && a[-1] == n && a[1] == 3 - n)
        {
            ++m2;
        }
        if (a[-3] == 0 && a[-2] == 0 && a[-1] == 0 && a[1] == n && a[2] == 3 - n)
        {
            ++m2;
        }
        if (a[-1] == 3 - n && a[1] == 0 && a[2] == n && a[3] == 0 && a[4] == 0)
        {
            ++m2;
        }
        if (a[-3] == 3 - n && a[-2] == n && a[-1] == 0 && a[1] == 0 && a[2] == 3 - n)
        {
            ++m2;
        }
        if (a[-4] == 0 && a[-3] == 0 && a[-2] == n && a[-1] == 0 && a[1] == 3 - n)
        {
            ++m2;
        }
        if (a[-2] == 0 && a[-1] == 0 && a[1] == 0 && a[2] == n && a[3] == 3 - n)
        {
            ++m2;
        }
        if (a[-1] == 3 - n && a[1] == 0 && a[2] == 0 && a[3] == n && a[4] == 0)
        {
            ++m2;
        }
        if (a[-4] == 3 - n && a[-3] == n && a[-2] == 0 && a[-1] == 0 && a[1] == 0)
        {
            ++m2;
        }
        if (a[-4] == 0 && a[-3] == n && a[-2] == 0 && a[-1] == 0 && a[1] == 3 - n)
        {
            ++m2;
        }
        if (a[-1] == 0 && a[1] == 0 && a[2] == 0 && a[3] == n && a[4] == 3 - n)
        {
            ++m2;
        }
        if (a[1] == 0 && a[2] == 0 && a[3] == 0 && a[4] == n)
        {
            ++m2;
        }
        if (a[-4] == n && a[-3] == 0 && a[-2] == 0 && a[-1] == 0)
        {
            ++m2;
        }
        if (a[-3] == 3 - n && a[-2] == 0 && a[-1] == 0 && a[1] == n && a[2] == 0 && a[3] == 3 - n)
        {
            ++m2;
        }
        if (a[-4] == 3 - n && a[-3] == 0 && a[-2] == 0 && a[-1] == n && a[1] == 0 && a[2] == 3 - n)
        {
            ++m2;
        }
        if (a[-3] == 3 - n && a[-2] == 0 && a[-1] == n && a[1] == 0 && a[2] == 0 && a[3] == 3 - n)
        {
            ++m2;
        }
        if (a[-2] == 3 - n && a[-1] == 0 && a[1] == n && a[2] == 0 && a[3] == 0 && a[4] == 3 - n)
        {
            ++m2;
        }
        if (a[-2] == 3 - n && a[-1] == 0 && a[1] == 0 && a[2] == n && a[3] == 0 && a[4] == 3 - n)
        {
            ++m2;
        }
        if (a[-4] == 3 - n && a[-3] == 0 && a[-2] == n && a[-1] == 0 && a[1] == 0 && a[2] == 3 - n)
        {
            ++m2;
        }
        // tiao 3
        if (bound == 0)
        {
            if (num == 0)
            {
                if (a[-4] == 0 && a[-3] == n && a[-2] == n && a[-1] == 0)
                {
                    ++th3;
                }
                if (a[1] == 0 && a[2] == n && a[3] == n && a[4] == 0)
                {
                    ++th3;
                }
            }
            if (num == 1)
            {
                if (a[-4] == 0 && a[-3] == n && a[-2] == 0 && a[-1] == n)
                {
                    ++th3;
                }
                if (a[1] == n && a[2] == 0 && a[3] == n && a[4] == 0)
                {
                    ++th3;
                }
                if (a[3] == 0 && a[2] == n && a[-1] == n)
                {
                    ++th3;
                }
                if (a[1] == n && a[-2] == n && a[-3] == 0)
                {
                    ++th3;
                }
            }
        }
        // jia huo 3
        if (num == 2 && bound == 0)
        {
            if (a[-3] == 3 - n && a[-2] == 0 && a[-1] == n && a[1] == n && a[2] == 0 && a[3] == 3 - n)
            {
                jh3 = 1;
            }
            else if (a[-4] == 3 - n && a[-3] == 0 && a[-2] == n && a[-1] == n && a[1] == 0 && a[2] == 3 - n)
            {
                jh3 = 1;
            }
            else if (a[-2] == 3 - n && a[-1] == 0 && a[1] == n && a[2] == n && a[3] == 0 && a[4] == 3 - n)
            {
                jh3 = 1;
            }
            else if (a[-3] != n && a[-2] == 0 && a[-1] == n && a[1] == n && a[2] == 0 && a[3] != n)
            {
                jh3 = 0;
            }
            else if (a[-4] != n && a[-3] == 0 && a[-2] == n && a[-1] == n && a[1] == 0 && a[2] != n)
            {
                jh3 = 0;
            }
            else if (a[-2] != n && a[-1] == 0 && a[1] == n && a[2] == n && a[3] == 0 && a[4] != n)
            {
                jh3 = 0;
            }
        }
        // mian 3
        if (a[-1] == 3 - n && a[1] == n && a[2] == n && a[3] == 0 && a[4] == 0)
        {
            m3++;
        }
        if (a[-2] == 3 - n && a[-1] == n && a[1] == n && a[2] == 0 && a[3] == 0)
        {
            m3++;
        }
        if (a[-3] == 3 - n && a[-2] == n && a[-1] == n && a[1] == 0 && a[2] == 0)
        {
            m3++;
        }
        if (a[3] == 3 - n && a[2] == n && a[1] == n && a[-1] == 0 && a[-2] == 0)
        {
            m3++;
        }
        if (a[1] == 3 - n && a[-1] == n && a[-2] == n && a[-3] == 0 && a[-4] == 0)
        {
            m3++;
        }
        if (a[2] == 3 - n && a[1] == n && a[-1] == n && a[-2] == 0 && a[-3] == 0)
        {
            m3++;
        }
        if (a[-1] == 3 - n && a[1] == n && a[2] == 0 && a[3] == n && a[4] == 0)
        {
            m3++;
        }
        if (a[-2] == 3 - n && a[-1] == n && a[1] == 0 && a[2] == n && a[3] == 0)
        {
            m3++;
        }
        if (a[-4] == 3 - n && a[-3] == n && a[-2] == n && a[-1] == 0 && a[1] == 0)
        {
            m3++;
        }
        if (a[4] == 3 - n && a[3] == n && a[2] == n && a[1] == 0 && a[-1] == 0)
        {
            m3++;
        }
        if (a[1] == 3 - n && a[-1] == n && a[-2] == 0 && a[-3] == n && a[-4] == 0)
        {
            m3++;
        }
        if (a[2] == 3 - n && a[1] == n && a[-1] == 0 && a[-2] == n && a[-3] == 0)
        {
            m3++;
        }
        if (a[-1] == 3 - n && a[1] == 0 && a[2] == n && a[3] == n && a[4] == 0)
        {
            m3++;
        }
        if (a[-3] == 3 - n && a[-2] == n && a[-1] == 0 && a[1] == n && a[2] == 0)
        {
            m3++;
        }
        if (a[-4] == 3 - n && a[-3] == n && a[-2] == 0 && a[-1] == n && a[1] == 0)
        {
            m3++;
        }
        if (a[4] == 3 - n && a[3] == n && a[2] == 0 && a[1] == n && a[-1] == 0)
        {
            m3++;
        }
        if (a[1] == 3 - n && a[-1] == 0 && a[-2] == n && a[-3] == n && a[-4] == 0)
        {
            m3++;
        }
        if (a[3] == 3 - n && a[2] == n && a[0] == 0 && a[-1] == n && a[-2] == 0)
        {
            m3++;
        }
        if (a[1] == n && a[2] == 0 && a[3] == 0 && a[4] == n)
        {
            m3++;
        }
        if (a[-1] == n && a[1] == 0 && a[2] == 0 && a[3] == n)
        {
            m3++;
        }
        if (a[-1] == n && a[-2] == 0 && a[-3] == 0 && a[-4] == n)
        {
            m3++;
        }
        if (a[-1] == 0 && a[-2] == 0 && a[-3] == n && a[-4] == n)
        {
            m3++;
        }
        if (a[-3] == n && a[-2] == 0 && a[-1] == 0 && a[1] == n)
        {
            m3++;
        }
        if (a[1] == 0 && a[2] == 0 && a[3] == n && a[4] == n)
        {
            m3++;
        }
        if (a[1] == 0 && a[2] == n && a[3] == 0 && a[4] == n)
        {
            m3++;
        }
        if (a[-2] == n && a[-1] == 0 && a[1] == 0 && a[2] == n)
        {
            m3++;
        }
        if (a[-1] == 0 && a[-2] == n && a[-3] == 0 && a[-4] == n)
        {
            m3++;
        }
        // chong 4
        if (num == 0)
        {
            if (a[-1] == 0 && a[-2] == n && a[-3] == n && a[-4] == n)
            {
                t4++;
            }
            if (a[1] == 0 && a[2] == n && a[3] == n && a[4] == n)
            {
                t4++;
            }
        }
        if (num == 1)
        {
            if (a[-1] == n && a[-2] == 0 && a[-3] == n && a[-4] == n)
            {
                t4++;
            }
            if (a[1] == n && a[2] == 0 && a[3] == n && a[4] == n)
            {
                t4++;
            }
            if (a[-3] == n && a[-2] == n && a[-1] == 0 && a[1] == n)
            {
                t4++;
            }
            if (a[-1] == n && a[1] == 0 && a[2] == n && a[3] == n)
            {
                t4++;
            }
        }
        if (num == 2)
        {
            if (a[1] == n && a[2] == n && a[3] == 0 && a[4] == n)
            {
                t4++;
            }
            if (a[-3] == n && a[-2] == 0 && a[-1] == n && a[1] == n)
            {
                t4++;
            }
            if (a[3] == n && a[2] == 0 && a[1] == n && a[-1] == n)
            {
                t4++;
            }
            if (a[-1] == n && a[-2] == n && a[-3] == 0 && a[-4] == n)
            {
                t4++;
            }
            if (a[2] == n && a[-2] == n && a[-1] == n && a[1] == 0)
            {
                t4++;
            }
            if (a[-2] == n && a[2] == n && a[1] == n && a[-1] == 0)
            {
                t4++;
            }
        }
        // count
        if (num == 4||(n==2&&num>4))
            score += WULIAN;
        if (num == 3 && bound == 0)
            score += HUOSI;
        if (num == 3 && bound == 1)
            score += LIANSI;
        score += t4 * TIAOSI;
        if (num == 2 && jh3 == 1)
            score += JIAHUOSAN;
        if (num == 2 && jh3 == 0)
            score += LIANHUOSAN;
        score += th3 * TIAOHUOSAN;
        score += m3 * MIANSAN;
        score += h2 * HUOER;
        score += m2 * MIANER;
    }
    return score;
}