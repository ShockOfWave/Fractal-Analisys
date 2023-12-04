#include "hasNumber.h"

bool hasNumber(const std::vector<int> vec, int numberToFind) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == numberToFind) {
            return false;
        }
    }
    return true;
}
