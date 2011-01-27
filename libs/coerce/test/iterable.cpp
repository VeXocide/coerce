//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE iterable

#include <boost/coerce.hpp>
#include <boost/test/unit_test.hpp>

#include <string>

BOOST_TEST_DONT_PRINT_LOG_VALUE(std::string::const_iterator)

BOOST_AUTO_TEST_CASE(iterable) {
    using boost::coerce::traits::iterable;

    char const * test_char_const_pointer = "test";
    iterable<char const *> test_iterable_char_const_pointer(
        test_char_const_pointer);
    BOOST_CHECK_EQUAL(
        test_iterable_char_const_pointer.begin(),
        &test_char_const_pointer[0]);
    BOOST_CHECK_EQUAL(
        test_iterable_char_const_pointer.end(),
        &test_char_const_pointer[0] + 4);
    BOOST_CHECK_EQUAL(test_iterable_char_const_pointer.size(), 4u);

    wchar_t const * test_wchar_t_const_pointer = L"test";
    iterable<wchar_t const *> test_iterable_wchar_t_const_pointer(
        test_wchar_t_const_pointer);
    BOOST_CHECK_EQUAL(
        test_iterable_wchar_t_const_pointer.begin(),
        &test_wchar_t_const_pointer[0]);
    BOOST_CHECK_EQUAL(
        test_iterable_wchar_t_const_pointer.end(),
        &test_wchar_t_const_pointer[0] + 4);
    BOOST_CHECK_EQUAL(test_iterable_wchar_t_const_pointer.size(), 4u);

    char const test_char_const_extend[5] = "test";
    iterable<char const *> test_iterable_char_const_extend(
        test_char_const_extend);
    BOOST_CHECK_EQUAL(
        test_iterable_char_const_extend.begin(), &test_char_const_extend[0]);
    BOOST_CHECK_EQUAL(
        test_iterable_char_const_extend.end(), &test_char_const_extend[0] + 4);
    BOOST_CHECK_EQUAL(test_iterable_char_const_extend.size(), 4u);

    std::string const test_string_const("test");
    iterable<std::string const> test_iterable_string_const(test_string_const);
    BOOST_CHECK_EQUAL(
        test_iterable_string_const.begin(), test_string_const.begin());
    BOOST_CHECK_EQUAL(
        test_iterable_string_const.end(), test_string_const.end());
    BOOST_CHECK_EQUAL(
        test_iterable_string_const.size(), 4u);
}

BOOST_AUTO_TEST_CASE(is_iterable) {
    using boost::coerce::traits::is_iterable;

    BOOST_CHECK(!is_iterable<bool>::type());

    BOOST_CHECK(is_iterable<char *>::type());
    BOOST_CHECK(is_iterable<char const *>::type());
    BOOST_CHECK(is_iterable<char * const>::type());
    BOOST_CHECK(is_iterable<char const * const>::type());
    BOOST_CHECK(is_iterable<char [1]>::type());
    BOOST_CHECK(is_iterable<char const [1]>::type());
    BOOST_CHECK(is_iterable<char (&)[1]>::type());
    BOOST_CHECK(is_iterable<char const (&)[1]>::type());

    BOOST_CHECK(is_iterable<wchar_t *>::type());
    BOOST_CHECK(is_iterable<wchar_t const *>::type());
    BOOST_CHECK(is_iterable<wchar_t * const>::type());
    BOOST_CHECK(is_iterable<wchar_t const * const>::type());
    BOOST_CHECK(is_iterable<wchar_t [1]>::type());
    BOOST_CHECK(is_iterable<wchar_t const [1]>::type());
    BOOST_CHECK(is_iterable<wchar_t (&)[1]>::type());
    BOOST_CHECK(is_iterable<wchar_t const (&)[1]>::type());

    BOOST_CHECK(is_iterable<std::string>::type());
    BOOST_CHECK(is_iterable<std::string const>::type());
    BOOST_CHECK(is_iterable<std::string &>::type());
    BOOST_CHECK(is_iterable<std::string const &>::type());
    
    BOOST_CHECK(is_iterable<std::wstring>::type());
    BOOST_CHECK(is_iterable<std::wstring const>::type());
    BOOST_CHECK(is_iterable<std::wstring &>::type());
    BOOST_CHECK(is_iterable<std::wstring const &>::type());
}
