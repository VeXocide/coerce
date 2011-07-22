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

#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>

#include <iterator>
#include <string>
#include <vector>

namespace boost { namespace coerce { namespace traits {

    template <typename T>
    struct sequence_impl
        : mpl::identity<void> { };

    template <typename T>
    struct sequence_impl_std {
        typedef std::back_insert_iterator<T> type;

        static inline type
        back_inserter(T & value) {
            return std::back_inserter(value);
        }
    };

    template <typename T, typename Traits, typename Allocator>
    struct sequence_impl<std::basic_string<T, Traits, Allocator> >
        : sequence_impl_std<std::basic_string<T, Traits, Allocator> > { };

    template <typename T, typename Allocator>
    struct sequence_impl<std::vector<T, Allocator> >
        : sequence_impl_std<std::vector<T, Allocator> > { };

    template <typename T, typename Enable = void>
    struct sequence
        : sequence_impl<T> { };

    template <typename T>
    struct is_sequence
        : mpl::not_<is_same<typename sequence<T>::type, void> > { };

} } }  // namespace boost::coerce::traits

#endif  // BOOST_COERCE_SEQUENCE_HPP
