#ifndef FRACTAL_ANALISYS_H
#define FRACTAL_ANALISYS_H
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include "gsl/gsl_fit.h"
#include "coord.h"
#include "hasNumber.h"
#include "marks.h"
#include "memory_free.h"
#include "result.h"
void mark_squares_8(std::vector<std::vector<int>>&& matrix, const int height, const int width);
void mark_squares_4(std::vector<std::vector<int>>&& matrix, const int height, const int width);
void calc_Regression(std::vector<int>&& regression, int height, int width);
void Bradley_threshold(const std::vector<std::vector<double>>&& src, std::vector<std::vector<int>>&& res, int width, int height, double pressure);
void boxCounting(std::vector<int>&& regression, std::vector<std::vector<int>>&& matrix, std::vector<double>&& half_regressions, std::vector<double>&& lambdas, std::vector<double>&& counts, double* holes_num);
void slide_box_counting(std::vector<int>&& regression, std::vector<std::vector<int>>&& matrix,
    std::vector<double>&& half_regressions, std::vector<double>&& lambdas, std::vector<double>&& counts, double* holes_num);
void calc_Increase(std::vector<double>&& increases, std::vector<int>&& regression);
double calcDerivative(std::vector<double> x, std::vector<double> y);
int markInnerOnes(std::vector<std::vector<int> >& matrix, int* area_count);
void compute_square(std::vector<std::vector<int> > matrix, int* z_square, int* u_square, int* z_bg);
Marks countUniqueMarkers(const std::vector<std::vector<int> >& matrix);
void computeDerivative(const std::vector<double>& x_data, const std::vector<double>& y_data, std::vector<double>&& y_derivative);
void visualizeImage(std::vector<std::vector<int> > matrix, int wait_k);
void show_loading_progress(int current, int total);
#endif
