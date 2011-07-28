//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE tag

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/coerce.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/test/unit_test.hpp>

#include <string>

struct source_test {
    template <typename T>
    void
    operator()(T) {
        using namespace boost;

        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(
                static_cast<T>(23), coerce::tag::base<10>()),
            "23");

        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(static_cast<T>(23), coerce::tag::bin()),
            "10111");

        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(static_cast<T>(23), coerce::tag::oct()),
            "27");

        BOOST_CHECK_EQUAL(
            coerce::as<std::string>(static_cast<T>(23), coerce::tag::hex()),
            "17");
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

        BOOST_CHECK_EQUAL(
            coerce::as<T>("23", coerce::tag::base<10>()), static_cast<T>(23));

        BOOST_CHECK_EQUAL(
            coerce::as<T>("10111", coerce::tag::bin()), static_cast<T>(23));

        BOOST_CHECK_EQUAL(
            coerce::as<T>("27", coerce::tag::oct()), static_cast<T>(23));

        BOOST_CHECK_EQUAL(
            coerce::as<T>("17", coerce::tag::hex()), static_cast<T>(23));
        BOOST_CHECK_EQUAL(
            coerce::as<T>("0x17", coerce::tag::hex()), static_cast<T>(23));

        BOOST_CHECK_THROW(
            coerce::as<T>("23X", coerce::tag::base<10>()), coerce::bad_cast);
        BOOST_CHECK_THROW(
            coerce::as<T>("XXX", coerce::tag::base<10>()), coerce::bad_cast);
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
    > integral_types;

    boost::mpl::for_each<integral_types>(test);
}
