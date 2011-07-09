//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE floating_point

#include <boost/coerce.hpp>
#include <boost/limits.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/unit_test.hpp>

struct source_test {
    template <typename T>
    void
    operator()(T) {
        using namespace boost;
        BOOST_CHECK_EQUAL(coerce::as<std::string>(static_cast<T>(0)), "0.0");

        BOOST_CHECK_EQUAL(coerce::as<std::string>(static_cast<T>(23)), "23.0");
        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(static_cast<T>(-23)), "-23.0");

        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(static_cast<T>(1.01828183L)), "1.01828183");

        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(static_cast<T>(1.0e23L)), "1.0e23");
        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(static_cast<T>(1.0e-23L)), "1.0e-23");

        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(std::numeric_limits<T>::quiet_NaN()),
            "nan");
        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(-std::numeric_limits<T>::quiet_NaN()),
            "-nan");

        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(std::numeric_limits<T>::infinity()), "inf");
        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(-std::numeric_limits<T>::infinity()),
            "-inf");
    }
};

BOOST_AUTO_TEST_CASE(source) {
    source_test test;

    typedef boost::mpl::vector<
        float
      , double
      , long double
    > integral_types;

    boost::mpl::for_each<integral_types>(test);
}

struct target_test {
    template <typename T>
    void
    operator()(T) {
        using namespace boost;

        BOOST_CHECK_EQUAL(coerce::as<T>(".0"), 0);
        BOOST_CHECK_EQUAL(coerce::as<T>("0."), 0);
        BOOST_CHECK_EQUAL(coerce::as<T>("0.0"), 0);

        BOOST_CHECK_EQUAL(coerce::as<T>("23.0"), 23);
        BOOST_CHECK_EQUAL(coerce::as<T>("+23.0"), 23);
        BOOST_CHECK_EQUAL(coerce::as<T>("-23.0"), -23);

        BOOST_CHECK_CLOSE_FRACTION(
            coerce::as<T>("1.01828183"),
            static_cast<T>(1.01828183L),
            std::numeric_limits<T>::epsilon());

        BOOST_CHECK_CLOSE_FRACTION(
            coerce::as<T>("1.0e23"),
            static_cast<T>(1.0e23L),
            std::numeric_limits<T>::epsilon());
        BOOST_CHECK_CLOSE_FRACTION(
            coerce::as<T>("1.0E23"),
            static_cast<T>(1.0e23L),
            std::numeric_limits<T>::epsilon());
        BOOST_CHECK_CLOSE_FRACTION(
            coerce::as<T>("1.0e+23"),
            static_cast<T>(1.0e23L),
            std::numeric_limits<T>::epsilon());
        BOOST_CHECK_CLOSE_FRACTION(
            coerce::as<T>("1.0e-23"),
            static_cast<T>(1.0e-23L),
            std::numeric_limits<T>::epsilon());

        BOOST_CHECK_EQUAL(math::fpclassify(coerce::as<T>("NaN")), FP_NAN);
        BOOST_CHECK_EQUAL(math::fpclassify(coerce::as<T>("-NaN")), FP_NAN);

        BOOST_CHECK_EQUAL(math::fpclassify(coerce::as<T>("Inf")), FP_INFINITE);
        BOOST_CHECK_EQUAL(
            math::fpclassify(coerce::as<T>("Infinity")), FP_INFINITE);
        BOOST_CHECK_EQUAL(
            math::fpclassify(coerce::as<T>("-Inf")), FP_INFINITE);
    }
};

BOOST_AUTO_TEST_CASE(target) {
    target_test test;

    typedef boost::mpl::vector<
        float
      , double
      , long double
    > integral_types;

    boost::mpl::for_each<integral_types>(test);
}
