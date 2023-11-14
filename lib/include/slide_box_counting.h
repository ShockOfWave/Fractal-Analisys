#ifndef SLIDE_BOX_COUNTING_H
#define SLIDE_BOX_COUNTING_H

#include <map>
#include <vector>
#include <cmath>

void slide_box_counting(std::vector<int>&& regression, std::vector<std::vector<int> >&& matrix, std::vector<double>&& half_regressions, std::vector<double>&& lambdas, std::vector<double>&& exp_half_regressions, std::vector<double>&& exp_lambdas);

#endif
