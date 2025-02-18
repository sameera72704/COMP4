// copyright 2024 Sameera Sakinala

#include <iostream>
#include "FibLFSR.hpp"

namespace PhotoMagic {

    FibLFSR::FibLFSR(const std::string& seed) : reg(seed) {}

    int FibLFSR::step() {
        int tap13 = reg[2] - '0';  // Position 13
        int tap12 = reg[3] - '0';  // Position 12
        int tap10 = reg[5] - '0';  // Position 10
        int leftmost = reg[0] - '0';  // Leftmost bit

        int newBit = leftmost ^ tap13 ^ tap12 ^ tap10;

        reg = reg.substr(1) + std::to_string(newBit);

        return newBit;
    }

    int FibLFSR::generate(int k) {
        int result = 0;
        for (int i = 0; i < k; ++i) {
            result = (result << 1) | step();
        }
        return result;
    }

    std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr) {
        out << lfsr.reg;
        return out;
    }
}  //  namespace PhotoMagic
