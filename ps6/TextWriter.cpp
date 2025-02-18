// Copyright 2024 Sameera Sakinala

#include <iostream>
#include <sstream>
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
    // Check for correct usage
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <k> <L>\n";
        return 1;
    }

    // Parse arguments for order and length
    const size_t k = static_cast<size_t>(std::stoul(argv[1]));
    const size_t L = static_cast<size_t>(std::stoul(argv[2]));

    // Read input text from standard input
    std::ostringstream oss;
    oss << std::cin.rdbuf();

    // Validate input text is not empty
    const std::string inputText = oss.str();
    if (inputText.empty()) {
        std::cerr << "Error: Input text cannot be empty.\n";
        return 1;
    }

    try {
        RandWriter rw(inputText, k);
        // Generate output starting with the first 'k' characters as seed
        std::cout << rw.generate(inputText.substr(0, k), L) << '\n';
    } catch (const std::exception& e) {
        // Handle any exceptions thrown by RandWriter
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
