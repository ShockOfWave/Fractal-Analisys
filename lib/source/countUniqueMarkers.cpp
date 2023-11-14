#include "countUniqueMarkers.h"

Marks countUniqueMarkers(const std::vector<std::vector<int> >& matrix) {
    int width = matrix[0].size();
    int height = matrix.size();
    Marks marks;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int currentMarker = matrix[y][x];
            if (currentMarker < 0) {
                if (std::find(marks.zero_marks.begin(), marks.zero_marks.end(), currentMarker) == marks.zero_marks.end()) {
                    marks.zero_marks.push_back(currentMarker);
                }
            }
            else if (currentMarker > 0) {
                if (std::find(marks.un_marks.begin(), marks.un_marks.end(), currentMarker) == marks.un_marks.end()) {
                    marks.un_marks.push_back(currentMarker);
                }
            }
        }
    }

    return marks;
}
