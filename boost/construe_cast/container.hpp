//            Copyright Joel de Guzman 2001 - 2010.
//            Copyright Hartmut Kaiser 2001 - 2010.
//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// This file was initially a copy of boost/spirit/home/support/container.hpp

#ifndef BOOST_CONSTRUE_CONTAINER_HPP
#define BOOST_CONSTRUE_CONTAINER_HPP

#include <boost/mpl/bool.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost {

    namespace construe {

        namespace traits {

            namespace detail {

                BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)
                BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
                BOOST_MPL_HAS_XXX_TRAIT_DEF(size_type)
                BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)

            }  // namespace detail

            template <typename Type>
            struct is_container_impl
                : mpl::bool_<
                    detail::has_value_type<Type>::value &&
                    detail::has_iterator<Type>::value &&
                    detail::has_size_type<Type>::value &&
                    detail::has_reference<Type>::value> { };

            template <typename Type, typename Enable = void>
            struct is_container
                : is_container_impl<
                    typename remove_const<
                        typename remove_reference<Type>::type
                    >::type> { };

        }  // namespace traits

    }  // namespace construe

}  // namespace boost

#endif  // BOOST_CONSTRUE_CONTAINER_HPP
