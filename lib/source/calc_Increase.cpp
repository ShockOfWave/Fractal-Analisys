#include "calc_Increase.h"

#include <iostream>

void calc_Increase(std::vector<double>&& increases, std::vector<int>&& regression) {

    for (int i = 0; i < regression.size(); ++i) {
        increases.push_back(log10(pow(regression[i], -1)));
    }
}