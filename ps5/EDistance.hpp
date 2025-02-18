// copyright 2024 Sameera Sakinala

#ifndef EDISTANCE_HPP
#define EDISTANCE_HPP
#include <string>
#include <vector>
#include <tuple>

class EDistance {
 private:
    std::string x, y;
    std::vector<std::vector<int>> opt;

 public:
    EDistance(const std::string& x, const std::string& y);
    ~EDistance();

    static int penalty(char a, char b);
    static int min3(int a, int b, int c);

    int optDistance();
    std::string alignment();

    // New functions
    std::vector<std::tuple<int, int, int, int, int, bool>> minComparisonAnalysis();
    std::pair<double, double> optimizationComparisonAnalysis();
};

#endif   //   EDISTANCE_HPP
