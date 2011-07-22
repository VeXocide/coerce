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

#include <boost/coerce/precision.hpp>

#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/numeric/int.hpp>
#include <boost/spirit/home/qi/numeric/uint.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace coerce { namespace tag {

    struct none {
        template <typename Target, typename Source>
        struct parser
            : spirit::traits::create_parser<Target>::type {
            parser(tag::none const &) { }
        };

        template <typename Target, typename Source>
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
                return traits::precision<Source>::value;
            }
        };

        template <typename Target, typename Source>
        struct generator_floating_point
            : spirit::karma::real_generator<Source, real_policies<Source> > { };

        template <typename Target>
        struct generator<Target, float>
            : generator_floating_point<Target, float> {
            generator(tag::none const &) { }
        };

        template <typename Target>
        struct generator<Target, double>
            : generator_floating_point<Target, double> {
            generator(tag::none const &) { }
        };

        template <typename Target>
        struct generator<Target, long double>
            : generator_floating_point<Target, long double> {
            generator(tag::none const &) { }
        };
    };

    template <unsigned Radix>
    struct base {
        template <typename Target, typename Source, bool U = is_signed<Target>::value>
        struct parser;

        template <typename Target, typename Source>
        struct parser<Target, Source, true>
            : spirit::qi::int_parser<Target, Radix> {
            parser(tag::base<Radix> const &) { }
        };

        template <typename Target, typename Source>
        struct parser<Target, Source, false>
            : spirit::qi::uint_parser<Target, Radix> {
            parser(tag::base<Radix> const &) { }
        };

        template <typename Target, typename Source, bool U = is_signed<Target>::value>
        struct generator;

        template <typename Target, typename Source>
        struct generator<Target, Source, true>
            : spirit::karma::int_generator<Source, Radix> {
            generator(tag::base<Radix> const &) { }
        };

        template <typename Target, typename Source>
        struct generator<Target, Source, false>
            : spirit::karma::uint_generator<Source, Radix> {
            generator(tag::base<Radix> const &) { }
        };
    };

    struct bin
        : base<2> { };

    struct oct
        : base<8> { };

    struct hex
        : base<16> { };

} } }  // namespace boost::coerce::tag

#endif  // BOOST_COERCE_TAG_HPP
