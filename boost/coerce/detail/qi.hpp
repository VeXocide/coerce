//           Copyright Jeroen Habraken 2010 - 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_DETAIL_QI_HPP
#define BOOST_COERCE_DETAIL_QI_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/coerce/reserve.hpp>

#include <boost/range/begin.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/qi/operator/optional.hpp>

namespace boost { namespace coerce { namespace detail {

    struct qi {
        template <typename Target, typename Source>
        static inline bool
        call(Target & target, Source const & source) {
            typename range_difference<Source>::type size =
                boost::size(source);
            detail::call_reserve(target, size);

            typedef typename range_const_iterator<Source>::type iterator_type;
            iterator_type begin = boost::const_begin(source),
                          iterator = begin;
            iterator_type end = boost::const_end(source);

            bool result = spirit::qi::parse(
                iterator, end, target);

            if (!result || !((begin <= iterator && iterator < end && *iterator == 0) || iterator == end))
                return false;

            return true;
        }
    };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_QI_HPP
