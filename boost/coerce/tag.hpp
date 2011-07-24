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

#include <boost/config.hpp>
#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/directive/no_case.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/numeric/int.hpp>
#include <boost/spirit/home/qi/numeric/uint.hpp>
#include <boost/spirit/home/qi/operator/optional.hpp>
#include <boost/spirit/home/qi/operator/sequence.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/string/lit.hpp>
#include <boost/spirit/home/support/meta_compiler.hpp>
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
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4348)  // redefinition of default parameter : parameter 2
#endif
        template <typename Target, bool U = is_signed<Target>::value>
        struct parser_base;
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

        template <typename Target>
        struct parser_base<Target, true>
            : spirit::qi::int_parser<Target, Radix> { };

        template <typename Target>
        struct parser_base<Target, false>
            : spirit::qi::uint_parser<Target, Radix> { };

        template <typename Target, typename Source>
        struct parser
            : parser_base<Target> {
            parser(tag::base<Radix> const &) { }
        };

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4348)  // redefinition of default parameter : parameter 2
#endif
        template <typename Source, bool U = is_signed<Source>::value>
        struct generator_base;
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

        template <typename Source>
        struct generator_base<Source, true>
            : spirit::karma::int_generator<Source, Radix> { };

        template <typename Source>
        struct generator_base<Source, false>
            : spirit::karma::uint_generator<Source, Radix> { };
    
        template <typename Target, typename Source>
        struct generator
            : generator_base<Source> {
            generator(tag::base<Radix> const &) { }
        };
    };

    struct bin
        : base<2> { };

    struct oct
        : base<8> { };

    struct hex
        : base<16> {
        template <typename Target, typename Source>
        struct parser
            : spirit::qi::parser<parser<Target, Source> > {
            parser(tag::hex const &) { }

            template <typename Context, typename Iterator>
            struct attribute {
                typedef Target type;
            };
            
            template <typename Iterator, typename Context, typename Skipper>
            inline bool
            parse(
                Iterator & first,
                Iterator const & last,
                Context & context,
                Skipper const & skipper,
                Target & target
            ) const {
                return spirit::compile<spirit::qi::domain>(
                    -spirit::standard::no_case_type()["0x"] >> parser_base<Target>()
                ).parse(first, last, context, skipper, target);
            }
        };
    };

} } }  // namespace boost::coerce::tag

#endif  // BOOST_COERCE_TAG_HPP
