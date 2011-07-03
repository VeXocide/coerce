//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE karma

#include <boost/coerce.hpp>
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>

BOOST_TEST_DONT_PRINT_LOG_VALUE(std::wstring);
BOOST_TEST_DONT_PRINT_LOG_VALUE(std::vector<char>);
BOOST_TEST_DONT_PRINT_LOG_VALUE(std::vector<wchar_t>);

BOOST_AUTO_TEST_CASE(qi) {
    using namespace boost;

    BOOST_CHECK_EQUAL(coerce::as<std::string>(1), std::string("1"));
    BOOST_CHECK_EQUAL(coerce::as<std::wstring>(1), std::wstring(L"1"));

    std::vector<char> vector_char(1, '1');
    BOOST_CHECK_EQUAL(coerce::as<std::vector<char> >(1), vector_char);
    std::vector<wchar_t> vector_wchar_t(1, L'1');
    BOOST_CHECK_EQUAL(coerce::as<std::vector<wchar_t> >(1), vector_wchar_t);
}
