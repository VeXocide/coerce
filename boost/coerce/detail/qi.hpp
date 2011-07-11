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
#include <boost/coerce/string.hpp>
#include <boost/coerce/tag.hpp>

#include <boost/config.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/qi/operator/optional.hpp>

namespace boost { namespace coerce { namespace detail {

    template <typename Target, typename Tag>
    struct create_parser {
        typedef typename Tag::BOOST_NESTED_TEMPLATE parser<Target>::type type;

        static inline type const
        call() {
            return Tag::BOOST_NESTED_TEMPLATE parser<Target>::call();
        }
    };

    template <typename Target>
    struct create_parser<Target, tag::none>
        : spirit::traits::create_parser<Target> { };

    struct qi {
        template <typename Target, typename Source, typename Tag>
        static inline bool
        call(Target & target, Source const & source) {
            typedef traits::string<Source> string_traits;

            typename string_traits::size_type
                length = string_traits::length(source);
            detail::call_reserve(target, length);

            typename string_traits::const_iterator
                begin = string_traits::begin(source), iterator = begin;

            bool result = spirit::qi::parse(
                iterator, string_traits::end(source),
                create_parser<Target, Tag>::call(),
                target);

            if (static_cast<typename string_traits::size_type>(iterator - begin) != length) {
                return false;
            }

            return result;
        }
    };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_QI_HPP
