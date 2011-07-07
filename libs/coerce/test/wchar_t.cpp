//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE wchar_t

#include <boost/coerce.hpp>
#include <boost/config.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(source) {
    using namespace boost;

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_CHECK_EQUAL(coerce::as<std::string>(L'\0'), std::string("\0", 1));
    BOOST_CHECK_EQUAL(coerce::as<std::string>(L' '), " ");
    BOOST_CHECK_EQUAL(coerce::as<std::string>(L'\x23'), "\x23");
    BOOST_CHECK_EQUAL(coerce::as<std::string>(L'A'), "A");
#endif
}

BOOST_AUTO_TEST_CASE(target) {
    using namespace boost;

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_CHECK_THROW(coerce::as<wchar_t>(""), coerce::bad_cast);

    BOOST_CHECK_EQUAL(coerce::as<wchar_t>("\0"), L'\0');
    BOOST_CHECK_EQUAL(coerce::as<wchar_t>(" "), L' ');
    BOOST_CHECK_EQUAL(coerce::as<wchar_t>("\x23"), L'\x23');
    BOOST_CHECK_EQUAL(coerce::as<wchar_t>("A"), L'A');

    BOOST_CHECK_THROW(coerce::as<wchar_t>("XXX"), coerce::bad_cast);
#endif
}

/*  lexical_cast

    BOOST_CHECK_EQUAL(L'1', lexical_cast<wchar_t>(1));
    BOOST_CHECK_EQUAL(L'0', lexical_cast<wchar_t>(0));
    BOOST_CHECK_EQUAL(L'1', lexical_cast<wchar_t>('1'));
    BOOST_CHECK_EQUAL(L'0', lexical_cast<wchar_t>('0'));
    BOOST_CHECK_THROW(lexical_cast<wchar_t>(123), bad_lexical_cast);
    BOOST_CHECK_EQUAL(L'1', lexical_cast<wchar_t>(1.0));
    BOOST_CHECK_EQUAL(L'0', lexical_cast<wchar_t>(0.0));
    BOOST_CHECK_EQUAL(L'1', lexical_cast<wchar_t>(true));
    BOOST_CHECK_EQUAL(L'0', lexical_cast<wchar_t>(false));
    BOOST_CHECK_EQUAL(L'A', lexical_cast<wchar_t>(L'A'));
    BOOST_CHECK_EQUAL(L' ', lexical_cast<wchar_t>(L' '));
    BOOST_CHECK_EQUAL(L'A', lexical_cast<wchar_t>(L"A"));
    BOOST_CHECK_EQUAL(L' ', lexical_cast<wchar_t>(L" "));
    BOOST_CHECK_THROW(lexical_cast<wchar_t>(L""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<wchar_t>(L"Test"), bad_lexical_cast);
    BOOST_CHECK_EQUAL(L'A', lexical_cast<wchar_t>(std::wstring(L"A")));
    BOOST_CHECK_EQUAL(L' ', lexical_cast<wchar_t>(std::wstring(L" ")));
    BOOST_CHECK_THROW(
        lexical_cast<wchar_t>(std::wstring(L"")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<wchar_t>(std::wstring(L"Test")), bad_lexical_cast);
*/
