#include "calcDerivative.h"

double calcDerivative(std::vector<double> x, std::vector<double> y) {

    size_t n = x.size();
    double c0, c1, cov00, cov01, cov11, sumsq;

    gsl_fit_linear(&x[0], 1, &y[0], 1, n, &c0, &c1, &cov00, &cov01, &cov11, &sumsq);

    return c1;
}
