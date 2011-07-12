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

#include <boost/coerce/detail/precision.hpp>
#include <boost/coerce/reserve.hpp>
#include <boost/coerce/sequence.hpp>
#include <boost/coerce/tag.hpp>

#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/char.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/karma/operator/optional.hpp>
#include <boost/spirit/include/version.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace coerce { namespace detail {

    template <typename Source, typename Tag>
    struct create_generator {
        typedef typename Tag::BOOST_NESTED_TEMPLATE generator<Source>::type type;

        static inline type const
        call() {
            return Tag::BOOST_NESTED_TEMPLATE generator<Source>::call();
        }
    };

    template <typename Source>
    struct create_generator<Source, tag::none>
        : spirit::traits::create_generator<Source> { };

    template <typename Source>
    struct real_policies
        : spirit::karma::real_policies<Source> {
        static inline unsigned
        precision(Source const &) {
            return detail::precision<Source>::value;
        }
    };

    template <typename Source>
    struct create_generator_floating_point {
        typedef spirit::karma::real_generator<
            Source,
            real_policies<typename remove_const<Source>::type>
        > type;

        static inline type const
        call() {
            return type();
        }
    }; 

    template <>
    struct create_generator<float, tag::none>
        : create_generator_floating_point<float> { };

    template <>
    struct create_generator<double, tag::none>
        : create_generator_floating_point<double> { };

    template <>
    struct create_generator<long double, tag::none>
        : create_generator_floating_point<long double> { };

    struct karma {
        template <typename Target, typename Source, typename Tag>
        static inline bool
        call(Target & target, Source const & source) {
            detail::call_reserve(
                target, traits::reserve_size<Source>::call(source));

            bool result = spirit::karma::generate(
                traits::sequence<Target>::back_inserter(target),
                create_generator<Source, Tag>::call(),
                source);

            return result; 
        }
    };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_KARMA_HPP
