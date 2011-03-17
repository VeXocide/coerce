//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_TAG_HPP
#define BOOST_COERCE_TAG_HPP

#include <boost/mpl/if.hpp>
#include <boost/proto/deep_copy.hpp>
#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/directive/no_case.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/qi/operator/sequence.hpp>
#include <boost/spirit/home/qi/operator/optional.hpp>
#include <boost/spirit/home/qi/string/lit.hpp>
#include <boost/static_assert.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_signed.hpp>

namespace boost {

    namespace coerce {

        namespace detail {

            // TODO, numeric_parser and numeric_generator: http://codepad.org/qbneDiqx

        }  // namespace detail

        namespace tag {

            struct bin_type {
                template <typename Target>
                struct parser {
                    BOOST_STATIC_ASSERT(is_integral<Target>::value);

                    typedef typename mpl::if_<
                        is_signed<Target>,
                        spirit::qi::int_parser<Target, 2>,
                        spirit::qi::uint_parser<Target, 2>
                    >::type type;
                
                    static inline type const
                    call() {
                        return type();
                    }
                };

                template <typename Source>
                struct generator {
                    BOOST_STATIC_ASSERT(is_integral<Source>::value);

                    typedef typename mpl::if_<
                        is_signed<Source>,
                        spirit::karma::int_generator<Source, 2>,
                        spirit::karma::uint_generator<Source, 2>
                    >::type type;

                    static inline type const
                    call() {
                        return type();
                    }
                };
            } const bin = bin_type();

            struct oct_type {
                template <typename Target>
                struct parser {
                    BOOST_STATIC_ASSERT(is_integral<Target>::value);

                    typedef typename mpl::if_<
                        is_signed<Target>,
                        spirit::qi::int_parser<Target, 8>,
                        spirit::qi::uint_parser<Target, 8>
                    >::type type;

                    static inline type const
                    call() {
                        return type();
                    }
                };

                template <typename Source>
                struct generator {
                    BOOST_STATIC_ASSERT(is_integral<Source>::value);

                    typedef typename mpl::if_<
                        is_signed<Source>,
                        spirit::karma::int_generator<Source, 8>,
                        spirit::karma::uint_generator<Source, 8>
                    >::type type;

                    static inline type const
                    call() {
                        return type();
                    }
                };
            } const oct = oct_type();

            struct hex_type {
                template <typename Target>
                struct parser {
                    BOOST_STATIC_ASSERT(is_integral<Target>::value);

                    typedef typename mpl::if_<
                        is_signed<Target>,
                        spirit::qi::int_parser<Target, 16>,
                        spirit::qi::uint_parser<Target, 16>
                    >::type parser_type;

                    typedef typename proto::result_of::deep_copy<
                        BOOST_TYPEOF_TPL((-spirit::standard::no_case["0x"] >> parser_type()))
                    >::type type;

                    static inline type const
                    call() {
                        return proto::deep_copy(
                            -spirit::standard::no_case["0x"] >> parser_type());
                    }
                };

                template <typename Source>
                struct generator {
                    BOOST_STATIC_ASSERT(is_integral<Source>::value);

                    typedef typename mpl::if_<
                        is_signed<Source>,
                        spirit::karma::int_generator<Source, 16>,
                        spirit::karma::uint_generator<Source, 16>
                    >::type type;

                    static inline type const
                    call() {
                        return type();
                    }
                };
            } const hex = hex_type();

        }  // namespace tag

    }  // namespace coerce

}  // namespace boost

#endif  // BOOST_COERCE_TAG_HPP
