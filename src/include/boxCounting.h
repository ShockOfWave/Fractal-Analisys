#ifndef BOX_COUNTING_H
#define BOX_COUNTING_H

#include <algorithm>
#include <cmath>
#include <vector>

std::vector<double> boxCounting(std::vector<int>&& regression, std::vector<std::vector<int>>&& matrix, double* holes_num);

#endif
