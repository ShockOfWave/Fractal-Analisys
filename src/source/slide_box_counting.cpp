#include "slide_box_counting.h"

#include <algorithm>
#include <iostream>

void slide_box_counting(std::vector<int>&& regression, std::vector<std::vector<int> >&& matrix, std::vector<double>&& half_regressions, std::vector<double>&& lambdas, std::vector<double>&& exp_half_regressions, std::vector<double>&& exp_lambdas) {

    int delimit_regression = 0;
    std::sort(regression.begin(), regression.end());

    for (int k = 0; k < regression.size(); ++k) {
        int box_counter = 0; //количество единиц в ячейке
        double n = 0; //количество ячеек размера r, содержащих k белых пикселей
        double Z1 = 0; //
        double Z2 = 0;
        double lambda = 0;

        std::vector<int> K; //для каждой ячейки размера r количество единиц входящих в нее

        if (regression[k] > 1) {
            delimit_regression = (regression[k] / 2);
            //dl = (static_cast<double>(regression[k] / 2));
        }
        else {
            delimit_regression = regression[k];
            //dl = (static_cast<double>(regression[k]));
        }
        int N = ((matrix.size() * matrix[0].size()) / delimit_regression); //кол-во ячеек размера r необходимое для покрытия изображения полностью

        for (int i = 0; i < matrix.size(); i += regression[k]) {

            for (int j = 0; j < matrix[i].size(); j += delimit_regression) {
                bool flag = false;
                //скользящий счетчик коробок d == 0.5 ящика
                for (int z = i; z < std::min(i + regression[k], static_cast<int>(matrix.size())); ++z) {
                    for (int o = j; o < std::min(j + delimit_regression, static_cast<int>(matrix[i].size())); ++o) {
                        if (matrix[z][o] == 1) {
                            box_counter++;
                        }
                    }
                }
                K.push_back(box_counter);
                //std::cout << " bc = " << box_counter << "\n";
                for (int w = i; w < std::min(i + regression[k], static_cast<int>(matrix.size())); ++w) {
                    for (int p = j; p < std::min(j + delimit_regression, static_cast<int>(matrix[i].size())); ++p) {
                        if (matrix[w][p] == 1) {
                            n++;
                            flag = true;
                            break;
                        }
                    }
                    if (flag) {
                        break;
                    }
                }
            }
        }
        double Q = (n / N);
        for (int f = 0; f < K.size(); ++f) {
            Z1 += (K[f] * Q);
            Z2 += (pow(K[f], 2) * Q);
        }
        lambda = (Z2 / (pow(Z1, 2))); // лакунарность для ячейки размера r

        half_regressions.push_back(log(regression[k]));
        exp_half_regressions.push_back(regression[k]);
        
        lambdas.push_back(log(lambda));
        exp_lambdas.push_back(lambda);
        //lacunarityes[log(regression[k])] = log(lambda);
    }
}
