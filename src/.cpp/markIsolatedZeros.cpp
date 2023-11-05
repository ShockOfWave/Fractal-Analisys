#include "markIsolatedZeros.h"

void markIsolatedZeros(std::vector<std::vector<int>>& matrix, int width, int height) {
    int currentMarker = -1;
    int dx[] = { 1, 0, -1, 0 };
    int dy[] = { 0, 1, 0, -1 };

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (matrix[y][x] == 0) {
                bool hasZeroNeighbor = false;
                for (int i = 0; i < 4; i++) {
                    int newY = y + dy[i];
                    int newX = x + dx[i];

                    if (newX >= 0 && newX < width && newY >= 0 && newY < height && matrix[newY][newX] == 0) {
                        hasZeroNeighbor = true;
                        break;
                    }
                    if (hasZeroNeighbor) break;
                }
                if (!hasZeroNeighbor) {
                    matrix[y][x] = currentMarker;
                    currentMarker--;
                }
            }
        }
    }
}