#include "findInnerOnes.h"
#include "markInnerOnes.h"

int findInnerOnes(std::vector<std::vector<int>>& matrix) {
    int width = matrix[0].size();
    int height = matrix.size();
    int marker = 0; // Маркер группы 4-связных единиц
    int count = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (matrix[y][x] > -1) {
                int count_c = 0;
                marker = matrix[y][x];
                count_c = markInnerOnes(matrix, x, y, marker, height, width);
                count += count_c;
            }

        }
    }
    return count;
}