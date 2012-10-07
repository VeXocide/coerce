//           Copyright Jeroen Habraken 2011 - 2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE qi

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/coerce.hpp>
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>

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
    BOOST_CHECK_EQUAL(coerce::as<int>(boost::make_iterator_range(string)), 1);
    std::wstring wide_string(L"1");
    BOOST_CHECK_EQUAL(coerce::as<int>(wide_string), 1);
    BOOST_CHECK_EQUAL(coerce::as<int>(
        boost::make_iterator_range(wide_string)), 1);

    std::string const string_const("1");
    BOOST_CHECK_EQUAL(coerce::as<int>(string_const), 1);
    BOOST_CHECK_EQUAL(coerce::as<int>(
        boost::make_iterator_range(string_const)), 1);
    std::wstring const wide_string_const(L"1");
    BOOST_CHECK_EQUAL(coerce::as<int>(wide_string_const), 1);
    BOOST_CHECK_EQUAL(coerce::as<int>(
        boost::make_iterator_range(wide_string_const)), 1);

    BOOST_CHECK_EQUAL(coerce::as<int>(std::string("1")), 1);
    BOOST_CHECK_EQUAL(coerce::as<int>(std::wstring(L"1")), 1);

    std::vector<char> vector_char(1, '1');
    BOOST_CHECK_EQUAL(coerce::as<int>(vector_char), 1);
    std::vector<wchar_t> vector_wchar_t(1, L'1');
    BOOST_CHECK_EQUAL(coerce::as<int>(vector_wchar_t), 1);
}

BOOST_AUTO_TEST_CASE(throw_) {
    using namespace boost;

    BOOST_CHECK_THROW(coerce::as<int>("1\0"), coerce::bad_cast);
    BOOST_CHECK_THROW(coerce::as<int>("1\0" "1"), coerce::bad_cast);
}
