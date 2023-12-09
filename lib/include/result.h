#ifndef RESULT_H
#define RESULT_H

#include <cstddef>

struct Result { 
// struct for returning arrays to python
	double* pressures;
	size_t pressures_len;
		
	double* derivatives;
	size_t derivatives_len;
	
	int* holes;
	size_t holes_len;
	
	int* external_lands;
	size_t external_lands_len;
	
	int* internal_lands;
	size_t internal_lands_len;
	
	double* relationship;
	size_t relationship_len;
	
	double* relationship_derivatives;
	size_t relationship_derivatives_len;
	
	int* ex_ones_square;
	size_t ex_ones_square_len;
	
	int* in_ones_square;
	size_t in_ones_square_len;
	
	int* z_square;
	size_t z_square_len;
	
	double* half_regressions;
	size_t half_regressions_len;

	double* lambdas;
	size_t lambdas_len;

    int* z_bgVec;
    size_t z_bg_len;
};
#endif
