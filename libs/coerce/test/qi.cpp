//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE qi

#include <boost/coerce.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(qi) {
    using namespace boost;
    
    char char_extent[1] = {'1'};
    BOOST_CHECK_EQUAL(coerce::as<int>(char_extent), 1);
    wchar_t wchar_t_extent[1] = {'1'};
    BOOST_CHECK_EQUAL(coerce::as<int>(wchar_t_extent), 1);

    char const char_const_extent[1] = {'1'};
    BOOST_CHECK_EQUAL(coerce::as<int>(char_const_extent), 1);
    wchar_t const wchar_t_const_extent[1] = {'1'};
    BOOST_CHECK_EQUAL(coerce::as<int>(wchar_t_const_extent), 1);

    BOOST_CHECK_EQUAL(coerce::as<int>("1"), 1);
    BOOST_CHECK_EQUAL(coerce::as<int>(L"1"), 1);

    char * char_pointer = const_cast<char *>("1");
    BOOST_CHECK_EQUAL(coerce::as<int>(char_pointer), 1);
    wchar_t * wchar_t_pointer = const_cast<wchar_t *>(L"1");
    BOOST_CHECK_EQUAL(coerce::as<int>(wchar_t_pointer), 1);

    char const * char_const_pointer = "1";
    BOOST_CHECK_EQUAL(coerce::as<int>(char_const_pointer), 1);
    wchar_t const * wchar_t_const_pointer = L"1";
    BOOST_CHECK_EQUAL(coerce::as<int>(wchar_t_const_pointer), 1);

    char * const char_pointer_const = const_cast<char * const>("1");
    BOOST_CHECK_EQUAL(coerce::as<int>(char_pointer_const), 1);
    wchar_t * const wchar_t_pointer_const = const_cast<wchar_t * const>(L"1");
    BOOST_CHECK_EQUAL(coerce::as<int>(wchar_t_pointer_const), 1);

    char const * const char_const_pointer_const = "1";
    BOOST_CHECK_EQUAL(coerce::as<int>(char_const_pointer_const), 1);
    wchar_t const * const wchar_t_const_pointer_const = L"1";
    BOOST_CHECK_EQUAL(coerce::as<int>(wchar_t_const_pointer_const), 1);

    std::string string("1");
    BOOST_CHECK_EQUAL(coerce::as<int>(string), 1);
    std::wstring wide_string(L"1");
    BOOST_CHECK_EQUAL(coerce::as<int>(wide_string), 1);

    BOOST_CHECK_EQUAL(coerce::as<int>(std::string("1")), 1);
    BOOST_CHECK_EQUAL(coerce::as<int>(std::wstring(L"1")), 1);
}
