// copyright 2024 Sameera Sakinala
#include <sys/resource.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include "EDistance.hpp"

// Function to get current memory usage
double getCurrentMemoryUsage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss / 1024.0;
}

// Function to get CPU information
std::string getCPUInfo() {
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    while (std::getline(cpuinfo, line)) {
        if (line.substr(0, 10) == "model name") {
            return line.substr(line.find(":") + 2);
        }
    }
    return "Unknown";
}

int main() {
    std::string x, y;
    std::cin >> x >> y;
    double initialMemory = getCurrentMemoryUsage();
    auto start = std::chrono::high_resolution_clock::now();
    EDistance ed(x, y);
    int distance = ed.optDistance();
    std::string alignment = ed.alignment();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    double finalMemory = getCurrentMemoryUsage();
std::cout << "Edit distance = " << distance << std::endl;
    std::cout << alignment;
    std::cout << "Execution time is " << diff.count() << " seconds" << std::endl;
    std::cout << "Memory used: " << (finalMemory - initialMemory) << " MB" << std::endl;

    auto minComparisonResults = ed.minComparisonAnalysis();
    std::cout << "\nMin Comparison Analysis:" << std::endl;
    for (const auto& [a, b, c, min3_result, direct_result, is_equal] : minComparisonResults) {
std::cout <<
"(" << a << ", " << b << ", " << c << "): min3 = " << min3_result
<< ", direct = " << direct_result << ", equal: " << (is_equal ? "true" : "false") << std::endl;
    }

    auto [unoptimized_time, optimized_time] = ed.optimizationComparisonAnalysis();
    std::cout << "\nOptimization Comparison Analysis:" << std::endl;
    std::cout << "Unoptimized time: " << unoptimized_time << " seconds" << std::endl;
    std::cout << "Optimized time: " << optimized_time << " seconds" << std::endl;

    return 0;
}
