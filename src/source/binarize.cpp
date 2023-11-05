#include "binarize.h"

void binarize(std::vector<std::vector<int>>&& bin_matrix, std::vector<std::vector<double>> image, double thresh, double pressure) {

    for (int i = 0; i < image.size(); ++i) {
        std::vector<int> row;
        for (int j = 0; j < image[i].size(); ++j) {
            image[i][j] *= (pressure*5e7);
            row.push_back((image[i][j] > thresh) ? 1 : 0);
        }
        bin_matrix.push_back(row);
    }
}