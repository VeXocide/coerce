//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE integral

#include <boost/coerce.hpp>
#include <boost/limits.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/test/unit_test.hpp>

struct source_test {
    template <typename T>
    void
    operator()(T) {
        using namespace boost;

        BOOST_CHECK_EQUAL(coerce::as<std::string>(static_cast<T>(0)), "0");

        BOOST_CHECK_EQUAL(coerce::as<std::string>(static_cast<T>(23)), "23");
        if (std::numeric_limits<T>::is_signed) {
            BOOST_CHECK_EQUAL(
                coerce::as<std::string>(static_cast<T>(-23)), "-23");
        }
    }
};

BOOST_AUTO_TEST_CASE(source) {
    source_test test;

    typedef boost::mpl::vector<
#ifdef BOOST_HAS_LONG_LONG
        boost::long_long_type,
        boost::ulong_long_type,
#endif
        short,
        unsigned short,
        int,
        unsigned int,
        long,
        unsigned long
    > integral_types;

    boost::mpl::for_each<integral_types>(test);
}

struct target_test {
    template <typename T>
    void
    operator()(T) {
        using namespace boost;

        BOOST_CHECK_EQUAL(coerce::as<T>("0"), static_cast<T>(0));
        if (std::numeric_limits<T>::is_signed) {
            BOOST_CHECK_EQUAL(coerce::as<T>("+0"), static_cast<T>(0));
            BOOST_CHECK_EQUAL(coerce::as<T>("-0"), static_cast<T>(0));
        }

        BOOST_CHECK_THROW(coerce::as<T>(""), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("+"), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("-"), coerce::bad_cast);

        BOOST_CHECK_EQUAL(coerce::as<T>("23"), static_cast<T>(23));
        if (std::numeric_limits<T>::is_signed) {
            BOOST_CHECK_EQUAL(coerce::as<T>("23"), static_cast<T>(23));
            BOOST_CHECK_EQUAL(coerce::as<T>("-23"), static_cast<T>(-23));
        }

        BOOST_CHECK_THROW(coerce::as<T>("++23"), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("+-23"), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("-+23"), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("--23"), coerce::bad_cast);

        BOOST_CHECK_EQUAL(coerce::as<T>("00023"), static_cast<T>(23));
        if (std::numeric_limits<T>::is_signed) {
            BOOST_CHECK_EQUAL(coerce::as<T>("+00023"), static_cast<T>(23));
            BOOST_CHECK_EQUAL(coerce::as<T>("-00023"), static_cast<T>(-23));
        }

        BOOST_CHECK_THROW(coerce::as<T>("   23"), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("23   "), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("   23   "), coerce::bad_cast);

        BOOST_CHECK_THROW(coerce::as<T>("23.0"), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("+23.0"), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("-23.0"), coerce::bad_cast);

        BOOST_CHECK_THROW(
            coerce::as<T>("18446744073709551616"), coerce::bad_cast);
        BOOST_CHECK_THROW(
            coerce::as<T>("-9223372036854775809"), coerce::bad_cast);

        BOOST_CHECK_THROW(coerce::as<T>("23X"), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("XXX"), coerce::bad_cast);
    }
};

BOOST_AUTO_TEST_CASE(target) {
    target_test test;

    typedef boost::mpl::vector<
#ifdef BOOST_HAS_LONG_LONG
        boost::long_long_type,
        boost::ulong_long_type,
#endif
        short,
        unsigned short,
        int,
        unsigned int,
        long,
        unsigned long
    > integral_types;

    boost::mpl::for_each<integral_types>(test);
}

/*  lexical_cast

    BOOST_CHECK_EQUAL(1, lexical_cast<int>('1'));
    BOOST_CHECK_EQUAL(0, lexical_cast<int>('0'));
    BOOST_CHECK_THROW(lexical_cast<int>('A'), bad_lexical_cast);
    BOOST_CHECK_EQUAL(1, lexical_cast<int>(1));
    BOOST_CHECK_EQUAL(1, lexical_cast<int>(1.0));

    BOOST_CHECK_EQUAL(
        (std::numeric_limits<int>::max)(),
        lexical_cast<int>((std::numeric_limits<int>::max)()));

    BOOST_CHECK_EQUAL(
        (std::numeric_limits<int>::min)(),
        lexical_cast<int>((std::numeric_limits<int>::min)()));

    BOOST_CHECK_THROW(lexical_cast<int>(1.23), bad_lexical_cast);

    BOOST_CHECK_THROW(lexical_cast<int>(1e20), bad_lexical_cast);
    BOOST_CHECK_EQUAL(1, lexical_cast<int>(true));
    BOOST_CHECK_EQUAL(0, lexical_cast<int>(false));
    BOOST_CHECK_EQUAL(123, lexical_cast<int>("123"));
    BOOST_CHECK_THROW(
        lexical_cast<int>(" 123"), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<int>(""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<int>("Test"), bad_lexical_cast);
    BOOST_CHECK_EQUAL(123, lexical_cast<int>("123"));
    BOOST_CHECK_EQUAL(123, lexical_cast<int>(std::string("123")));
    BOOST_CHECK_THROW(
        lexical_cast<int>(std::string(" 123")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<int>(std::string("")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<int>(std::string("Test")), bad_lexical_cast);

    BOOST_CHECK(lexical_cast<T>("-1") == static_cast<T>(-1));
    BOOST_CHECK(lexical_cast<T>("-9") == static_cast<T>(-9));
    BOOST_CHECK(lexical_cast<T>(-1) == static_cast<T>(-1));
    BOOST_CHECK(lexical_cast<T>(-9) == static_cast<T>(-9));

    BOOST_CHECK_THROW(lexical_cast<T>("-1.0"), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<T>("-9.0"), bad_lexical_cast);
    BOOST_CHECK(lexical_cast<T>(-1.0) == static_cast<T>(-1));
    BOOST_CHECK(lexical_cast<T>(-9.0) == static_cast<T>(-9));

    BOOST_CHECK(lexical_cast<T>(static_cast<T>(1)) == static_cast<T>(1));
    BOOST_CHECK(lexical_cast<T>(static_cast<T>(9)) == static_cast<T>(9));
    BOOST_CHECK_THROW(lexical_cast<T>(1.1f), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<T>(1.1), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<T>(1.1L), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<T>(1.0001f), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<T>(1.0001), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<T>(1.0001L), bad_lexical_cast);

    BOOST_CHECK(lexical_cast<T>("+1") == static_cast<T>(1) );
    BOOST_CHECK(lexical_cast<T>("+9") == static_cast<T>(9) );
    BOOST_CHECK(lexical_cast<T>("+10") == static_cast<T>(10) );
    BOOST_CHECK(lexical_cast<T>("+90") == static_cast<T>(90) );
    BOOST_CHECK_THROW(lexical_cast<T>("++1"), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<T>("-+9"), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<T>("--1"), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<T>("+-9"), bad_lexical_cast);
*/
