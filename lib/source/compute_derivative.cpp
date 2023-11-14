#include "compute_derivative.h"

void computeDerivative(const std::vector<double>& x_data, const std::vector<double>& y_data, std::vector<double>&& y_derivative) {
    
    const int size = x_data.size();

    for (int i = 0; i < size; ++i) {
        y_derivative.push_back((y_data[i + 1] - y_data[i]) / (x_data[i + 1] - x_data[i]));
    }
}
