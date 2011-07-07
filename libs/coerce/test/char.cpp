//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE char

#include <boost/coerce.hpp>
#include <boost/test/unit_test.hpp>

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

    BOOST_CHECK_THROW(coerce::as<char>(L"\u2345"), coerce::bad_cast);

    BOOST_CHECK_THROW(coerce::as<char>("XXX"), coerce::bad_cast);
}

/*  lexical_cast

    BOOST_CHECK_EQUAL('A', lexical_cast<char>('A'));
    BOOST_CHECK_EQUAL(' ', lexical_cast<char>(' '));
    BOOST_CHECK_EQUAL('1', lexical_cast<char>(1));
    BOOST_CHECK_EQUAL('0', lexical_cast<char>(0));
    BOOST_CHECK_THROW(lexical_cast<char>(123), bad_lexical_cast);
    BOOST_CHECK_EQUAL('1', lexical_cast<char>(1.0));
    BOOST_CHECK_EQUAL('1', lexical_cast<char>(true));
    BOOST_CHECK_EQUAL('0', lexical_cast<char>(false));
    BOOST_CHECK_EQUAL('A', lexical_cast<char>("A"));
    BOOST_CHECK_EQUAL(' ', lexical_cast<char>(" "));
    BOOST_CHECK_THROW(lexical_cast<char>(""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<char>("Test"), bad_lexical_cast);
    BOOST_CHECK_EQUAL('A', lexical_cast<char>(std::string("A")));
    BOOST_CHECK_EQUAL(' ', lexical_cast<char>(std::string(" ")));
    BOOST_CHECK_THROW(
        lexical_cast<char>(std::string("")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<char>(std::string("Test")), bad_lexical_cast);
*/
