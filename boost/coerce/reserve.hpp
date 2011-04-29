//                 Copyright Adam Merz 2010.
//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_RESERVE_HPP
#define BOOST_COERCE_RESERVE_HPP

#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/optional.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <cstddef>

#ifndef BOOST_COERCE_UNSPECIALIZED_RESERVE
#define BOOST_COERCE_UNSPECIALIZED_RESERVE 16
#endif  // BOOST_COERCE_UNSPECIALIZED_RESERVE

namespace boost {

    namespace coerce {

        namespace traits {

            template <typename Type>
            struct reserve_size_impl {
                BOOST_STATIC_CONSTANT(std::size_t, value =
                    BOOST_COERCE_UNSPECIALIZED_RESERVE);
            };

            template <>
            struct reserve_size_impl<char> {
                BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            };

            template <>
            struct reserve_size_impl<wchar_t> {
                BOOST_STATIC_CONSTANT(std::size_t, value = 1);
            };

            template <typename Type>
            struct reserve_size_impl_integral {
                BOOST_STATIC_CONSTANT(std::size_t, value =
                    std::numeric_limits<Type>::is_signed +
                    1 +
                    std::numeric_limits<Type>::digits10);
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

            template <typename Type>
            struct reserve_size_impl_floating_point {
                BOOST_STATIC_CONSTANT(std::size_t, value =
                    std::numeric_limits<Type>::is_signed +
                    8 +
                    std::numeric_limits<Type>::digits10);
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

            template <typename Type>
            struct reserve_size_impl<boost::optional<Type> >
                : reserve_size_impl<Type> { };

            template <typename Type, typename Enable = void>
            struct reserve_size {
                typedef std::size_t type;

                static inline type
                call(typename remove_reference<Type>::type const &) {
                    return reserve_size_impl<
                        typename remove_const<
                            typename remove_reference<Type>::type
                        >::type>::value;
                }
            };

        }  // namespace traits

        namespace detail {

            template <typename Sequence>
            class has_reserve {
                template <typename U, void (U::*)(typename U::size_type) = &U::reserve>
                struct impl { };

                template <typename U>
                static type_traits::yes_type test(U*, impl<U>* = 0);

                template <typename U>
                static type_traits::no_type test(...);

            public:
                BOOST_STATIC_CONSTANT(bool, value =
                    sizeof(test<Sequence>(0)) == sizeof(type_traits::yes_type));
                typedef mpl::bool_<value> type;
            };

            template <typename Sequence>
            inline void
            call_reserve_impl(
                Sequence & sequence,
                typename Sequence::size_type const size,
                mpl::true_ const
            ) {
                sequence.reserve(size);
            }

            template <typename Sequence>
            inline void
            call_reserve_impl(
                Sequence const &,
                typename Sequence::size_type const,
                mpl::false_ const
            ) {
                // Missing .reserve()
            }

            template <typename Sequence>
            inline void
            call_reserve(
                Sequence & sequence,
                typename Sequence::size_type const size
            ) {
                call_reserve_impl(
                    sequence, size, typename has_reserve<Sequence>::type());
            }

            template <typename Sequence>
            inline void
            call_reserve(
                Sequence const &,
                std::size_t const
            ) {
                // Missing size_type
            }

        }  // namespace detail

    }  // namespace coerce

}  // namespace boost

#endif  // BOOST_COERCE_RESERVE_HPP
