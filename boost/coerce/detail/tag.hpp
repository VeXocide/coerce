//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_DETAIL_TAG_HPP
#define BOOST_COERCE_DETAIL_TAG_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/mpl/if.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace coerce { namespace detail {

    template <typename T, unsigned Radix>
    struct integer_parser
        : mpl::if_<
            is_signed<T>,
            spirit::qi::int_parser<T, Radix>,
            spirit::qi::uint_parser<T, Radix>
        > {
            BOOST_STATIC_ASSERT(is_integral<T>::value);
        };

    template <typename T, unsigned Radix>
    struct integer_generator 
        : mpl::if_<
            is_signed<T>,
            spirit::karma::int_generator<T, Radix>,
            spirit::karma::uint_generator<T, Radix>
        > {
            BOOST_STATIC_ASSERT(is_integral<T>::value);
        };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_TAG_HPP
