//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE default

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/coerce.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(default_) {
    using namespace boost;

    BOOST_CHECK_EQUAL(coerce::as_default<int>("XXX"), 0);
    BOOST_CHECK_EQUAL(coerce::as_default<int>("XXX", 23), 23);
}
