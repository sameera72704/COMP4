// Copyright 2024 By Sameera Sakinala
// Editted by Dr. Daly
// test.cpp for PS1a
#include <iostream>
#include <string>

#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

using PhotoMagic::FibLFSR;


BOOST_AUTO_TEST_CASE(testStepInstr) {
FibLFSR l("1011011000110110");
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 1);
BOOST_REQUIRE_EQUAL(l.step(), 1);
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 0);
BOOST_REQUIRE_EQUAL(l.step(), 1);
FibLFSR l1("1100100010011110");
BOOST_REQUIRE_EQUAL(l1.step(), 0);
BOOST_REQUIRE_EQUAL(l1.step(), 1);
BOOST_REQUIRE_EQUAL(l1.step(), 0);
BOOST_REQUIRE_EQUAL(l1.step(), 0);
BOOST_REQUIRE_EQUAL(l1.step(), 1);
BOOST_REQUIRE_EQUAL(l1.step(), 1);
BOOST_REQUIRE_EQUAL(l1.step(), 0);
BOOST_REQUIRE_EQUAL(l1.step(), 1);
FibLFSR l2("1010111010101010");
BOOST_REQUIRE_EQUAL(l2.step(), 1);
BOOST_REQUIRE_EQUAL(l2.step(), 0);
BOOST_REQUIRE_EQUAL(l2.step(), 1);
BOOST_REQUIRE_EQUAL(l2.step(), 1);
BOOST_REQUIRE_EQUAL(l2.step(), 0);
BOOST_REQUIRE_EQUAL(l2.step(), 0);
BOOST_REQUIRE_EQUAL(l2.step(), 1);
BOOST_REQUIRE_EQUAL(l2.step(), 1);

FibLFSR l3("1010111110101010");
BOOST_REQUIRE_EQUAL(l3.step(), 1);
BOOST_REQUIRE_EQUAL(l3.step(), 0);
BOOST_REQUIRE_EQUAL(l3.step(), 1);
BOOST_REQUIRE_EQUAL(l3.step(), 1);
BOOST_REQUIRE_EQUAL(l3.step(), 0);
BOOST_REQUIRE_EQUAL(l3.step(), 1);
BOOST_REQUIRE_EQUAL(l3.step(), 0);
BOOST_REQUIRE_EQUAL(l3.step(), 1);

FibLFSR l4("1110001101010100");
BOOST_REQUIRE_EQUAL(l4.step(), 0);
BOOST_REQUIRE_EQUAL(l4.step(), 1);
BOOST_REQUIRE_EQUAL(l4.step(), 1);
BOOST_REQUIRE_EQUAL(l4.step(), 0);
BOOST_REQUIRE_EQUAL(l4.step(), 0);
BOOST_REQUIRE_EQUAL(l4.step(), 1);
BOOST_REQUIRE_EQUAL(l4.step(), 1);
BOOST_REQUIRE_EQUAL(l4.step(), 0);
}

BOOST_AUTO_TEST_CASE(testGenerateInstr) {
FibLFSR l("1011011000110110");
BOOST_REQUIRE_EQUAL(l.generate(9), 51);

FibLFSR l1("1100100010011110");
BOOST_REQUIRE_EQUAL(l1.generate(5), 18);

FibLFSR l2("1010111010101010");
BOOST_REQUIRE_EQUAL(l2.generate(4), 10);

FibLFSR l3("1010111110101010");
BOOST_REQUIRE_EQUAL(l3.generate(5), 21);

FibLFSR l4("1110001101010100");
BOOST_REQUIRE_EQUAL(l4.generate(3), 5);
}
