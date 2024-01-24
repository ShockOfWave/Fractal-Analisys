#include <ctime>
#include <iostream>
#include <cstdlib>
#include "matrix_process.h"

extern "C"{
	Result lacunarity(double* array, size_t n, size_t p, int connectivity, int box, int N, int wait_k) {
		clock_t start_time = clock();
        int loading = 0;
		std::vector<std::vector<double> > image;
		for (size_t i = 0; i < n; i++){
        	std::vector<double> row;
            for (size_t j = 0; j < p; j++){
                row.push_back(array[i * n + j]);
            }
            image.push_back(row);
        }
		Result result;
		Marks marks;
		double p_limit = 1.0;
		std::vector<int> regression;
		std::vector<double> pressures; 
        // an array for storing the pressure value on each slice
		std::vector<double> derivatives; 
        // array for storing the value of the derivative calculated by least squares for the log10N-log10r^-1 dependence on each slice
		std::vector<int> holes;
        // array to add number of gaps
        std::vector<int> holes_int;
        // number of internal holes
		std::vector<int> external_lands; 
        // array to add number of external units
		std::vector<int> internal_lands; 
        // array to add number of internal units
		std::vector<double> relationship; 
        // an array to add the ratio of the number of gaps to the total surface area
		std::vector<double> relationship_derivatives; 
        // array for adding partial derivatives of the previous one
        std::vector<int> z_bgVec;

		std::vector<double> half_regressions;
		std::vector<double> lambdas;
		//std::vector<double> exp_half_regressions;
		//std::vector<double> exp_lambdas;

		std::vector<int> ex_ones_square;
		std::vector<int> in_ones_square;
		std::vector<int> z_square;
        double dPressure = static_cast<double>(1.0/N);
        const int height = image.size();  // determination of constant parameters - matrix size
		const int width = image[0].size();
		const int square = (image.size()) * (image[0].size());

		calc_Regression(std::move(regression), height, width);

		for (double pressure = 0.0; pressure < 1.0; pressure += (dPressure)) {
            if((loading % 5) == 0){
                show_loading_progress(loading, 100);
            }
            loading++;
		    double holes_num = 0.0;
		    int ex_ones = 0;
		    int in_ones = 0;
            int z_bg = 0;
		    int z = 0;
		    std::vector<std::vector<int> > matrix(height, std::vector<int>(width, 0));
		    double derivative;
		    //std::map<int, int> box_counts;
		    std::vector<double> logN;
		    std::vector<double> increases;
            Bradley_threshold(std::move(image), std::move(matrix), height, width, pressure);
            // visualizeImage(matrix, wait_k);
		    if (box == 1) {
    			boxCounting(std::move(regression), std::move(matrix), std::move(half_regressions), std::move(lambdas), std::move(logN), &holes_num);
			}
			else {
    			slide_box_counting(std::move(regression), std::move(matrix), std::move(half_regressions),
        			std::move(lambdas), std::move(logN), &holes_num);
			}
		    calc_Increase(std::move(increases), std::move(regression));
		    derivative = calcDerivative(increases, logN);
		    if (connectivity == 8) {
    			mark_squares_8(std::move(matrix), height, width);
			}
			else {
    			mark_squares_4(std::move(matrix), height, width);
			}
            int count = markInnerOnes(matrix, &in_ones); // internal units and their area
            compute_square(matrix, &z, &ex_ones, &z_bg);
            marks = countUniqueMarkers(matrix); // number of internal zeros and external ones
		    pressures.push_back(pressure*100);
		    derivatives.push_back(derivative);
		    holes.push_back(marks.zero_marks.size()-1);
            int o = (int)((marks.zero_marks.size())-((marks.un_marks.size())));
            if(o < 0) o = 0;
            holes_int.push_back(o);
            external_lands.push_back((marks.un_marks.size() - count));
		    internal_lands.push_back(count);
		    relationship.push_back(holes_num / (square));
		    ex_ones_square.push_back(ex_ones);
		    in_ones_square.push_back(in_ones);
		    z_square.push_back(z);
            z_bgVec.push_back(z_bg);
		}
        show_loading_progress(loading, 100);
        std::system("clear");
		computeDerivative(pressures, relationship, std::move(relationship_derivatives));
		
		result.pressures_len = pressures.size();
		result.pressures = new double[result.pressures_len];
		
		result.derivatives_len = derivatives.size();
		result.derivatives = new double[result.derivatives_len];
		
		result.holes_len = holes.size();
		result.holes = new int[result.holes_len];

        result.holes_int_len = holes_int.size();
        result.holes_int = new int[result.holes_int_len];
		
		result.external_lands_len = external_lands.size();
		result.external_lands = new int[result.external_lands_len];
		
		result.internal_lands_len = internal_lands.size();
		result.internal_lands = new int[result.internal_lands_len];
		
		result.relationship_len = relationship.size();
		result.relationship = new double[result.relationship_len];
		
		result.relationship_derivatives_len = relationship_derivatives.size();
		result.relationship_derivatives = new double[result.relationship_derivatives_len];
		
		result.ex_ones_square_len = ex_ones_square.size();
		result.ex_ones_square = new int[result.ex_ones_square_len];
		
		result.in_ones_square_len = in_ones_square.size();
		result.in_ones_square = new int[result.in_ones_square_len];
		
        result.z_bg_len = z_bgVec.size();
        result.z_bgVec = new int[result.z_bg_len];

		result.z_square_len = z_square.size();
		result.z_square = new int[result.z_square_len];
		for (int h = 0; h < pressures.size(); ++h) {
			result.pressures[h] = pressures[h];
			result.derivatives[h] = derivatives[h];
			result.holes[h] = holes[h];
            result.holes_int[h] = holes_int[h];
			result.external_lands[h] = external_lands[h];
			result.internal_lands[h] = internal_lands[h];
			result.relationship[h] = relationship[h];
			result.relationship_derivatives[h] = relationship_derivatives[h];
			result.ex_ones_square[h] = ex_ones_square[h];
			result.in_ones_square[h] = in_ones_square[h];
			result.z_square[h] = z_square[h];
            result.z_bgVec[h] = z_bgVec[h];
		}
		
		result.half_regressions_len = half_regressions.size();
		result.half_regressions = new double[result.half_regressions_len];
		
		result.lambdas_len = lambdas.size();
		result.lambdas = new double[result.lambdas_len];
		for (int l = 0; l < lambdas.size(); ++l){
			result.half_regressions[l] = half_regressions[l];
			result.lambdas[l] = lambdas[l];
		}
		clock_t end_time = clock();
		double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        std::cout << "Full library runtime: " << duration << ", sec" << "\n";

		return result;
	}
}
