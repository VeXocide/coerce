//           Copyright Jeroen Habraken 2010 - 2011.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_RESERVE_HPP
#define BOOST_COERCE_RESERVE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/coerce/detail/reserve.hpp>

#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/optional.hpp>

#include <cstddef>  // std::size_t

namespace boost { namespace coerce { namespace traits {

    template <typename T>
    struct reserve_size_impl {
        BOOST_STATIC_CONSTANT(std::size_t, value = 0);
    };

    template <>
    struct reserve_size_impl<char> {
        BOOST_STATIC_CONSTANT(std::size_t, value = 1);
    };

    template <>
    struct reserve_size_impl<wchar_t> {
        BOOST_STATIC_CONSTANT(std::size_t, value = 1);
    };

    template <typename T>
    struct reserve_size_impl_integral {
        BOOST_STATIC_CONSTANT(std::size_t, value =
            std::numeric_limits<T>::is_signed +
            1 +
            std::numeric_limits<T>::digits10);
    };

    template <>
    struct reserve_size_impl<int>
        : reserve_size_impl_integral<int> { };

    template <>
    struct reserve_size_impl<short>
        : reserve_size_impl_integral<short> { };

    template <>
    struct reserve_size_impl<long>
        : reserve_size_impl_integral<long> { };

    template <>
    struct reserve_size_impl<unsigned int>
        : reserve_size_impl_integral<unsigned int> { };

    template <>
    struct reserve_size_impl<unsigned short>
        : reserve_size_impl_integral<unsigned short> { };

    template <>
    struct reserve_size_impl<unsigned long>
        : reserve_size_impl_integral<unsigned long> { };

#ifdef BOOST_HAS_LONG_LONG

    template <>
    struct reserve_size_impl<boost::long_long_type>
        : reserve_size_impl_integral<boost::long_long_type> { };

    template <>
    struct reserve_size_impl<boost::ulong_long_type>
        : reserve_size_impl_integral<boost::ulong_long_type> { };

#endif  // BOOST_HAS_LONG_LONG

    template <typename T>
    struct reserve_size_impl_floating_point {
        BOOST_STATIC_CONSTANT(std::size_t, value =
            std::numeric_limits<T>::is_signed +
            8 +
            std::numeric_limits<T>::digits10);
    };

    template <>
    struct reserve_size_impl<float>
        : reserve_size_impl_floating_point<float> { };

    template <>
    struct reserve_size_impl<double>
        : reserve_size_impl_floating_point<double> { };

    template <>
    struct reserve_size_impl<long double>
        : reserve_size_impl_floating_point<long double> { };

    template <>
    struct reserve_size_impl<bool> {
        BOOST_STATIC_CONSTANT(std::size_t, value = 5);
    };

    template <typename T>
    struct reserve_size_impl<boost::optional<T> >
        : reserve_size_impl<T> { };

    template <typename T, typename Enable = void>
    struct reserve_size {
        typedef std::size_t type;

        static inline type
        call(T const &) {
            return reserve_size_impl<T>::value;
        }
    };

} } }  // namespace boost::coerce::traits

#endif  // BOOST_COERCE_RESERVE_HPP
