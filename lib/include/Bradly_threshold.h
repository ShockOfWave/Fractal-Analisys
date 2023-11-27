#ifndef BRADLY_THRESHOLD_H
#define BRADLY_THRESHOLD_H

#include <vector>

void Bradley_threshold(const std::vector<std::vector<double>>&& src, std::vector<std::vector<int>>&& res, int width, int height, double pressure);

#endif
