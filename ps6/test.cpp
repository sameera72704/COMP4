// Copyright 2024 Sameera Sakinala
#define BOOST_TEST_MODULE RandWriterTest
#include <boost/test/included/unit_test.hpp>
#include "RandWriter.hpp"

BOOST_AUTO_TEST_CASE(constructor_test) {
    BOOST_REQUIRE_NO_THROW(RandWriter("abcde", 2));
    BOOST_REQUIRE_THROW(RandWriter("abc", 4), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(order_k_test) {
    RandWriter rw("abcde", 2);
    BOOST_REQUIRE_EQUAL(rw.orderK(), 2);
}

BOOST_AUTO_TEST_CASE(freq_test) {
    RandWriter rw("gagggagaggcgagaaa", 2);
    BOOST_REQUIRE_EQUAL(rw.freq("ga"), 5);
    BOOST_REQUIRE_EQUAL(rw.freq("gg"), 3);
    BOOST_REQUIRE_EQUAL(rw.freq("aa"), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("zz"), 0);
    BOOST_REQUIRE_THROW(rw.freq("a"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(freq_char_test) {
    RandWriter rw("gagggagaggcgagaaa", 2);
    BOOST_REQUIRE_EQUAL(rw.freq("ga", 'g'), 4);
    BOOST_REQUIRE_EQUAL(rw.freq("ga", 'a'), 1);
    BOOST_REQUIRE_EQUAL(rw.freq("gg", 'g'), 1);
    BOOST_REQUIRE_EQUAL(rw.freq("gg", 'a'), 1);
    BOOST_REQUIRE_EQUAL(rw.freq("aa", 'a'), 1);
    BOOST_REQUIRE_EQUAL(rw.freq("zz", 'a'), 0);
    BOOST_REQUIRE_THROW(rw.freq("a", 'a'), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(krand_test) {
    RandWriter rw("gagggagaggcgagaaa", 2);
    std::string kgram = "ga";
    std::map<char, int> counts;
    for (int i = 0; i < 1000; ++i) {
        counts[rw.kRand(kgram)]++;
    }
    BOOST_REQUIRE(counts['g'] > 700);
    BOOST_REQUIRE(counts['a'] > 100);
    BOOST_REQUIRE(counts['c'] < 100);
    BOOST_REQUIRE_THROW(rw.kRand("zz"), std::runtime_error);
    BOOST_REQUIRE_THROW(rw.kRand("a"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(generate_test) {
    RandWriter rw("gagggagaggcgagaaa", 2);
    std::string generated = rw.generate("ga", 20);
    BOOST_REQUIRE_EQUAL(generated.length(), 20);
    BOOST_REQUIRE_EQUAL(generated.substr(0, 2), "ga");
    BOOST_REQUIRE_THROW(rw.generate("a", 20), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.generate("ga", 1), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(generate_length_test) {
    RandWriter rw("gagggagaggcgagaaa", 2);

    std::string generated = rw.generate("ga", 300);
    BOOST_REQUIRE_EQUAL(generated.length(), 300);
    BOOST_REQUIRE_EQUAL(generated.substr(0, 2), "ga");
}BOOST_AUTO_TEST_CASE(transform_alphabet_test) {
    RandWriter rw("abcdef", 2);

    rw.transformAlphabet([](char c) { return std::toupper(c); });

    std::ostringstream oss;
    oss << rw;
    std::string output = oss.str();
    std::cout << "Generated output: " << output << std::endl;

    // Check if the alphabet contains uppercase letters
    BOOST_REQUIRE_MESSAGE(
        output.find("ABCDEF") != std::string::npos,
        "Alphabet transformation failed. Output: " + output);
}
