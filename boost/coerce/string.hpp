//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_STRING_HPP
#define BOOST_COERCE_STRING_HPP

#include <boost/coerce/char.hpp>

#include <boost/mpl/identity.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <cstddef>  // std::size_t
#include <string>

namespace boost { namespace coerce { namespace traits {

    template <typename T>
    struct string_impl
        : mpl::identity<void> { };

    template <typename T, typename U = typename is_char<T>::type>
    struct string_impl_pointer
        : mpl::identity<void> { };

    template <typename T>
    struct string_impl_pointer<T, mpl::true_> {
        typedef T * type;

        typedef T const *const_iterator;
        typedef std::size_t size_type;

        static inline const_iterator
        begin(type const value) {
            return value;
        }

        static inline const_iterator
        end(type const value) {
            return value + length(value) + 1;
        }

        static inline size_type
        length(type const value) {
            return std::char_traits<
                    typename remove_const<T>::type
                >::length(value);
        }
    };

    template <typename T>
    struct string_impl<T *>
        : string_impl_pointer<T> { };

    template <typename T, std::size_t N, typename U = typename is_char<T>::type>
    struct string_impl_extent
        : mpl::identity<void> { };

    template <typename T, std::size_t N>
    struct string_impl_extent<T, N, mpl::true_> {
        typedef T type[N];

        typedef T const *const_iterator;
        typedef std::size_t size_type;

        static inline const_iterator
        begin(type const & value) {
            return &value[0];
        }

        static inline const_iterator
        end(type const & value) {
            return &value[0] + length(value);
        }

        static inline size_type
        length(type const & value) {
            return value[N - 1] == 0 ? N - 1 : N;
        }
    };

    template <typename T, std::size_t N>
    struct string_impl<T [N]>
        : string_impl_extent<T, N> { };

    template <typename T, typename Traits, typename Allocator>
    struct string_impl<std::basic_string<T, Traits, Allocator> > {
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
    struct string
        : string_impl<T> { };

    template <typename T>
    struct is_string
        : mpl::not_<is_same<typename string<T>::type, void> > { };

} } }  // namespace boost::coerce::traits

#endif  // BOOST_COERCE_STRING_HPP
