//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE char

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/coerce.hpp>
#include <boost/test/unit_test.hpp>

#include <string>

BOOST_AUTO_TEST_CASE(source) {
    using namespace boost;

    BOOST_CHECK_EQUAL(coerce::as<std::string>('\0'), std::string("\0", 1));
    BOOST_CHECK_EQUAL(coerce::as<std::string>(' '), " ");
    BOOST_CHECK_EQUAL(coerce::as<std::string>('\x23'), "\x23");
    BOOST_CHECK_EQUAL(coerce::as<std::string>('A'), "A");
}

BOOST_AUTO_TEST_CASE(target) {
    using namespace boost;

    BOOST_CHECK_THROW(coerce::as<char>(""), coerce::bad_cast);

    BOOST_CHECK_EQUAL(coerce::as<char>("\0"), '\0');
    BOOST_CHECK_EQUAL(coerce::as<char>(" "), ' ');
    BOOST_CHECK_EQUAL(coerce::as<char>("\x17"), '\x17');
    BOOST_CHECK_EQUAL(coerce::as<char>("A"), 'A');

    // http://cdn.svcs.c2.uclick.com/c2/c88fd5f0c8e9012d63f600163e41dd5b
    BOOST_CHECK_THROW(coerce::as<char>(L"\u2603"), coerce::bad_cast);

    BOOST_CHECK_THROW(coerce::as<char>("XXX"), coerce::bad_cast);
}
