#include "Fractal_analisys.h"
// finding the regression from the min side of the image
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
// Bradley-Rout binarization
void Bradley_threshold(const std::vector<std::vector<double>>&& src, std::vector<std::vector<int>>&& res, int width, int height, double pressure) {
    const double S = static_cast<double> (width / 8);
    double s2 = S / 2;
    const double t = 0.70;
    double sum = 0.0;
    double count = 0.0;
    int index;
    double x1;
    double x2;
    double y1;
    double y2;
    std::vector<double> integral_image(width * height);
    for (int i = 0; i < width; i++) {
        sum = 0;
        for (int j = 0; j < height; j++) {
            index = j * width + i;
            sum += (src[i][j]);
            if (i == 0)
                integral_image[index] = sum;
            else
                integral_image[index] = integral_image[index - 1] + sum;
        }
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            // int index = j * width + i;
            x1 = i - s2;
            x2 = i + s2;
            y1 = j - s2;
            y2 = j + s2;
            if (x1 < 0)
                x1 = 0;
            if (x2 >= width)
                x2 = width - 1;
            if (y1 < 0)
                y1 = 0;
            if (y2 >= height)
                y2 = height - 1;
            count = (x2 - x1) * (y2 - y1);
            sum = integral_image[y2 * width + x2] - integral_image[y1 * width + x2] - integral_image[y2 * width + x1] + integral_image[y1 * width + x1];
            if ((src[i][j] * count * pressure) < (sum * (1.0 - t))) {
                res[i][j] = 0;
            }
            else {
                res[i][j] = 1;
            }
        }
    }
}
// simple box counting
void boxCounting(std::vector<int>&& regression, std::vector<std::vector<int>>&& matrix,
    std::vector<double>&& half_regressions, std::vector<double>&& lambdas, std::vector<double>&& counts, double* holes_num) {
    std::sort(regression.begin(), regression.end());
    for (int k = 0; k < regression.size(); ++k) {
        int box_counter = 0;
        // number of 1 in box
        double n = 0;
        double Z1 = 0;
        // 1 distrib moment
        double Z2 = 0;
        // 2 distrib moment
        double lambda = 0;
        // lacunarity
        std::unordered_map<int, double> k_values;
        std::unordered_map<int, double> q_values;
        for (int c = 0; c < pow(regression[k], 2); ++c) {
            k_values[c] = 0;
            q_values[c] = 0;
        }
        std::vector<int> K; 
        // for each cell of size r the number of units included in it
        int N = ((matrix.size() * matrix[0].size()) / regression[k]); 
        // number of cells of size r required to cover the image completely
        for (int i = 0; i < matrix.size(); i += regression[k]) {
            for (int j = 0; j < matrix[i].size(); j += regression[k]) {
                if (matrix[i][j] == 0 && regression[k] == 1) {
                    *(holes_num) += 1.0;
                }
                bool flag = false;
                for (int z = i; z < std::min(i + regression[k], static_cast<int>(matrix.size())); ++z) {
                    for (int o = j; o < std::min(j + regression[k], static_cast<int>(matrix[i].size())); ++o) {
                        if (matrix[z][o] == 1) {
                            box_counter++;
                        }
                    }
                }
                k_values[box_counter] += 1;
                K.push_back(box_counter);
                box_counter = 0;
                for (int y = i; y < std::min(i + regression[k], static_cast<int>(matrix.size())); ++y) {
                    for (int x = j; x < std::min(j + regression[k], static_cast<int>(matrix[i].size())); ++x) {
                        if (matrix[y][x] == 1) {
                            n++;
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
        for (auto it1 = k_values.begin(), it2 = q_values.begin(); it1 != k_values.end() && it2 != q_values.end(); ++it1, ++it2) {
            it2->second = (it1->second / N);
            Z1 += (it1->first * it2->second);
            Z2 += (pow(it1->first, 2) * it2->second);
        }
        lambda = (Z2 / (pow(Z1, 2)));
        half_regressions.push_back(log(regression[k]));
        lambdas.push_back(log(lambda));
        counts.push_back(log10(n));
    }
}
// slide box counting
void slide_box_counting(std::vector<int>&& regression, std::vector<std::vector<int>>&& matrix,
    std::vector<double>&& half_regressions, std::vector<double>&& lambdas, std::vector<double>&& counts,
    double* holes_num) {

    int delimit_regression = 0;
    std::sort(regression.begin(), regression.end());

    for (int k = 0; k < regression.size(); ++k) {
        int box_counter = 0;
        // number of units in a cell
        double n = 0; 
        double m = 0;
        // number of cells of size r containing k white pixels
        double Z1 = 0; //
        double Z2 = 0;
        //double lambda = 0;

        std::unordered_map<int, double> k_values;
        std::unordered_map<int, double> q_values;
        for (int c = 0; c < pow(regression[k], 2); ++c) {
            k_values[c] = 0;
            q_values[c] = 0;
        }

        std::vector<int> K;
        // for each cell of size r the number of units included in it

        if (regression[k] > 1) {
            delimit_regression = (regression[k] / 2);
            //dl = (static_cast<double>(regression[k] / 2));
        }
        else {
            delimit_regression = regression[k];
            //dl = (static_cast<double>(regression[k]));
        }
        int N = ((matrix.size() * matrix[0].size()) / pow(regression[k], 2));
        // number of cells of size r required to cover the image completely
        for (int i = 0; i < matrix.size(); i += regression[k]) {
            for (int j = 0; j < matrix[i].size(); j += delimit_regression) {
                if (matrix[i][j] == 0 && regression[k] == 1) {
                    *(holes_num) += 1.0;
                }
                bool flag = false;
                for (int z = i; z < std::min(i + regression[k], static_cast<int>(matrix.size())); ++z) {
                    for (int o = j; o < std::min(j + regression[k], static_cast<int>(matrix[i].size())); ++o) {
                        if (matrix[z][o] == 1) {
                            box_counter++; // k
                        }
                    }
                }
                k_values[box_counter] += 1;
                box_counter = 0;
                for (int w = i; w < std::min(i + regression[k], static_cast<int>(matrix.size())); ++w) {
                    for (int p = j; p < std::min(j + regression[k], static_cast<int>(matrix[i].size())); ++p) {
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
        for (auto it1 = k_values.begin(), it2 = q_values.begin(); it1 != k_values.end() && it2 != q_values.end(); ++it1, ++it2) {
            it2->second = (it1->second / N);
            Z1 += (it1->first * it2->second);
            Z2 += (pow(it1->first, 2) * it2->second);
        }

        double lambda = (Z2 / (pow(Z1, 2)));
        // lacunarity for a cell of size r
        half_regressions.push_back(log(regression[k]));
        lambdas.push_back(log(lambda));
        counts.push_back(log10(n));
    }
}
//
void calc_Increase(std::vector<double>&& increases, std::vector<int>&& regression) {
    for (int i = 0; i < regression.size(); ++i) {
        increases.push_back(log10(pow(regression[i], -1)));
    }
}
//
double calcDerivative(std::vector<double> x, std::vector<double> y) {
    size_t n = x.size();
    double c0, c1, cov00, cov01, cov11, sumsq;
    gsl_fit_linear(&x[0], 1, &y[0], 1, n, &c0, &c1, &cov00, &cov01, &cov11, &sumsq);
    return c1;
}
// calculate inner lands
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
                if (x + 1 < width && matrix[y][x + 1] > -1 || (x - 1 >= 0 && matrix[y][x - 1] > -1)) {
                    int newX = x;
                    int newY = y;
                    if (y + 1 < height) {
                        newY = y + 1;
                    }
                    else {
                        newY = y;
                        newX = x;
                    }
                    if (newX >= 0 && newX < width && newY >= 0 && newY < height && matrix[newY][newX] < -1) {
                       // int z_mark = matrix[newY][newX];
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
//
bool hasNumber(const std::vector<int> vec, int numberToFind) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == numberToFind) {
            return false;
        }
    }
    return true;
}
// function for calculate area
void compute_square(std::vector<std::vector<int> > matrix, int* z_square, int* u_square, int* z_bg) {
    std::vector<int> cache;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            int z_count = 0;
            int meet = 0;
            if (matrix[i][j] > 0) {
                (*u_square)++;
                int marker = matrix[i][j];
                if (i + 1 < matrix.size() && i + 1 < 0) {
                    int newI = i + 1;
                    int pre_meet = 0;
                    int tmpI = newI;
                    while (tmpI < matrix.size()) {
                        if (matrix[tmpI][j] == marker){
                            pre_meet++;
                            break;
                        }
                        tmpI++;
                    }
                    while (newI < matrix.size() && pre_meet > 0) {
                        if (matrix[newI][j] < 0) {
                            (*z_square)++;
                            if (hasNumber(cache, matrix[newI][j])){
                                cache.push_back(matrix[newI][j]);
                            }
                        }
                        /*else if (matrix[newI][j] == marker) {
                            meet++;
                            break;
                        }*/
                        newI++;
                    }
                }
            }
            /*if (meet == 0) {
                z_count = 0;
            }
            (*z_square) += z_count;*/
        }
    }
    for (int k = 0; k < matrix.size(); ++k) {
        for (int j = 0; j < matrix[k].size(); ++j) {
            if ((matrix[k][j] < 0) && (hasNumber(cache, matrix[k][j]))){
                (*z_bg)++;
            }
        }
    }
}
// calculate set power
Marks countUniqueMarkers(const std::vector<std::vector<int> >& matrix) {
    int width = matrix[0].size();
    int height = matrix.size();
    Marks marks;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int currentMarker = matrix[y][x];
            if (currentMarker < 0) {
                if (std::find(marks.zero_marks.begin(), marks.zero_marks.end(), currentMarker) == marks.zero_marks.end()) {
                    marks.zero_marks.push_back(currentMarker);
                }
            }
            else if (currentMarker > 0) {
                if (std::find(marks.un_marks.begin(), marks.un_marks.end(), currentMarker) == marks.un_marks.end()) {
                    marks.un_marks.push_back(currentMarker);
                }
            }
        }
    }
    return marks;
}
//
void computeDerivative(const std::vector<double>& x_data, const std::vector<double>& y_data, std::vector<double>&& y_derivative) {
    const int size = x_data.size();
    for (int i = 0; i < size; ++i) {
        y_derivative.push_back((y_data[i + 1] - y_data[i]) / (x_data[i + 1] - x_data[i]));
    }
}
// highlight sets according to 4 - connectivity
void mark_area_4(int x, int y, int mark, std::vector<std::vector<int>>&& matrix, int width, int height, int targetValue) {
    std::stack<Coord> stack;
    stack.push(Coord(x, y));

    while (!stack.empty()) {
        Coord current = stack.top();
        stack.pop();

        if (matrix[current.y][current.x] == targetValue) {
            matrix[current.y][current.x] = mark;

            int dx[] = { 1, 0, -1, 0 };
            int dy[] = { 0, 1, 0, -1 };

            for (int i = 0; i < 4; i++) {
                int newX = current.x + dx[i];
                int newY = current.y + dy[i];

                if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                    stack.push(Coord(newX, newY));
                }
            }
        }
    }
}
// highlight sets according to 8 - connectivity
void mark_area_8(int x, int y, int mark, std::vector<std::vector<int>>&& matrix, int width, int height, int targetValue) {
    std::stack<Coord> stack;
    stack.push(Coord(x, y));

    while (!stack.empty()) {
        Coord current = stack.top();
        stack.pop();

        if (matrix[current.y][current.x] == targetValue) {
            matrix[current.y][current.x] = mark;

            int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
            int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

            for (int i = 0; i < 8; i++) {
                int newX = current.x + dx[i];
                int newY = current.y + dy[i];

                if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
                    stack.push(Coord(newX, newY));
                }
            }
        }
    }
}
// mark sets according to 4 - connectivity
void mark_squares_4(std::vector<std::vector<int>>&& matrix, const int height, const int width) {

    int currentMarker = 2; 
    int zerosMarker = -1;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (matrix[y][x] == 1) {
                mark_area_4(x, y, currentMarker, std::move(matrix), width, height, 1);
                currentMarker++;
            }
            else if (matrix[y][x] == 0) {
                mark_area_4(x, y, zerosMarker, std::move(matrix), width, height, 0);
                zerosMarker--;
            }
        }
    }
}
// mark sets according to 8 - connectivity
void mark_squares_8(std::vector<std::vector<int>>&& matrix, const int height, const int width) {
    
    int currentMarker = 2;
    int zerosMarker = -1;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (matrix[y][x] == 1) {
                mark_area_8(x, y, currentMarker, std::move(matrix), width, height, 1);
                currentMarker++;
            }
            else if (matrix[y][x] == 0) {
                mark_area_8(x, y, zerosMarker, std::move(matrix), width, height, 0);
                zerosMarker--;
            }
        }
    }
}
// loading visualization
void show_loading_progress(int current, int total) {
    int progress = (current * 100) / total;
    int bars = progress / 5;
    std::cout << "\r LOADING: [";
    for (int i = 0; i < bars; i++) {
        std::cout << "#";
    }
    for (int i = bars; i < 20; i++) {
        std::cout << " ";
    }
    std::cout << "] " << progress << "%";
    std::system("clear");
    std::cout << "\n";
}
