#include "calcDerivative.h"
#include "gsl/gsl_multifit.h"

double calc_derivative(std::vector<double> x, std::vector<double> y) {
    // ������� GSL-������� X � ������ y
    int N = x.size();
    gsl_matrix* X = gsl_matrix_alloc(N, 2);
    gsl_vector* y_data = gsl_vector_alloc(N);

    // ����������������� ������ ���� � GSL � � ������
    for (size_t i = 0; i < N; i++) {
        gsl_matrix_set(X, i, 0, 1.0); // ������ ������� ������ 1 ��� ������������� ������
        gsl_matrix_set(X, i, 1, x[i]); // ������ ������� - �������� x �� ����������������� ������
        gsl_vector_set(y_data, i, y[i]); // ������ y - �������� y �� ����������������� ������
    }

    // ��������� ��� �������� �����������
    gsl_vector* c = gsl_vector_alloc(2); // ������������ �������� �������������
    gsl_matrix* cov = gsl_matrix_alloc(2, 2); // ������� ����������
    double chisq; // �������� ��-�������

    // ������������� ������� ���������� ���������
    gsl_multifit_linear_workspace* work = gsl_multifit_linear_alloc(N, 2);
    gsl_multifit_linear(X, y_data, c, cov, &chisq, work);

    // ����� ������������� �������� ������������� (c), ������� ���������� (cov)
    // � �������� ��-������� (chisq)
    /*std::cout << "Linear Fit Results:" << std::endl;
    std::cout << "Intercept: " << gsl_vector_get(c, 0) << std::endl;
    std::cout << "Slope: " << gsl_vector_get(c, 1) << std::endl;
    std::cout << "Covariance Matrix:" << std::endl;*/
    for (size_t i = 0; i < 2; i++) {
        for (size_t j = 0; j < 2; j++) {
            //std::cout << gsl_matrix_get(cov, i, j) << " ";
        }
        //std::cout << std::endl;
    }
    //std::cout << "Chi-squared: " << chisq << std::endl;

    // ���������� �����������
    double derivative = gsl_vector_get(c, 1);
    //std::cout << "Derivative: " << derivative << std::endl;

    // ������������ ��������
    gsl_multifit_linear_free(work);
    gsl_matrix_free(X);
    gsl_vector_free(y_data);
    gsl_vector_free(c);
    gsl_matrix_free(cov);

    return derivative;
}