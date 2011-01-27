//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_COERCE_UNSPECIALIZED_RESERVE 0
#define BOOST_TEST_MODULE reserve

#include <boost/coerce.hpp>
#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>

BOOST_AUTO_TEST_CASE(reserve_size) {
    using namespace boost::coerce::tag;

    using boost::coerce::traits::reserve_size;
    using boost::spirit::unused_type;

    BOOST_CHECK_GT((reserve_size<char, unused_type>::call('\0')), 0u);
    BOOST_CHECK_GT((reserve_size<wchar_t, unused_type>::call(L'\0')), 0u);
    short const test_short = 0;
    BOOST_CHECK_GT((reserve_size<short, unused_type>::call(test_short)), 0u);
    BOOST_CHECK_GT((reserve_size<int, unused_type>::call(0)), 0u);
    BOOST_CHECK_GT((reserve_size<long, unused_type>::call(0l)), 0u);
    unsigned short const test_unsigned_short = 0u;
    BOOST_CHECK_GT((reserve_size<unsigned short, unused_type>::call(
        test_unsigned_short)), 0u);
    BOOST_CHECK_GT((reserve_size<unsigned int, unused_type>::call(0u)), 0u);
    BOOST_CHECK_GT((reserve_size<unsigned long, unused_type>::call(0ul)), 0u);
    BOOST_CHECK_GT((reserve_size<float, unused_type>::call(0.0f)), 0u);
    BOOST_CHECK_GT((reserve_size<double, unused_type>::call(0.0)), 0u);
    BOOST_CHECK_GT((reserve_size<long double, unused_type>::call(0.0l)), 0u);
    BOOST_CHECK_GT((reserve_size<bool, unused_type>::call(false)), 0u);

    BOOST_CHECK_GT((reserve_size<char const, unused_type>::call('\0')), 0u);
    BOOST_CHECK_GT((reserve_size<char &, unused_type>::call('\0')), 0u);
    BOOST_CHECK_GT((reserve_size<char const &, unused_type>::call('\0')), 0u);

    BOOST_CHECK_GT((reserve_size<boost::optional<char>, unused_type>::call(
        boost::optional<char>('\0'))), 0u);

    BOOST_CHECK_GT((reserve_size<int, bin_type>::call(0)), 0u);
    BOOST_CHECK_GT((reserve_size<int, oct_type>::call(0)), 0u);
    BOOST_CHECK_GT((reserve_size<int, hex_type>::call(0)), 0u);
}

BOOST_AUTO_TEST_CASE(has_reserve) {
    using boost::coerce::detail::has_reserve;

    BOOST_CHECK(!has_reserve<bool>::type());

    BOOST_CHECK(has_reserve<std::string>::type());
    BOOST_CHECK(has_reserve<std::wstring>::type());

    BOOST_CHECK(has_reserve<std::vector<char> >::type());
    BOOST_CHECK(has_reserve<std::vector<wchar_t> >::type());
}

BOOST_AUTO_TEST_CASE(call_reserve) {
    using boost::coerce::detail::call_reserve;

    call_reserve('\0', 1u);

    std::string test_string;
    call_reserve(test_string, 1u);
    BOOST_CHECK_EQUAL(test_string.capacity(), 1u);
}
