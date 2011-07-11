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

#include <boost/mpl/if.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_signed.hpp>

namespace boost { namespace coerce { namespace tag {

    struct none { };

    struct bin {
        template <typename Target>
        struct parser {
            BOOST_STATIC_ASSERT(is_integral<Target>::value);

            typedef typename mpl::if_<
                is_signed<Target>,
                spirit::qi::int_parser<Target, 2>,
                spirit::qi::uint_parser<Target, 2>
            >::type type;
                
            static inline type const
            call() {
                return type();
            }
        };

        template <typename Source>
        struct generator {
            BOOST_STATIC_ASSERT(is_integral<Source>::value);

            typedef typename mpl::if_<
                is_signed<Source>,
                spirit::karma::int_generator<Source, 2>,
                spirit::karma::uint_generator<Source, 2>
            >::type type;

            static inline type const
            call() {
                return type();
            }
        };
    };

} } }  // namespace boost::coerce::tag

#endif  // BOOST_COERCE_TAG_HPP
