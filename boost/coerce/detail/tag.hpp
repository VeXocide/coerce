//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_DETAIL_TAG_HPP
#define BOOST_COERCE_DETAIL_TAG_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/or.hpp>

namespace boost { namespace coerce { namespace detail {

    BOOST_MPL_HAS_XXX_TEMPLATE_DEF(parser)
    BOOST_MPL_HAS_XXX_TEMPLATE_DEF(generator)

    template <typename T>
    struct is_tag
        : mpl::or_<
            has_parser<T>,
            has_generator<T>
        > { };

} } }  // namespace boost::coerce::detail

#endif  // BOOST_COERCE_DETAIL_TAG_HPP
