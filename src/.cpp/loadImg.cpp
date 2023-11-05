#include "loadImg.h"

#include <string>
#include <sstream>
#include <fstream>

void loadImg(std::vector<std::vector<double>>&& image, std::string path) {
    std::ifstream file(path);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<double> row;
        double num;
        while (iss >> num) {
            row.push_back(num);
        }
        image.push_back(row);
    }
    file.close();
}