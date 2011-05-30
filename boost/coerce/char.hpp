//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_CHAR_HPP
#define BOOST_COERCE_CHAR_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_const.hpp>

namespace boost { namespace coerce { namespace traits {

    template <typename T>
    struct is_char_impl
        : mpl::false_ { };

    template <>
    struct is_char_impl<char>
        : mpl::true_ { };

#ifndef BOOST_NO_WCHAR_T
    template <>
    struct is_char_impl<wchar_t>
        : mpl::true_ { };
#endif

    template <typename T, typename Enable = void>
    struct is_char
        : is_char_impl<typename remove_const<T>::type> { };

} } }  // namespace boost::coerce::traits

#endif  // BOOST_COERCE_CHAR_HPP
