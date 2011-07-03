//           Copyright Jeroen Habraken 2010 - 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_DETAIL_KARMA_HPP
#define BOOST_COERCE_DETAIL_KARMA_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/coerce/reserve.hpp>
#include <boost/coerce/sequence.hpp>

#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/char.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/karma/operator/optional.hpp>
#include <boost/spirit/include/version.hpp>

namespace boost { namespace coerce { namespace detail {

    struct karma {
        template <typename Target, typename Source>
        static inline bool
        call(Target & target, Source const & source) {
            detail::call_reserve(
                target, traits::reserve_size<Source>::call(source));

            bool result = spirit::karma::generate(
                traits::sequence<Target>::back_inserter(target),
#if SPIRIT_VERSION <= 0x2030
                spirit::karma::auto_,
#endif
                source);

            return result; 
        }
    };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_KARMA_HPP
