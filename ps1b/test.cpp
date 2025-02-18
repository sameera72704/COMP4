// Copyright 2024 Sameera Sakinala

#include <iostream>
#define BOOST_TEST_MAIN
#include "FibLFSR.hpp"
#include <boost/test/included/unit_test.hpp>
using PhotoMagic::FibLFSR;
BOOST_AUTO_TEST_CASE(testStepInstr) {
    FibLFSR l("1011011000110110");
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 0);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
    BOOST_REQUIRE_EQUAL(l.step(), 1);
}
BOOST_AUTO_TEST_CASE(testGenerateInstr) {
    FibLFSR l("1011011000110110");
    BOOST_REQUIRE_EQUAL(l.generate(9), 51);
}
BOOST_AUTO_TEST_CASE(testStreamOutput) {
    FibLFSR l("1011011000110110");
    std::ostringstream oss;
    oss << l;
    BOOST_REQUIRE_EQUAL(oss.str(), "1011011000110110");
}
BOOST_AUTO_TEST_CASE(testGenerateMultiple) {
    FibLFSR l("1011011000110110");
    BOOST_REQUIRE_EQUAL(l.generate(5), 3);
    BOOST_REQUIRE_EQUAL(l.generate(10), 206);
}
