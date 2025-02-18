// copyright 2024 Sameera Sakinala
#include "EDistance.hpp"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <chrono>

EDistance::EDistance(const std::string& x, const std::string& y) : x(x), y(y) {
    opt.resize(x.length() + 1, std::vector<int>(y.length() + 1, 0));
}

EDistance::~EDistance() {}

int EDistance::penalty(char a, char b) {
    return (a == b) ? 0 : 1;
}

int EDistance::min3(int a, int b, int c) {
    return std::min({a, b, c});
}

int EDistance::optDistance() {
    int m = x.length(), n = y.length();
    // Initialize the base cases
    for (int i = 0; i <= m; i++) opt[i][n] = 2 * (m - i);
    for (int j = 0; j <= n; j++) opt[m][j] = 2 * (n - j);
    // Fill the matrix
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            opt[i][j] = min3(
                opt[i + 1][j + 1] + penalty(x[i], y[j]),
                opt[i + 1][j] + 2,
                opt[i][j + 1] + 2);
        }
    }
    return opt[0][0];
}

std::string EDistance::alignment() {
    std::ostringstream result;
    std::string::size_type i = 0, j = 0;
    while (i < x.size() || j < y.size()) {
        if (i < x.size() && j < y.size() && opt[i][j] == opt[i + 1][j + 1] + penalty(x[i], y[j])) {
            result << x[i] << " " << y[j] << " " << penalty(x[i], y[j]) << "\n";
            ++i;
            ++j;
        } else if (i < x.size() && opt[i][j] == opt[i + 1][j] + 2) {
            result << x[i] << " - 2\n";
            ++i;
        } else {
            result << "- " << y[j] << " 2\n";
            ++j;
        }
    }
    return result.str();
}

std::vector<std::tuple<int, int, int, int, int, bool>> EDistance::minComparisonAnalysis() {
    std::vector<std::tuple<int, int, int, int, int, bool>> results;
    std::vector<std::tuple<int, int, int>> test_values = {{3, 5, 2}, {10, 1, 7}, {6, 6, 6}};
    for (const auto& [a, b, c] : test_values) {
        int min3_result = min3(a, b, c);
        int direct_result = std::min({a, b, c});
        results.emplace_back(a, b, c, min3_result, direct_result, min3_result == direct_result);
    }
    return results;
}

std::pair<double, double> EDistance::optimizationComparisonAnalysis() {
    auto start = std::chrono::high_resolution_clock::now();
    optDistance();  // Run the unoptimized version
    auto end = std::chrono::high_resolution_clock::now();
    double unoptimized_time = std::chrono::duration<double>(end - start).count();

    // Placeholder for optimized version
    start = std::chrono::high_resolution_clock::now();
    optDistance();
    end = std::chrono::high_resolution_clock::now();
    double optimized_time = std::chrono::duration<double>(end - start).count();

    return {unoptimized_time, optimized_time};
}
