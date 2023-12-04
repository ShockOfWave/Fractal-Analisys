#include "logFrom.h"

#include <cmath>

void logFrom(std::map<int, int> counts, std::vector<double>&& logs) {
    for (const auto& pair : counts) {
        double originalValue = pair.second;
        double logValue = std::log10(originalValue);
        logs.push_back(logValue);
    }
}
