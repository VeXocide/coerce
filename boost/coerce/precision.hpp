//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_PRECISION_HPP
#define BOOST_COERCE_PRECISION_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/limits.hpp>

namespace boost { namespace coerce { namespace traits {

    template <typename T>
    struct precision {
        typedef std::numeric_limits<T> limits;

        BOOST_STATIC_CONSTANT(bool, is_specialized =
            limits::is_specialized && !limits::is_exact);

        BOOST_STATIC_CONSTANT(bool, is_specialized_binary =
            is_specialized && limits::radix == 2 && limits::digits > 0);

        BOOST_STATIC_CONSTANT(unsigned, precision_binary =
            2UL + limits::digits * 30103UL / 100000UL);

        BOOST_STATIC_CONSTANT(bool, is_specialized_decimal =
            is_specialized && limits::radix == 10 && limits::digits10 > 0);

        BOOST_STATIC_CONSTANT(unsigned, precision_decimal =
            limits::digits10 + 1U);

        BOOST_STATIC_CONSTANT(unsigned, value =
            is_specialized_binary ? precision_binary
                : is_specialized_decimal ? precision_decimal : 6);
    };

} } }  // namespace boost::coerce::traits

#endif  // BOOST_COERCE_PRECISION_HPP
