//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_SEQUENCE_HPP
#define BOOST_COERCE_SEQUENCE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/mpl/bool.hpp>

#include <iterator>
#include <string>
#include <vector>

namespace boost { namespace coerce { namespace traits {

    template <typename T>
    struct sequence_traits_impl;

    template <typename T>
    struct sequence_traits_impl_std {
        typedef std::back_insert_iterator<T> iterator;

        static inline iterator
        back_inserter(T & value) {
            return std::back_inserter(value);
        }
    };

    template <typename T, typename Traits, typename Allocator>
    struct sequence_traits_impl<std::basic_string<T, Traits, Allocator> >
        : sequence_traits_impl_std<
            std::basic_string<T, Traits, Allocator>
        > { };

    template <typename T, typename Allocator>
    struct sequence_traits_impl<std::vector<T, Allocator> >
        : sequence_traits_impl_std<std::vector<T, Allocator> > { };

    template <typename T, typename Enable = void>
    struct sequence_traits
        : sequence_traits_impl<T> { };

    template <typename T>
    struct is_sequence_impl
        : mpl::false_ { };

    template <typename T, typename Traits, typename Allocator>
    struct is_sequence_impl<std::basic_string<T, Traits, Allocator> >
        : mpl::true_ { };

    template <typename T, typename Allocator>
    struct is_sequence_impl<std::vector<T, Allocator> >
        : mpl::true_ { };

    template <typename T, typename Enable = void>
    struct is_sequence
        : is_sequence_impl<T> { };

} } }  // namespace boost::coerce::traits

#endif  // BOOST_COERCE_SEQUENCE_HPP
