//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_TAG_HPP
#define BOOST_COERCE_TAG_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/coerce/detail/precision.hpp>

#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/numeric/real.hpp>
#include <boost/spirit/home/karma/numeric/real_policies.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace coerce { namespace tag {

    struct none {
        template <typename Iterator, typename Target, typename Source>
        struct parser
            : spirit::traits::create_parser<Target>::type {
            parser(tag::none const &) { }
        };

        template <typename Iterator, typename Target, typename Source>
        struct generator
            : spirit::traits::create_generator<Source>::type {
            generator(tag::none const &) { }
        };

        template <typename Source>
        struct real_policies
            : spirit::karma::real_policies<
                typename remove_const<Source>::type
            > {
            static inline unsigned
            precision(Source const &) {
                return detail::precision<Source>::value;
            }
        };

        template <typename Source>
        struct generator_floating_point
            : spirit::karma::real_generator<Source, real_policies<Source> > { };

        template <typename Iterator, typename Target>
        struct generator<Iterator, Target, float>
            : generator_floating_point<float> {
            generator(tag::none const &) { }
        };

        template <typename Iterator, typename Target>
        struct generator<Iterator, Target, double>
            : generator_floating_point<double> {
            generator(tag::none const &) { }
        };

        template <typename Iterator, typename Target>
        struct generator<Iterator, Target, long double>
            : generator_floating_point<long double> {
            generator(tag::none const &) { }
        };
    };

    template <unsigned Radix>
    struct base;

    struct bin;

    struct oct;
    
    struct hex;

} } }  // namespace boost::coerce::tag

#endif  // BOOST_COERCE_TAG_HPP
