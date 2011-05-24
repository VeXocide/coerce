//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE integral

#define CHECK_EQUAL(type, source, target) \
    BOOST_CHECK_EQUAL(boost::coerce::as<type>(source), target)

#define CHECK_THROW(type, source) \
    BOOST_CHECK_THROW(boost::coerce::as<type>(source), boost::coerce::bad_cast)

#include <boost/coerce.hpp>
#include <boost/limits.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/test/unit_test.hpp>

struct source_test {
    template <typename T>
    void
    operator()(T) {
        CHECK_EQUAL(std::string, static_cast<T>(0), "0");

        CHECK_EQUAL(std::string, static_cast<T>(23), "23");
        if (std::numeric_limits<T>::is_signed) {
            CHECK_EQUAL(std::string, static_cast<T>(-23), "-23");
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
        CHECK_EQUAL(T, "0", static_cast<T>(0));
        if (std::numeric_limits<T>::is_signed) {
            CHECK_EQUAL(T, "+0", static_cast<T>(0));
            CHECK_EQUAL(T, "-0", static_cast<T>(0));
        }

        CHECK_THROW(T, "");
        CHECK_THROW(T, "+");
        CHECK_THROW(T, "-");

        CHECK_EQUAL(T, "23", static_cast<T>(23));
        if (std::numeric_limits<T>::is_signed) {
            CHECK_EQUAL(T, "+23", static_cast<T>(23));
            CHECK_EQUAL(T, "-23", static_cast<T>(-23));
        }

        CHECK_EQUAL(T, "00023", static_cast<T>(23));
        if (std::numeric_limits<T>::is_signed) {
            CHECK_EQUAL(T, "+00023", static_cast<T>(23));
            CHECK_EQUAL(T, "-00023", static_cast<T>(-23));
        }

        CHECK_THROW(T, "   23");
        CHECK_THROW(T, "23   ");
        CHECK_THROW(T, "   23   ");

        CHECK_THROW(T, "18446744073709551616");
        CHECK_THROW(T, "-9223372036854775809");

        CHECK_THROW(T, "23X");
        CHECK_EQUAL(T, "23\0X", static_cast<T>(23));

        CHECK_THROW(T, "XXX");
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
