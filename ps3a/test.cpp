// copyright 2024 Sameera Sakinala
#define BOOST_TEST_MODULE GalaxyModelTests
#include <boost/test/included/unit_test.hpp>
#include "Universe.hpp"
#include "CelestialBody.hpp"

BOOST_AUTO_TEST_SUITE(GalaxyTests)

BOOST_AUTO_TEST_CASE(GalaxyConstructionAndIO) {
    NB::Universe galaxyModel;
    std::stringstream dataStream("2 1.0000e+06\n"
    "1.0000e+00 2.0000e+00 3.0000e+00 4.0000e+00 5.0000e+00 earth.gif\n"
    "6.0000e+00 7.0000e+00 8.0000e+00 9.0000e+00 1.0000e+01 mars.gif");
    dataStream >> galaxyModel;

    BOOST_CHECK_EQUAL(galaxyModel.size(), 2);

    BOOST_CHECK_CLOSE(galaxyModel.getRadius(), 1.0000e+06, 0.001);

    std::stringstream outputStream;
    outputStream << galaxyModel;

    std::string expectedOutput = "2\n1.0000e+06\n"
    "1.0000e+00 2.0000e+00 3.0000e+00 4.0000e+00 5.0000e+00 earth.gif\n"
    "6.0000e+00 7.0000e+00 8.0000e+00 9.0000e+00 1.0000e+01 mars.gif\n";

    BOOST_CHECK_EQUAL(outputStream.str(), expectedOutput);
}

BOOST_AUTO_TEST_CASE(GalaxyIndexOperator) {
    NB::Universe galaxyModel;
    std::stringstream dataStream("2 1.0000e+06\n"
    "1.0000e+00 2.0000e+00 3.0000e+00 4.0000e+00 5.0000e+00 earth.gif\n"
    "6.0000e+00 7.0000e+00 8.0000e+00 9.0000e+00 1.0000e+01 mars.gif");
    dataStream >> galaxyModel;

    BOOST_CHECK_CLOSE(galaxyModel[0].getPosition().x, 1.0000e+00, 0.001);
    BOOST_CHECK_CLOSE(galaxyModel[1].getPosition().y, 7.0000e+00, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()
