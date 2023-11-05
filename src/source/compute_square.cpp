#include "compute_square.h"

void compute_square(std::vector<std::vector<int>> matrix, int* z_square, int* u_square) {

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            int z_count = 0;
            int meet = 0;

            if (matrix[i][j] > 0) {
                (*u_square)++;
                int marker = matrix[i][j];

                if (i + 1 < matrix.size()) {

                    int newI = i + 1;
                    while (newI < matrix.size()) {
                        if (matrix[newI][j] < 0) {
                            z_count++;
                        }
                        else if (matrix[newI][j] == marker) {
                            meet++;
                            break;
                        }
                        newI++;
                    }
                }
            }
            if (meet == 0) {
                z_count = 0;
            }
            (*z_square) += z_count;
        }
    }
}