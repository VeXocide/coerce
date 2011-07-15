//           Copyright Jeroen Habraken 2010 - 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE reserve

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/coerce.hpp>
#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>

BOOST_AUTO_TEST_CASE(reserve_size) {
    using boost::coerce::traits::reserve_size;

    BOOST_CHECK_GT(reserve_size<char>::call('\0'), 0u);
    BOOST_CHECK_GT(reserve_size<wchar_t>::call(L'\0'), 0u);
    short const test_short = 0;
    BOOST_CHECK_GT(reserve_size<short>::call(test_short), 0u);
    BOOST_CHECK_GT(reserve_size<int>::call(0), 0u);
    BOOST_CHECK_GT(reserve_size<long>::call(0l), 0u);
    unsigned short const test_unsigned_short = 0u;
    BOOST_CHECK_GT(reserve_size<unsigned short>::call(
        test_unsigned_short), 0u);
    BOOST_CHECK_GT(reserve_size<unsigned int>::call(0u), 0u);
    BOOST_CHECK_GT(reserve_size<unsigned long>::call(0ul), 0u);
    BOOST_CHECK_GT(reserve_size<float>::call(0.0f), 0u);
    BOOST_CHECK_GT(reserve_size<double>::call(0.0), 0u);
    BOOST_CHECK_GT(reserve_size<long double>::call(0.0l), 0u);
    BOOST_CHECK_GT(reserve_size<bool>::call(false), 0u);

    BOOST_CHECK_GT(reserve_size<boost::optional<char> >::call(
        boost::optional<char>('\0')), 0u);
}

BOOST_AUTO_TEST_CASE(has_reserve) {
    using boost::coerce::detail::has_reserve;

    BOOST_CHECK(!has_reserve<void>::type());

    BOOST_CHECK(has_reserve<std::string>::type());
    BOOST_CHECK(has_reserve<std::wstring>::type());

    BOOST_CHECK(has_reserve<std::vector<char> >::type());
    BOOST_CHECK(has_reserve<std::vector<wchar_t> >::type());
}

// TODO, call_reserve
