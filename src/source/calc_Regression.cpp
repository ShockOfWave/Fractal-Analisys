#include "calc_Regression.h"

void calc_Regression(std::vector<int>&& regression, int height, int width) {
    int n = 0;
    int current_val = 0;
    if (height < width) {
        n = static_cast<int>(log(height / 2) / log(2)) + 1;
        current_val = (height / 2);
    }
    else {
        n = static_cast<int>(log(width / 2) / log(2)) + 1;
        current_val = (width / 2);
    }

    for (int i = 0; i < n; ++i) {
        regression.push_back(current_val);
        current_val = current_val / 2;
    }
}
