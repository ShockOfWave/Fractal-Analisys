#include "boxCounting.h"

std::vector<double> boxCounting(std::vector<int>&& regression, std::vector<std::vector<int> >&& matrix, double* holes_num) {

    std::vector<double> counts;
    std::sort(regression.begin(), regression.end());
    for (int k = 0; k < regression.size(); ++k) {
        int box_counter = 0;

        for (int i = 0; i < matrix.size(); i += regression[k]) {

            for (int j = 0; j < matrix[i].size(); j += regression[k]) {
                if (matrix[i][j] == 0 && regression[k] == 1) {
                    *(holes_num) += 1.0;
                }
                bool flag = false;

                for (int y = i; y < std::min(i + regression[k], static_cast<int>(matrix.size())); ++y) {
                    for (int x = j; x < std::min(j + regression[k], static_cast<int>(matrix[i].size())); ++x) {
                        if (matrix[y][x] == 1) {
                            box_counter++;
                            flag = true;
                            break;
                        }
                    }
                    if (flag == true) {
                        break;
                    }
                }
            }
        }
        /*if (k > 0) {
            counts[regression[k]] = box_counter - counts[regression[k - 1]];
        }*/
        counts.push_back(log10(box_counter));
    }
    return counts;
}
