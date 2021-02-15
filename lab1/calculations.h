#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include <map>

using namespace std;

#define THREE 3

int get_max_dif(int *mn_x, int *mn_y, int mn_size, int cur_ids[THREE]);

int is_in_triangle(pair<int, int> dot, pair<int, int> tr_dot1, pair<int, int> tr_dot2, pair<int, int> tr_dot3);

#endif // CALCULATIONS_H
