#include "calculations.h"

int get_max_dif(pair<int, int> *mn, int mn_size, int cur_ids[THREE])
{
    int rez = -1;

    pair<int, int> cur[THREE];
    cur[0].first = mn[cur_ids[0]].first;
    cur[0].second = mn[cur_ids[0]].second;
    cur[1].first = mn[cur_ids[1]].first;
    cur[0].second = mn[cur_ids[1]].second;
    cur[2].first = mn[cur_ids[2]].first;
    cur[0].second = mn[cur_ids[2]].second;

    pair<int, int> center = make_pair((cur[0].first + cur[1].first + cur[2].first) / 3, (cur[0].second + cur[1].second + cur[2].second) / 3);

    pair<int, int> medians[THREE] =
    {
        make_pair((cur[0].first + cur[1].first) / 2, (cur[0].second + cur[1].second) / 2),
        make_pair((cur[1].first + cur[2].first) / 2, (cur[1].second + cur[2].second) / 2),
        make_pair((cur[2].first + cur[0].first) / 2, (cur[2].second + cur[0].second) / 2)
    };

    int counter[6] = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < mn_size; i++)
    {
        for (int j = 0; j < THREE; j++)
        {
            if (i == cur_ids[j])
            {
                i++;
                break;
            }
        }

        int tmp = is_in_triangle(mn[i], cur[0], cur[1], cur[2]);
        if (tmp > 0)
        {
            tmp = is_in_triangle(mn[i], cur[0], medians[0], center);
            if (tmp > 0)
            {
                counter[0]++;
            }

            tmp = is_in_triangle(mn[i], cur[1], medians[0], center);
            if (tmp > 0)
            {
                counter[1]++;
            }

            tmp = is_in_triangle(mn[i], cur[1], medians[1], center);
            if (tmp > 0)
            {
                counter[2]++;
            }

            tmp = is_in_triangle(mn[i], cur[2], medians[1], center);
            if (tmp > 0)
            {
                counter[3]++;
            }

            tmp = is_in_triangle(mn[i], cur[2], medians[2], center);
            if (tmp > 0)
            {
                counter[4]++;
            }

            tmp = is_in_triangle(mn[i], cur[0], medians[2], center);
            if (tmp > 0)
            {
                counter[5]++;
            }
        }
    }


    int max = -1;
    int min = mn_size;
    for (int i = 0; i < 6; i++)
    {
        if (counter[i] > max)
            max = counter[i];
        if (counter[i] < min)
            min = counter[i];
    }

    rez = max - min;

    return rez;
}

int cosoe_proizv(int x1, int x2, int y1, int y2)
{
    return x1 * y2 - y1 * x2;
}

//?
int get_side(pair<int, int> dot, pair<int, int> line_dot1, pair<int, int> line_dot2)
{
    int x1 = line_dot2.first - line_dot1.first;
    int y1 = line_dot2.second - line_dot1.second;
    int x2 = dot.first - line_dot1.first;
    int y2 = dot.second - line_dot1.second;
    int rez =  cosoe_proizv(x1, x2, y1, y2);
    return rez;
}

int is_in_triangle(pair<int, int> dot, pair<int, int> tr_dot1, pair<int, int> tr_dot2, pair<int, int> tr_dot3)
{
    int x0 = dot.first;
    int y0 = dot.second;

    /*int x1 = tr_dot2.first - tr_dot1.first;
    int y1 = tr_dot2.second - tr_dot1.second;
    int x2 = tr_dot3.first - tr_dot2.first;
    int y2 = tr_dot3.second - tr_dot2.second;
    int x3 = tr_dot1.first - tr_dot3.first;
    int y3 = tr_dot1.second - tr_dot3.second;*/

    int x1 = tr_dot1.first;
    int y1 = tr_dot1.second;
    int x2 = tr_dot2.first;
    int y2 = tr_dot2.second;
    int x3 = tr_dot3.first;
    int y3 = tr_dot3.second;

    int c1 = cosoe_proizv(x0 - x1, x2 - x1, y0 - y1, y2 - y1);
    int c2 = cosoe_proizv(x0 - x2, x3 - x2, y0 - y2, y3 - y2);
    int c3 = cosoe_proizv(x0 - x3, x1 - x3, y0 - y3, y1 - y3);

    int rez;

    if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0))
    {
        rez = 1;
    }
    else if (c1 == 0 || c2 == 0 || c3 == 0)
    {
        rez = 0;
    }
    else
    {
        rez = -1;
    }

    return rez;
}
