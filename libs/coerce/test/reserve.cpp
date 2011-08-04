//           Copyright Jeroen Habraken 2010 - 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE reserve

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/coerce.hpp>
#include <boost/coerce/tag/base.hpp>
#include <boost/optional.hpp>
#include <boost/test/unit_test.hpp>

#include <string>
#include <vector>

BOOST_AUTO_TEST_CASE(reserve_size) {
    using namespace boost;
    
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<char, coerce::tag::none>::call(
            '\0', coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<wchar_t, coerce::tag::none>::call(
            L'\0', coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<short, coerce::tag::none>::call(
            static_cast<short const>(0), coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<int, coerce::tag::none>::call(
            0, coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<long, coerce::tag::none>::call(
            0l, coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<unsigned short, coerce::tag::none>::call(
            static_cast<unsigned short const>(0), coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<unsigned int, coerce::tag::none>::call(
            0u, coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<unsigned long, coerce::tag::none>::call(
            0ul, coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<float, coerce::tag::none>::call(
            0.0f, coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<double, coerce::tag::none>::call(
            0.0, coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<long double, coerce::tag::none>::call(
            0.0l, coerce::tag::none())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<bool, coerce::tag::none>::call(
            false, coerce::tag::none())), 0u);

    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<
            boost::optional<char>, coerce::tag::none
        >::call(
            boost::optional<char>('\0'), coerce::tag::none())), 0u);

    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<unsigned, coerce::tag::base<10> >::call(
            0u, coerce::tag::base<10>())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<unsigned, coerce::tag::bin>::call(
            0u, coerce::tag::bin())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<unsigned, coerce::tag::oct>::call(
            0u, coerce::tag::oct())), 0u);
    BOOST_CHECK_GT(
        (coerce::traits::reserve_size<unsigned, coerce::tag::hex>::call(
            0u, coerce::tag::hex())), 0u);
}

BOOST_AUTO_TEST_CASE(has_reserve) {
    using namespace boost;

    BOOST_CHECK(!coerce::detail::has_reserve<void>::type());

    BOOST_CHECK(coerce::detail::has_reserve<std::string>::type());
    BOOST_CHECK(coerce::detail::has_reserve<std::wstring>::type());

    BOOST_CHECK(coerce::detail::has_reserve<std::vector<char> >::type());
    BOOST_CHECK(coerce::detail::has_reserve<std::vector<wchar_t> >::type());
}

// TODO, call_reserve
