#pragma once
#include <string>
#include <vector>
#include <map>

#include "gnuplot-iostream.h"

class Plotter
{
public:
    //Plotter();

    Plotter& set_xlabel(const std::string& label);
    Plotter& set_ylabel(const std::string& label);
    Plotter& set_zlabel(const std::string& label);
    Plotter& set_title(const std::string& title);
    Plotter& set_grid(bool enable);

    void line_plot(const std::vector<double>& x, const std::vector<double>& y, const std::string& title);
    void couple_lines_plot(const std::vector<double>& x, const std::vector<double>& y1, const std::vector<double>& y2, const std::string& title1, const std::string& title2);
    void triple_lines_plot(const std::vector<double>& x, const std::vector<int>& y1, const std::vector<int>& y2, const std::vector<int>& y3, const std::string& title1, const std::string& title2, const std::string& title3);
    void map_to_plot(const std::map<double, double>& data, std::string title);
    void three_dimentional_plot(std::vector<std::map<double, double>> r_lambda, std::vector<double> pressures);

private:
    Gnuplot gp;
};