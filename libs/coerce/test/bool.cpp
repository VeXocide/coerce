//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE bool

#include <boost/coerce.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(source) {
    using namespace boost;

    BOOST_CHECK_EQUAL(coerce::as<std::string>(true), "true");
    BOOST_CHECK_EQUAL(coerce::as<std::string>(false), "false");
}

BOOST_AUTO_TEST_CASE(target) {
    using namespace boost;

    BOOST_CHECK_THROW(coerce::as<bool>(""), coerce::bad_cast);

    BOOST_CHECK_EQUAL(coerce::as<bool>("true"), true);
    BOOST_CHECK_EQUAL(coerce::as<bool>("false"), false);

    BOOST_CHECK_THROW(coerce::as<bool>("trueX"), coerce::bad_cast);
    BOOST_CHECK_THROW(coerce::as<bool>("XXX"), coerce::bad_cast);
}
