//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_SPIRIT_HPP
#define BOOST_COERCE_SPIRIT_HPP

#include <boost/limits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/numeric/real.hpp>
#include <boost/spirit/home/karma/numeric/real_policies.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/include/version.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace boost {

    namespace coerce {

        namespace detail {

            template <typename Type, typename Tag>
            struct wrapped {
                wrapped(Type & value)
                    : value_(value) { }

                inline Type const &
                get_value() const {
                    return value_;
                }

                inline void
                set_value(Type const & value) {
                    value_ = value;
                } 
                
                private:
                    Type & value_;
            };

            template <typename Tag>
            struct wrap {
                template <typename Type>
                static inline wrapped<
                    typename remove_reference<Type>::type,
                    Tag
                >
                call(Type & value) {
                    return value;
                }
            };

            template <>
            struct wrap<spirit::unused_type> {
                template <typename Type>
                struct result {
                    typedef typename mpl::if_<
                        is_floating_point<Type>,
                        wrapped<
                            typename remove_reference<Type>::type,
                            spirit::unused_type
                        >,
                        Type &
                    >::type type;
                };

                template <typename Type>
                static inline typename result<Type>::type
                call(Type & value) {
                    return value;
                }
            };

            template <typename Target, typename Tag>
            struct create_parser {
                typedef typename Tag::template parser<Target>::type type;

                static inline type const
                call() {
                    return Tag::template parser<Target>::call();
                }
            };

            template <typename Target>
            struct create_parser<Target, spirit::unused_type>
                : spirit::traits::create_parser<Target> { };

            template <typename Source, typename Tag>
            struct create_generator {
                typedef typename Tag::template generator<Source>::type type;

                static inline type const
                call() {
                    return Tag::template generator<Source>::call();
                }
            };

            template <typename Source>
            struct create_generator<Source, spirit::unused_type>
                : spirit::traits::create_generator<Source> { };

            template <typename Source>
            struct real_policies
                : spirit::karma::real_policies<Source> {
                static inline unsigned
                precision(Source const &) {
                    return std::numeric_limits<Source>::digits10 + 1;
                }
            };

            template <typename Source>
            struct create_generator_floating_point {
                typedef spirit::karma::real_generator<
                    Source,
                    real_policies<typename remove_const<Source>::type>
                > type;

                static inline type const
                call() {
                    return type();
                }
            };

            template <>
            struct create_generator<float, spirit::unused_type>
                : create_generator_floating_point<float> { };

            template <>
            struct create_generator<double, spirit::unused_type>
                : create_generator_floating_point<double> { };

            template <>
            struct create_generator<long double, spirit::unused_type>
                : create_generator_floating_point<long double> { };

        }  // namespace detail 

    }  // namespace coerce

    namespace spirit {

        namespace traits {

            template <typename Target, typename Tag>
            struct create_parser<coerce::detail::wrapped<Target, Tag> >
                : coerce::detail::create_parser<
                    // NOTE, reference already remove in coerce::detail::wrap
                    typename remove_const<Target>::type,
                    Tag
                > { };

            template <typename Target, typename Tag>
            struct assign_to_attribute_from_value<
                coerce::detail::wrapped<Target, Tag>,
                typename remove_const<Target>::type
            > {
                static inline void
                call(
                    Target const & value,
                    coerce::detail::wrapped<Target, Tag> & attribute
                ) {
                    attribute.set_value(value);
                }
            };

            template <typename Target, typename Tag, typename Attrib>
            struct assign_to_attribute_from_value<
                coerce::detail::wrapped<Target, Tag>,
                Attrib
            > {
                BOOST_STATIC_ASSERT(sizeof(Target) == 0);
            };

            template <typename Source, typename Tag>
            struct create_generator<coerce::detail::wrapped<Source, Tag> >
                : coerce::detail::create_generator<
                    // NOTE, reference already remove in coerce::detail::wrap
                    typename remove_const<Source>::type,
                    Tag
                > { };

            template <typename Source, typename Tag>
            struct extract_from_attribute<
#if SPIRIT_VERSION >= 2040
                coerce::detail::wrapped<Source, Tag>,
                typename remove_const<Source>::type
#else
                coerce::detail::wrapped<Source, Tag>
#endif
            > {
                typedef Source type;

                template <typename Context>
                static inline type const &
                call(
                    coerce::detail::wrapped<Source, Tag> const & attribute,
                    Context &
                ) {
                    return attribute.get_value();
                }
            };

#if SPIRIT_VERSION >= 2040
            template <typename Source, typename Tag, typename Attrib>
            struct extract_from_attribute<
                coerce::detail::wrapped<Source, Tag>,
                Attrib
            > {
                BOOST_STATIC_ASSERT(sizeof(Source) == 0);
            };
#endif

        }  // namespace traits

    }  // namespace spirit

}  // namespace boost

#endif  // BOOST_COERCE_SPIRIT_HPP
