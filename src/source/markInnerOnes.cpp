#include "markInnerOnes.h"
#include "hasNumber.h"

int markInnerOnes(std::vector<std::vector<int> >& matrix, int* area_count) {
    int count = 0;
    std::vector<int> visited;
    int width = matrix[0].size();
    int height = matrix.size();
    int marker = 0;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            if (matrix[y][x] > -1) {
                marker = matrix[y][x];
                if (x + 1 < matrix[0].size() && matrix[y][x + 1] > -1 || (x - 1 >= 0 && matrix[y][x - 1] > -1)) {
                    
                    int newX = x;
                    int newY = y;
                    if (y + 1 < height) {
                        newY = y + 1;
                    }
                    else {
                        newY = y;
                        newX = x;
                    }

                    if (newX >= 0 && newX < matrix[0].size() && newY >= 0 && newY < height && matrix[newY][newX] < -1) {
                        int z_mark = matrix[newY][newX];
                        int tmp_mark = marker;
                        int meet = 0;
                        int pre_meet = 0;
                        int newY1 = newY;

                        while (newY1 < height) {
                            newY1 += 1;
                            if ((newY1 + 1 < height && matrix[newY1 + 1][newX] == marker) || (newY1 < height && matrix[newY1][newX] == marker)) {
                                pre_meet++;
                                break;
                            }
                        }
                        if (pre_meet > 0) {
                            while (newY < height && matrix[newY][newX] != marker) {


                                if (matrix[newY + 1][newX] > tmp_mark || matrix[newY + 1][newX] == tmp_mark) {
                                    (*area_count)++;
                                }
                                
                                if (newY + 1 < height && matrix[newY + 1][newX] > tmp_mark && (hasNumber(visited, matrix[newY + 1][newX]))) {
                                    tmp_mark = matrix[newY + 1][newX];
                                    visited.push_back(tmp_mark);
                                    count++;
                                }
                            
                                newY++;
                                if ((newY + 1 < height && matrix[newY + 1][newX] == marker) || (newY < height && matrix[newY][newX] == marker)) {
                                    meet++;
                                    break;
                                }
                            }
                            if (meet == 0) {
                                count = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return count;
}
