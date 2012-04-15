//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_DETAIL_SPIRIT_HPP
#define BOOST_COERCE_DETAIL_SPIRIT_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/coerce/detail/karma.hpp>
#include <boost/coerce/detail/qi.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/static_assert.hpp>

namespace boost { namespace coerce { namespace detail {

    template <typename T, typename U>
    struct spirit {
        BOOST_STATIC_ASSERT(sizeof(T) == 0);
    };

    template <>
    struct spirit<mpl::true_, mpl::false_> {
        typedef qi type;
    };

    template <typename T>
    struct spirit<T, mpl::true_> {
        typedef karma type;
    };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_SPIRIT_HPP
