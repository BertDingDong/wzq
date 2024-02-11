#include "ku.h"
int ban(int x, int y, int n,int time);
struct point AiLieDown(int n, int peoplex, int peopley);
int score(int x, int y, int n);
void updatescore(int x, int y, int n);
void initroad();
void formroad(int left, int right);
struct point road[SIZE * SIZE];
struct point AiLieDown(int n, int peoplex, int peopley)
{
    // the main idea of ai is deep searching,odd level I regard as useless because the attack without defence is meaningless
    // the six level is too fast and the eight level have the danger of out time,so I use the six level last
    // the technology I used contains: alpha-beta cut,min-max searching,best road forming,artificial define search width
    // hash table may be useful in this part,but it didn't makes eight level available and it has risk of hash damage,so I abandone this
    initroad();
    formroad(0, 224);
    // those two program is to form the best road of searching
    static int time = 0;
    struct point aipoint;
    struct point currentpoint;
    int i = 0;
    int max1, max3, min2, min4, max5, min6, x1, x2, x3, x4, x5, x6, y1, y2, y3, y4, y5, y6, score1, score2, score3, score4, score5, score6,
        re1, re2, re3, re4, re5, re6;                                                 // re refers to remember
    int limit1 = 15, limit2 = 10, limit3 = 20, limit4 = 20, limit5 = 30, limit6 = 30; // limit define how width we search in each level
    int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0;       // count how much point we have searched
    max1 = -200000;
    if (n == 1 && time == 0 && ((peoplex == 6 && peopley == 8) || (peoplex == 8 && peopley == 8) || (peoplex == 6 && peopley == 6) || (peoplex == 8 && peopley == 6)))
    {
        aipoint.x = peoplex + 2;
        if (aipoint.x == 8)
        {
            aipoint.y = peopley;
            time = 1;
            return aipoint;
        }
        aipoint.x = peoplex;
        aipoint.y = peopley + 2;
        if (aipoint.y == 8)
        {
            time = 1;
            return aipoint;
        }
        aipoint.y = peopley - 2;
        time = 1;
        return aipoint;
    } // artficially define the best open game type
    time = 1;
    if (scoreboard[(road[0]).x][(road[0]).y] >= 100000)
    {
        for (i = 0; scoreboard[(road[i]).x][(road[i]).y] >= 100000; i++)
        {
            if (score((road[i]).x, (road[i]).y, n) >= 100000)
            {
                aipoint.x = (road[i]).x;
                aipoint.y = (road[i]).y;
                return aipoint;
            }
        }
        aipoint.x = (road[0]).x;
        aipoint.y = (road[0]).y;
        return aipoint;
    }
    // above are use to find the killing point
    for (count1 = 0; count1 < 225; count1++)
    {
        // deep searching,use the road we formed
        x1 = (road[count1]).x;
        y1 = (road[count1]).y;//take the point out
        min2 = 200000;//initially define to ensure the search is meaningful
        re1 = arrayForInnerBoardLayout[x1][y1];//record the situation,after put it back
        score1 = score(x1, y1, n);//calculate the score
        if (score1 >= 100000)
        {
            max1 = score1;
            aipoint.x = x1;
            aipoint.y = y1;
            return aipoint;
            //research after killing point is meanlingless and may cause problem
        }
        arrayForInnerBoardLayout[x1][y1] = n;//thougt as if we lie a point here and what would happen
        limit2 = 20;//limit2 limit how much point we search in second level
        //under the definition is alike so I don't write again
        for (count2 = 0; count2 <= 224;)
        {
            x2 = (road[count2]).x;
            y2 = (road[count2]).y;
            if (arrayForInnerBoardLayout[x2][y2] != 0)
            {
                count2++;
                limit2++;
                continue;
                // avoid point we searched in the former level cause wrong
            }
            count2++;
            max3 = -200000;
            re2 = arrayForInnerBoardLayout[x2][y2];
            score2 = score(x2, y2, 3 - n);
            if (score2 >= 100000)
            {
                min2 = score1 - score2;
                break;
                //research after killing point is meanlingless and may cause problem
            }
            arrayForInnerBoardLayout[x2][y2] = 3 - n;
            limit3 = 50;
            for (count3 = 0; count3 <= 224;)
            {
                x3 = (road[count3]).x;
                y3 = (road[count3]).y;
                if (arrayForInnerBoardLayout[x3][y3] != 0)
                {
                    count3++;
                    limit3++;
                    continue;
                }
                count3++;
                min4 = 200000;
                re3 = arrayForInnerBoardLayout[x3][y3];
                score3 = score(x3, y3, n);
                if (score3 >= 100000)
                {
                    max3 = score1 - score2 + score3;
                    break;
                    //research after killing point is meanlingless and may cause problem
                }
                arrayForInnerBoardLayout[x3][y3] = n;
                limit4 = 50;
                for (count4 = 0; count4 <= 224;)
                {
                    x4 = (road[count4]).x;
                    y4 = (road[count4]).y;
                    if (arrayForInnerBoardLayout[x4][y4] != 0)
                    {
                        count4++;
                        limit4++;
                        continue;
                    }
                    count4++;
                    max5 = -200000;
                    re4 = arrayForInnerBoardLayout[x4][y4];
                    score4 = score(x4, y4, 3 - n);
                    if (score4 >= 100000)
                    {
                        min4 = score1 - score2 + score3 - score4;
                        break;
                        //research after killing point is meanlingless and may cause problem
                    }
                    arrayForInnerBoardLayout[x4][y4] = 3 - n;
                    for (count5 = 0; count5 <= 224;)
                    {
                        x5 = (road[count5]).x;
                        y5 = (road[count5]).y;
                        if (arrayForInnerBoardLayout[x5][y5] != 0)
                        {
                            count5++;
                            continue;
                        }
                        count5++;
                        min6 = 200000;
                        re5 = arrayForInnerBoardLayout[x5][y5];
                        score5 = score(x5, y5, n);
                        arrayForInnerBoardLayout[x5][y5] = n;
                        for (count6 = 0; count6 < 224;)
                        {
                            x6 = (road[count6]).x;
                            y6 = (road[count6]).y;
                            if (arrayForInnerBoardLayout[x6][y6] != 0)
                            {
                                count6++;
                                continue;
                            }
                            count6++;
                            score6 = score(x6, y6, 3 - n);
                            if (min6 > score1 - score2 + score3 - score4 + score5 - score6)
                            {
                                min6 = score1 - score2 + score3 - score4 + score5 - score6;
                            }
                            if (min6 <= max5)
                            {
                                min6 = -200000;
                                break;
                                // alpha-beta cut
                            }
                        }
                        arrayForInnerBoardLayout[x5][y5] = re5;
                        if (max5 < min6)
                        {
                            max5 = min6;
                        }
                        if (min4 <= max5)
                        {
                            max5 = 200000;
                            break;
                            // alpha-beta cut
                        }
                    }
                    arrayForInnerBoardLayout[x4][y4] = re4;
                    if (max5 < min4)
                    {
                        min4 = max5;
                    }
                    if (min4 <= max3)
                    {
                        min4 = -200000;
                        break;
                        // alpha-beta cut
                    }
                    if (count4 == limit4)
                    {
                        break;
                        // we search enough point in this level
                    }
                }
                arrayForInnerBoardLayout[x3][y3] = re3;
                if (max3 < min4)
                {
                    max3 = min4;
                }
                if (min2 <= max3)
                {
                    max3 = 200000;
                    break;
                    // alpha-beta cut
                }
                if (count3 == limit3)
                {
                    break;
                    // we search enough point in this level
                }
            }
            arrayForInnerBoardLayout[x2][y2] = re2;
            if (max3 < min2)
            {
                min2 = max3;
            }
            if (min2 <= max1)
            {
                min2 = -200000;
                break;
                // alpha-beta cut
            }
            if (count2 == limit2)
            {
                break;
                // we search enough point in this level
            }
        }
        arrayForInnerBoardLayout[x1][y1] = re1;
        if (min2 > max1)
        {
            if (ban(x1, y1, n,0) == 0)
            {
                aipoint.x = x1;
                aipoint.y = y1;
                max1 = min2;
            }
        }
        if (count1 == limit1)
        {
            return aipoint;
            // we search enough point in this level
        }
    }

    return aipoint;
}

void updatescore(int x, int y, int n)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            scoreboard[i][j] = score(i, j, 1) + score(i, j, 2);
        }
    } // the score board,useful
}

void initroad()
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            (road[j + i * 15]).x = i;
            (road[j + i * 15]).y = j;
        }
    } // input each point in road array
}

void formroad(int left, int right)
{
    // use quick sort to sort the point from the highest score to lowest
    int i, last;
    void swap(struct point v[], int i, int j);
    if (left >= right)
    {
        return;
    }
    swap(road, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
    {
        if (scoreboard[(road[i]).x][(road[i].y)] > scoreboard[(road[left]).x][(road[left].y)])
            swap(road, ++last, i);
    }
    swap(road, left, last);
    formroad(left, last - 1);
    formroad(last + 1, right);
}

void swap(struct point v[], int i, int j)
{
    // updated swap,nothing interesting
    int tempx, tempy;
    tempx = (v[i]).x;
    tempy = (v[i]).y;
    (v[i]).x = (v[j]).x;
    (v[i]).y = (v[j]).y;
    (v[j]).x = tempx;
    (v[j]).y = tempy;
}