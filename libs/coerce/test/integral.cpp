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
        short
      , unsigned short
      , int
      , unsigned int
      , long
      , unsigned long
#ifdef BOOST_HAS_LONG_LONG
      , boost::long_long_type
      , boost::ulong_long_type
#endif
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
            BOOST_CHECK_EQUAL(coerce::as<T>("+23"), static_cast<T>(23));
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

        if (std::numeric_limits<T>::is_integer) {
            BOOST_CHECK_THROW(
                coerce::as<T>("18446744073709551616"), coerce::bad_cast);
            BOOST_CHECK_THROW(
                coerce::as<T>("-9223372036854775809"), coerce::bad_cast);
        }

        BOOST_CHECK_THROW(coerce::as<T>("23X"), coerce::bad_cast);
        BOOST_CHECK_THROW(coerce::as<T>("XXX"), coerce::bad_cast);
    }
};

BOOST_AUTO_TEST_CASE(target) {
    target_test test;

    typedef boost::mpl::vector<
        short
      , unsigned short
      , int
      , unsigned int
      , long
      , unsigned long
#ifdef BOOST_HAS_LONG_LONG
      , boost::long_long_type
      , boost::ulong_long_type
#endif
      , float
      , double
      , long double
    > integral_types;

    boost::mpl::for_each<integral_types>(test);
}
