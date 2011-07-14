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

#include <boost/coerce/detail/tag.hpp>

#include <boost/proto/deep_copy.hpp>
#include <boost/spirit/home/qi/directive/no_case.hpp>
#include <boost/spirit/home/qi/operator/sequence.hpp>
#include <boost/spirit/home/qi/operator/optional.hpp>
#include <boost/spirit/home/qi/string/lit.hpp>

namespace boost { namespace coerce { namespace tag {

    struct none { };

    template <unsigned Radix>
    struct base {
        template <typename Target>
        struct parser {
            typedef typename detail::integer_parser<
                Target, Radix
            >::type type;

            static inline type const
            call() {
                return type();
            }
        };

        template <typename Source>
        struct generator {
            typedef typename detail::integer_generator<
                Source, Radix
            >::type type;

            static inline type const
            call() {
                return type();
            }
        };
    };

    struct bin
        : base<2> { };

    struct oct
        : base<8> { };

    struct hex
        : base<16> {
        template <typename Target>
        struct parser {
            typedef typename detail::integer_parser<
                Target, 16
            >::type parser_type;

            typedef typename proto::result_of::deep_copy<
                BOOST_TYPEOF_TPL((-spirit::standard::no_case_type()["0x"] >> parser_type()))
            >::type type;

            static inline type const
            call() {
                return proto::deep_copy(
                    -spirit::standard::no_case_type()["0x"] >> parser_type());
            }
        };
    };

} } }  // namespace boost::coerce::tag

#endif  // BOOST_COERCE_TAG_HPP
