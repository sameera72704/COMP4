// Copyright 2024 Sameera Sakinala
#ifndef RANDWRITER_HPP
#define RANDWRITER_HPP

#include <string>
#include <map>
#include <random>
#include <functional>

class RandWriter {
 public:
    RandWriter(const std::string& text, size_t k);
    size_t orderK() const;
    int freq(const std::string& kgram) const;
    int freq(const std::string& kgram, char c) const;
    char kRand(const std::string& kgram);
    std::string generate(const std::string& kgram, size_t L);

    // Lambda function parameter usage
    void transformAlphabet(const std::function<char(char)>& func);

    friend std::ostream& operator<<(std::ostream& os, const RandWriter& rw);

 private:
    size_t k;
    std::string alphabet;
    std::map<std::string, std::map<char, int>> freqMap;
    std::mt19937 rng;
};
#endif  // RANDWRITER_HPP
