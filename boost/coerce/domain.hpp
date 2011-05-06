//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_DOMAIN_HPP
#define BOOST_COERCE_DOMAIN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/coerce/detail/push_back.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/range/has_range_iterator.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace coerce { namespace traits {

    template <typename U, typename V>
    struct domain_impl {
        BOOST_STATIC_ASSERT(sizeof(U) == 0);
    };

    template <typename U>
    struct domain_impl<U, mpl::true_> {
        typedef spirit::qi::domain type;
    };

    template <>
    struct domain_impl<mpl::true_, mpl::false_> {
        typedef spirit::karma::domain type;
    };

    template <typename Target, typename Source, typename Enable = void>
    struct domain
        : domain_impl<
            typename detail::has_push_back<Target>::type,
            typename has_range_const_iterator<Source>::type
        > { };

    template <typename Domain, typename Target, typename Source>
    struct as;

} } }  // namespace boost::coerce::traits

#endif  // BOOST_COERCE_DOMAIN_HPP
