#include "memory_free.h"

extern "C"{
	void memory_free(Result result){
		delete[] result.pressures;
		delete[] result.derivatives;
		delete[] result.holes;
		delete[] result.external_lands;
		delete[] result.internal_lands;
		delete[] result.relationship;
		delete[] result.relationship_derivatives;
		delete[] result.ex_ones_square;
		delete[] result.in_ones_square;
		delete[] result.z_square;
		delete[] result.half_regressions;
		delete[] result.lambdas;
	}
}
