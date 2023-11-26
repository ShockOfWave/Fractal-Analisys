#include "Bradly_threshold.h"

void Bradley_threshold(const std::vector<std::vector<double>>&& src, std::vector<std::vector<int>>&& res,
    int width, int height, double pressure) {

    const double S = static_cast<double> (width / 8);
    double s2 = S / 2;
    const double t = 0.70;
    double sum = 0.0;
    double count = 0.0;
    int index;
    double x1;
    double x2;
    double y1;
    double y2;
    std::vector<double> integral_image(width * height);

    for (int i = 0; i < width; i++) {
        sum = 0;
        for (int j = 0; j < height; j++) {
            index = j * width + i;
            sum += (src[i][j]);
            if (i == 0)
                integral_image[index] = sum;
            else
                integral_image[index] = integral_image[index - 1] + sum;
        }
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int index = j * width + i;

            x1 = i - s2;
            x2 = i + s2;
            y1 = j - s2;
            y2 = j + s2;

            if (x1 < 0)
                x1 = 0;
            if (x2 >= width)
                x2 = width - 1;
            if (y1 < 0)
                y1 = 0;
            if (y2 >= height)
                y2 = height - 1;

            count = (x2 - x1) * (y2 - y1);
            
            sum = integral_image[y2 * width + x2] - integral_image[y1 * width + x2] - integral_image[y2 * width + x1] + integral_image[y1 * width + x1];
            
            if ((src[i][j] * count * pressure) < (sum * (1.0 - t))) {
                res[i][j] = 0;
            }
            else {
                res[i][j] = 1;
            }
        }
    }
}
