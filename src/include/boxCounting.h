#ifndef BOX_COUNTING_H
#define BOX_COUNTING_H

#include <map>
#include <vector>

std::map<int, int> boxCounting(std::vector<int>&& regression, std::vector<std::vector<int>>&& matrix, double* holes_num);

#endif
