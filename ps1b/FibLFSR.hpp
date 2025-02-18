// copyright 2024 Sameera Sakinala

#pragma once
#include <iostream>
#include <string>

namespace PhotoMagic {
class FibLFSR {
 public:
    explicit FibLFSR(const std::string& seed);

    int step();
    int generate(int k);

    friend std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr);

 private:
    std::string reg;  //  The LFSR register string
};
}   //  namespace PhotoMagic
