//           Copyright Jeroen Habraken 2010 - 2012.
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
#include <boost/coerce/string.hpp>
#include <boost/coerce/tag.hpp>

#include <boost/spirit/home/karma/char.hpp>
#include <boost/spirit/home/karma/generate.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/karma/operator/optional.hpp>

namespace boost { namespace coerce { namespace detail {

    struct karma {
        template <typename Target, typename Source, typename Tag>
        static inline bool
        call(Target & target, Source const & source, Tag const & tag) {
            typedef traits::string_traits<Target> string_traits;
            
            detail::call_reserve(
                target, traits::reserve_size<Source, Tag>::call(source, tag));

            typename Tag::template generator<
                typename string_traits::back_insert_iterator, Target, Source
            > generator(tag);

            return spirit::karma::generate(
                string_traits::back_inserter(target), generator, source);
        }
    };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_KARMA_HPP
