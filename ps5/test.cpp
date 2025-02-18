// copyright 2024 Sameera Sakinala
#include <algorithm>
#include <sstream>
#include <vector>
#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/included/unit_test.hpp>
#include "EDistance.hpp"

BOOST_AUTO_TEST_CASE(test_penalty) {
    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'A'), 0);
    BOOST_CHECK_EQUAL(EDistance::penalty('A', 'T'), 1);
}

BOOST_AUTO_TEST_CASE(test_min3) {
    BOOST_CHECK_EQUAL(EDistance::min3(1, 2, 3), 1);
    BOOST_CHECK_EQUAL(EDistance::min3(3, 1, 2), 1);
    BOOST_CHECK_EQUAL(EDistance::min3(3, 2, 1), 1);
}

BOOST_AUTO_TEST_CASE(test_optDistance) {
    EDistance ed1("AACAGTTACC", "TAAGGTCA");
    BOOST_CHECK_EQUAL(ed1.optDistance(), 7);
    EDistance ed2("", "ACATAG");
    BOOST_CHECK_EQUAL(ed2.optDistance(), 12);
    EDistance ed3("AGTACG", "");
    BOOST_CHECK_EQUAL(ed3.optDistance(), 12);
}

BOOST_AUTO_TEST_CASE(test_alignment) {
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    ed.optDistance();
    std::string alignment = ed.alignment();
    BOOST_CHECK(!alignment.empty());
    BOOST_CHECK(alignment.find("A T") < alignment.rfind("C A"));
    BOOST_CHECK(alignment.find("A T") != std::string::npos);
    BOOST_CHECK(alignment.rfind("C A") != std::string::npos);
    int lineCount = std::count(alignment.begin(), alignment.end(), '\n');
    BOOST_CHECK_EQUAL(lineCount, 10);
}

BOOST_AUTO_TEST_CASE(test_swapped_strings) {
    EDistance ed1("AACAGTTACC", "TAAGGTCA");
    EDistance ed2("TAAGGTCA", "AACAGTTACC");
    BOOST_CHECK_EQUAL(ed1.optDistance(), ed2.optDistance());
    std::string alignment1 = ed1.alignment();
    std::string alignment2 = ed2.alignment();
    BOOST_CHECK_NE(alignment1, alignment2);
}

BOOST_AUTO_TEST_CASE(test_alignment_direction) {
    EDistance ed("AGT", "ACA");
    ed.optDistance();
    std::string alignment = ed.alignment();
    BOOST_CHECK(alignment.find("A A") < alignment.find("G C"));
    BOOST_CHECK(alignment.find("G C") < alignment.find("T A"));
}

BOOST_AUTO_TEST_CASE(test_alignment_completeness) {
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    ed.optDistance();
    std::string alignment = ed.alignment();
    std::vector<std::string> lines;
    std::istringstream iss(alignment);
    for (std::string line; std::getline(iss, line); ) {
        lines.push_back(line);
    }
    BOOST_CHECK_EQUAL(lines.size(), 10);
    BOOST_CHECK(lines.front().find('A') != std::string::npos ||
                lines.front().find('T') != std::string::npos);
    BOOST_CHECK(lines.back().find('C') != std::string::npos ||
                lines.back().find('A') != std::string::npos);
    std::string seq1, seq2;
    for (const auto& line : lines) {
        if (line[0] != '-') seq1 += line[0];
        if (line[2] != '-') seq2 += line[2];
    }
    BOOST_CHECK_EQUAL(seq1, "AACAGTTACC");
    BOOST_CHECK_EQUAL(seq2, "TAAGGTCA");
    std::string expected_chars = "AACAGTTACCTAAGGTCA-";
    for (char c : expected_chars) {
        BOOST_CHECK(alignment.find(c) != std::string::npos);
    }
}
BOOST_AUTO_TEST_CASE(test_alignment_tail_completeness) {
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    ed.optDistance();
    std::string alignment = ed.alignment();
    
    // Print the alignment for debugging
    BOOST_TEST_MESSAGE("Alignment:\n" << alignment);
    
    // Check that the alignment starts and ends with correct characters from the sequences
    BOOST_CHECK_MESSAGE(alignment.find("A") != std::string::npos, "First 'A' not found in alignment");
    BOOST_CHECK_MESSAGE(alignment.rfind("C") != std::string::npos, "Last 'C' not found in alignment");
    BOOST_CHECK_MESSAGE(alignment.find("T") != std::string::npos, "First 'T' not found in alignment");
    BOOST_CHECK_MESSAGE(alignment.rfind("A") != std::string::npos, "Last 'A' not found in alignment");
    
    // Split the alignment into lines
    std::vector<std::string> lines;
    std::istringstream iss(alignment);
    std::string line;
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    
    // Check the number of lines
    BOOST_CHECK_MESSAGE(lines.size() == 10, "Expected 10 lines in alignment, got " << lines.size());
    
    // Check the first and last lines
    if (!lines.empty()) {
        BOOST_CHECK_MESSAGE(lines.front().find('A') != std::string::npos || lines.front().find('T') != std::string::npos,
                            "First line doesn't contain 'A' or 'T'");
        BOOST_CHECK_MESSAGE(lines.back().find('C') != std::string::npos || lines.back().find('A') != std::string::npos,
                            "Last line doesn't contain 'C' or 'A'");
    } else {
        BOOST_ERROR("Alignment is empty");
    }
}