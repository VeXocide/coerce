//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_DETAIL_BACKEND_HPP
#define BOOST_COERCE_DETAIL_BACKEND_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/coerce/detail/karma.hpp>
#include <boost/coerce/detail/qi.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace coerce { namespace detail {

    template <typename U, typename V>
    struct backend {
        BOOST_STATIC_ASSERT(sizeof(U) == 0);
    };

    template <typename U>
    struct backend<U, mpl::true_> {
        typedef qi type;
    };

    template <>
    struct backend<mpl::true_, mpl::false_> {
        typedef karma type;
    };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_BACKEND_HPP
