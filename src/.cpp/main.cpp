#include <ctime>
#include <iostream>
#include "Marks.h"
#include "Coord.h"
#include "markInnerOnes.h"
#include "markArea.h"
#include "markInnerOnes.h"
#include "countUniqueMarkers.h"
#include "binarize.h"
#include "calc_Increase.h"
#include "calc_Regression.h"
#include "boxCounting.h"
#include "logFrom.h"
#include "calcDerivative.h"
#include "hasNumber.h"
#include "compute_derivative.h"
#include "slide_box_counting.h"
#include "compute_square.h"
#include "result.h"
#include "memory_free.h"

// Функция для маркировки области единиц и нулей (markArea)


// Функция для маркировки нулей, которые не имеют 4-связных соседей нулей (mark isolated zeros)

// Функция для подсчета количества уникальных маркеров (count unique markers)

//функция для бинаризации изображения по границе (binarize)

//функция для загрузки изображения из файла .txt (loadimg)


//функция для записи массива в файл .txt (write to file)


//BOX COUNTING ВОЗВРАЩАЕТ СЛОВАРЬ

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
extern "C"{

	//точка входа
	Result lacunarity(double* array, size_t n, size_t p) {
		clock_t start_time = clock();
		std::vector<std::vector<double>> image;
		
		for (size_t i = 0; i < n; i++)
        {
        	std::vector<double> row;
            for (size_t j = 0; j < p; j++)
            {
                row.push_back(array[i * n + j]);
            }
            image.push_back(row);
        }
		
		Result result;
		Marks marks;
		
		double thresh = 0.5;
		
		std::vector<int> regression;

		std::vector<double> pressures; //массив для хранения значения давления на каждом срезе
		std::vector<double> derivatives; //массив для хранения значения производной вычисленной по мнк для зависимости log10N-log10r^-1 на каждом срезе
		std::vector<int> holes; //массив для добавления количества пропастей
		std::vector<int> external_lands; // массив для добавления количества внешних единиц
		std::vector<int> internal_lands; // массив для добавления количества внутренних единиц
		std::vector<double> relationship; // массив для добавления отношения количества пропастей к общей площади поверхности
		std::vector<double> relationship_derivatives; // массив для добавления частных производных от пердыдещго

		
		//std::map<double, double> lacunarityes;

		std::vector<double> half_regressions;
		std::vector<double> lambdas;
		std::vector<double> exp_half_regressions;
		std::vector<double> exp_lambdas;

		std::vector<int> ex_ones_square;
		std::vector<int> in_ones_square;
		std::vector<int> z_square;
		//printFramedText();
		//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
		//1// "C:/Users/Владислав/Desktop/ITMO_task/text_data.txt"
		// 
		//3// "C:/Users/Владислав/Desktop/ITMO_task/AFM/0.1 -30%_.txt"
		// 
		//2// "C:/Users/Владислав/Desktop/ITMO_task/AFM/5 - 80%__base.txt"
		// 
		// test // "C:/Users/Владислав/Desktop/ITMO_task/Suzuki85/c_test.txt"
		//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

		 //загрузка изображения из файла .txt
		

		const int height = image.size();  //определение константных парамтеров - размера матрицы
		const int width = image[0].size();
		const int square = (image.size()) * (image[0].size());

		calc_Regression(std::move(regression), height, width);

		for (double pressure = 0.0; pressure < 1.0; pressure += 0.01) {
		    
		    double holes_num = 0.0;

		    int ex_ones = 0;
		    int in_ones = 0;
		    int z = 0;

		    std::vector<std::vector<int>> matrix;
		    double derivative;

		    std::map<int, int> box_counts;

		    std::vector<double> logN;
		    
		    std::vector<double> increases;
		    //double rez = thresh * (pressure*100);
		    binarize(std::move(matrix), image, thresh, pressure); 
		    
		    //вычисляем размеры сетки для box counting
		    
		    box_counts = boxCounting(std::move(regression), std::move(matrix), &holes_num);
		        
		    slide_box_counting(std::move(regression), std::move(matrix), std::move(half_regressions), std::move(lambdas),std::move(exp_half_regressions),std::move(exp_lambdas));
		    

		    logFrom(box_counts, std::move(logN));

		    calc_Increase(std::move(increases), std::move(regression));

		    derivative = calc_derivative(increases, logN);
		    //std::cout << der << "\n";

		    int currentMarker = 2; // Начинаем с маркера 2 (1 уже занят)
		    int zerosMarker = -1;
		    for (int y = 0; y < height; y++) {
		        for (int x = 0; x < width; x++) {
		            if (matrix[y][x] == 1) {
		                markArea(x, y, currentMarker, std::move(matrix), width, height, 1);
		                currentMarker++;
		            }
		            else if (matrix[y][x] == 0) {
		                markArea(x, y, zerosMarker, std::move(matrix), width, height, 0);
		                zerosMarker--;
		            }
		        }
		    }
		    int count = 0;
		    
		    count = markInnerOnes(matrix, &in_ones); //внутренние единицы и их площадь
		    compute_square(matrix, &z, &ex_ones);
		    marks = countUniqueMarkers(matrix); //кол-во внутренних нулей и внешних единиц

		    pressures.push_back(pressure*100);
		    derivatives.push_back(derivative);
		    holes.push_back(marks.zero_marks.size()-1);
		    external_lands.push_back(marks.un_marks.size());
		    internal_lands.push_back(count);
		    relationship.push_back(holes_num / (square));

		    ex_ones_square.push_back(ex_ones);
		    in_ones_square.push_back(in_ones);
		    z_square.push_back(z);
		    
		}

		computeDerivative(pressures, relationship, std::move(relationship_derivatives));
		
		result.pressures_len = pressures.size();
		result.pressures = new double[result.pressures_len];
		
		result.derivatives_len = derivatives.size();
		result.derivatives = new double[result.derivatives_len];
		
		result.holes_len = holes.size();
		result.holes = new int[result.holes_len];
		
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
		
		result.z_square_len = z_square.size();
		result.z_square = new int[result.z_square_len];
		
		for (int h = 0; h < pressures.size(); ++h) {
			result.pressures[h] = pressures[h];
			result.derivatives[h] = derivatives[h];
			result.holes[h] = holes[h];
			result.external_lands[h] = external_lands[h];
			result.internal_lands[h] = internal_lands[h];
			result.relationship[h] = relationship[h];
			result.relationship_derivatives[h] = relationship_derivatives[h];
			result.ex_ones_square[h] = ex_ones_square[h];
			result.in_ones_square[h] = in_ones_square[h];
			result.z_square[h] = z_square[h];
		}
		
		result.half_regressions_len = half_regressions.size();
		result.half_regressions = new double[result.half_regressions_len];
		
		result.lambdas_len = lambdas.size();
		result.lambdas = new double[result.lambdas_len];
		
		result.exp_half_regressions_len = exp_half_regressions.size();
		result.exp_half_regressions = new double[result.exp_half_regressions_len];
		
		result.exp_lambdas_len = exp_lambdas.size();
		result.exp_lambdas = new double[result.exp_lambdas_len];
		
		for (int l = 0; l < lambdas.size(); ++l){
			result.half_regressions[l] = half_regressions[l];
			result.lambdas[l] = lambdas[l];
			result.exp_half_regressions[l] = exp_half_regressions[l];
			result.exp_lambdas[l] = exp_lambdas[l];
		}
		
		clock_t end_time = clock();
		double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
		std::cout << "Full library runtime: " << duration << ", sec" << "\n";

		return result;
	}
}
