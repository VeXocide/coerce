//           Copyright Jeroen Habraken 2010 - 2012.
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
#include <boost/coerce/string.hpp>
#include <boost/coerce/tag.hpp>

#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/qi/operator/optional.hpp>
#include <boost/spirit/home/qi/parse.hpp>

namespace boost { namespace coerce { namespace detail {

    struct qi {
        template <typename Target, typename Source, typename Tag>
        static inline bool
        call(Target & target, Source const & source, Tag const & tag) {
            typedef traits::string_traits<Source> string_traits;

            typename string_traits::const_iterator
                begin = string_traits::begin(source), iterator = begin;

            typename string_traits::const_iterator
                end = string_traits::end(source);

            typename Tag::template parser<
                typename string_traits::const_iterator, Target, Source
            > parser(tag);

            bool result = spirit::qi::parse(
                iterator, end, parser, target);

            return result && (iterator == end);
        }
    };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_QI_HPP
