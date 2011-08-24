//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_STRING_HPP
#define BOOST_COERCE_STRING_HPP

#include <boost/coerce/char.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <cstddef>  // std::size_t
#include <string>

namespace boost { namespace coerce { namespace traits {

    template <typename T>
    struct string_traits_impl;

    template <typename T>
    struct string_traits_impl<T *> {
        typedef T const * const_iterator;
        typedef std::size_t size_type;

        static inline const_iterator
        begin(T * const value) {
            return value;
        }

        static inline const_iterator
        end(T * const value) {
            return value + length(value) + 1;
        }

        static inline size_type
        length(T * const value) {
            return std::char_traits<
                    typename remove_const<T>::type
                >::length(value);
        }
    };

    template <typename T, std::size_t N>
    struct string_traits_impl<T [N]> {
        typedef T const * const_iterator;
        typedef std::size_t size_type;

        static inline const_iterator
        begin(T const(& value)[N]) {
            return value;
        }

        static inline const_iterator
        end(T const(& value)[N]) {
            return value + length(value);
        }

        static inline size_type
        length(T const(& value)[N]) {
            return value[N - 1] == 0 ? N - 1 : N;
        }
    };

    template <typename T, typename Traits, typename Allocator>
    struct string_traits_impl<std::basic_string<T, Traits, Allocator> > {
        typedef std::basic_string<T, Traits, Allocator> type;

        typedef typename type::const_iterator const_iterator;
        typedef typename type::size_type size_type;

        static inline const_iterator
        begin(type const & value) {
            return value.begin();
        }

        static inline const_iterator
        end(type const & value) {
            return value.end();
        }

        static inline size_type
        length(type const & value) {
            return value.length();
        }
    };

    template <typename T, typename Enable = void>
    struct string_traits
        : string_traits_impl<T> { };

    template <typename T>
    struct is_string_impl
        : mpl::false_ { };

    template <typename T>
    struct is_string_impl<T *>
        : traits::is_char<T> { };

    template <typename T, std::size_t N>
    struct is_string_impl<T [N]>
        : traits::is_char<T> { };

    template <typename T, typename Traits, typename Allocator>
    struct is_string_impl<std::basic_string<T, Traits, Allocator> >
        : traits::is_char<T> { };

    template <typename T, typename Enable = void>
    struct is_string
        : is_string_impl<T> { };

} } }  // namespace boost::coerce::traits

#endif  // BOOST_COERCE_STRING_HPP
