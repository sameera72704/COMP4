#include <iostream>
#include "FibLFSR.hpp"

using namespace PhotoMagic;

int main() {
    try {
        // Initialize the LFSR with a binary seed
        FibLFSR lfsr("1011011000110110");

        std::cout << "Initial state: " << lfsr << std::endl;

        // Perform a few steps
        for (int i = 0; i < 10; ++i) {
            int next_bit = lfsr.step();
            std::cout << "State after step " << (i + 1) << ": " << lfsr << " (Next bit: " << next_bit << ")" << std::endl;
        }

        // Generate bits
        int generated_bits_5 = lfsr.generate(5);
        std::cout << "Generated value for 5 bits: " << generated_bits_5 << std::endl;

        int generated_bits_10 = lfsr.generate(10);
        std::cout << "Generated value for 10 bits: " << generated_bits_10 << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
