#include "plotter.h"

//Plotter::Plotter() : gp("\"C:/Program Files/gnuplot/bin/gnuplot.exe\"") {}

Plotter& Plotter::set_xlabel(const std::string& label)
{
    gp << "set xlabel '" << label << "'\n";
    return *this;
}

Plotter& Plotter::set_ylabel(const std::string& label)
{
    gp << "set ylabel '" << label << "'\n";
    return *this;
}

Plotter& Plotter::set_zlabel(const std::string& label)
{
    gp << "set zlabel '" << label << "'\n";
    return *this;
}

Plotter& Plotter::set_title(const std::string& title)
{
    gp << "set title '" << title << "'\n";
    return *this;
}

Plotter& Plotter::set_grid(bool enable)
{
    if (enable) {
        gp << "set grid\n";
    }
    else {
        gp << "unset grid\n";
    }
    return *this;
}

void Plotter::line_plot(const std::vector<double>& x, const std::vector<double>& y, const std::string& title)
{
    gp << "set terminal wxt title 'Graph'\n";
    gp << "plot '-' with points pointtype 7 pointsize 1 title '" << title << "'\n";
    gp.send1d(std::make_pair(x, y));
}

void Plotter::couple_lines_plot(const std::vector<double>& x, const std::vector<double>& y1, const std::vector<double>& y2, const std::string& title1, const std::string& title2)
{
    gp << "set terminal wxt title 'Graph'\n";
    gp << "plot '-' with points pointtype 7 pointsize 1 title '" << title1 << "', '-' with points pointtype 2 pointsize 1 title '" << title2 << "'\n";
    gp.send1d(std::make_pair(x, y1));
    gp.send1d(std::make_pair(x, y2));
}

void Plotter::triple_lines_plot(const std::vector<double>& x, const std::vector<int>& y1, const std::vector<int>& y2, const std::vector<int>& y3, const std::string& title1, const std::string& title2, const std::string& title3)
{
    gp << "set terminal wxt title 'Graph'\n";
    gp << "plot '-' with points pointtype 7 pointsize 1.2 title '" << title1 << "', '-' with points pointtype 5 pointsize 1.2 title '" << title2 << "', '-' with points pointtype 11 pointsize 1.5 title'" << title3 << "'\n";
    gp.send1d(std::make_pair(x, y1));
    gp.send1d(std::make_pair(x, y2));
    gp.send1d(std::make_pair(x, y3));
}

void Plotter::map_to_plot(const std::map<double, double>& data, std::string title) {

    std::vector<std::pair<double, double>> plotData;

    for (const auto& entry : data) {
        plotData.emplace_back(entry.first, entry.second);
    }

    gp << "set terminal wxt title 'Graph'\n";
    gp << "plot '-' with linespoints linecolor rgb 'blue' linewidth 2 pointtype 7 pointsize 1 title '" << title << "'\n";
    gp.send1d(plotData);
}



void Plotter::three_dimentional_plot(std::vector<std::map<double, double>> r_lambda, std::vector<double> pressures)
{
    std::vector<double> xData;
    std::vector<double> yData;
    std::vector<double> zData;

    
    /*gp << "plot '-' with points pointtype 7 pointsize 1 title '" << title1 << "', '-' with points pointtype 2 pointsize 1 title '"
        << title2 << "', '-' with points pointtype 9 pointsize 1 title'" << title3 << "'\n";*/
    for (const auto& cols : r_lambda) {
        for (const auto& pair : cols) {
            xData.push_back(pair.first);
            yData.push_back(pair.second);
        }
        std::cout << " x " << xData.size() << " y " << yData.size() << " z " << pressures.size() << "\n";
        
    }

    gp << "set terminal wxt title 'Graph'\n";
    gp << "set hidden3d\n";
    gp << "set isosample 100, 100\n";
    gp << "splot '-' with points pointtype 7 pointsize 3\n";

    // Передача точек для построения трехмерного графика
    for (size_t i = 0; i < xData.size(); ++i) {
        gp << xData[i] << " " << yData[i] << " " << pressures[i] << "\n";
    }

    gp << "e\n";
}