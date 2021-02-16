#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <map>
#include <iostream>

using namespace std;

#define THREE 3

int get_max_dif(pair<int, int> *mn, int mn_size, int cur_ids[THREE]);

int cosoe_proizv(int x1, int x2, int y1, int y2);

int is_in_triangle(pair<int, int> dot, pair<int, int> tr_dot1, pair<int, int> tr_dot2, pair<int, int> tr_dot3);

#endif // CALCULATIONS_H
