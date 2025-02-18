// Copyright 2024 Sameera Sakinala
#include "RandWriter.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <random>

RandWriter::RandWriter(const std::string& text, size_t k)
    : k(k), rng(std::random_device { } ()) {
    if (text.length() < k) {
        throw std::invalid_argument
        ("Text length must be at least the value of k.");
    }

    const size_t n = text.length();
    for (size_t i = 0; i < n; ++i) {
        std::string kgram = text.substr(i, k);
        if (kgram.length() < k) {
            kgram += text.substr(0, k - kgram.length());
        }
        const char nextChar = text[(i + k) % n];
        freqMap[kgram][nextChar]++;

        if (alphabet.find(nextChar) == std::string::npos) {
            alphabet += nextChar;
        }
    }
}

size_t RandWriter::orderK() const {
    return k;
}

int RandWriter::freq(const std::string& kgram) const {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram must be of length k.");
    }

    const auto it = freqMap.find(kgram);
    if (it != freqMap.end()) {
        int total = 0;
        for (const auto& pair : it->second) {
            total += pair.second;
        }
        return total;
    }
    return 0;
}

int RandWriter::freq(const std::string& kgram, char c) const {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram must be of length k.");
    }

    const auto it = freqMap.find(kgram);
    if (it != freqMap.end()) {
        const auto charIt = it->second.find(c);
        if (charIt != it->second.end()) {
            return charIt->second;
        }
    }
    return 0;
}

char RandWriter::kRand(const std::string& kgram) {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram must be of length k.");
    }

    const auto it = freqMap.find(kgram);
    if (it == freqMap.end()) {
        throw std::runtime_error("No such kgram exists in the frequency map.");
    }

    const int total = freq(kgram);
    if (total == 0) {
        throw std::runtime_error("No valid transitions from this kgram.");
    }

    std::uniform_int_distribution<> dis(1, total);
    const int r = dis(rng);

    int sum = 0;
    for (const auto& pair : it->second) {
        sum += pair.second;
        if (r <= sum) {
            return pair.first;
        }
    }
    throw std::runtime_error
    ("Unexpected error: kRand failed to select a character.");
}
std::string RandWriter::generate(const std::string& kgram, size_t L) {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram must be of length k.");
    }
    if (L < k) {
        throw std::invalid_argument("L must be at least the value of k.");
    }

    std::string result = kgram;  // Start with the provided k-gram
    result.reserve(L);           // Reserve space for efficiency

    while (result.length() < L) {
        std::string currentKgram = result.substr(result.length() - k, k);
        char nextChar = kRand(currentKgram);
        result += nextChar;
    }

    return result;
}
void RandWriter::transformAlphabet(const std::function<char(char)>& func) {
    for (char& c : alphabet) {
        c = func(c);  // Apply the lambda to each character
    }

    // Ensure the alphabet remains ordered
    std::sort(alphabet.begin(), alphabet.end());
}


std::ostream& operator<<(std::ostream& os, const RandWriter& rw) {
    os << "Order: " << rw.k << "\n";
    os << "Alphabet: " << rw.alphabet << "\n";
    os << "Frequencies:\n";

    for (const auto& outer : rw.freqMap) {
        for (const auto& inner : outer.second) {
            os << outer.first << inner.first << ": " << inner.second << "\n";
        }
    }

    return os;
}
