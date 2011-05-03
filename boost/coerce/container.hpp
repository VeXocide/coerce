//           Copyright Jeroen Habraken 2010 - 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_CONTAINER_HPP
#define BOOST_COERCE_CONTAINER_HPP

#include <boost/mpl/and.hpp>
#include <boost/mpl/has_xxx.hpp>

namespace boost {

    namespace coerce {

        namespace traits {

            namespace detail {

                BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)
                BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator)
                BOOST_MPL_HAS_XXX_TRAIT_DEF(size_type)
                BOOST_MPL_HAS_XXX_TRAIT_DEF(reference)

            }  // namespace detail

            template <typename Type>
            struct is_container_impl
                : mpl::and_<
                    detail::has_value_type<Type>,
                    detail::has_iterator<Type>,
                    detail::has_size_type<Type>,
                    detail::has_reference<Type>
                > { };

            template <typename Type, typename Enable = void>
            struct is_container
                : is_container_impl<Type> { };

        }  // namespace traits

    }  // namespace coerce

}  // namespace boost

#endif  // BOOST_COERCE_CONTAINER_HPP
