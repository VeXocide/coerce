//           Copyright Jeroen Habraken 2010 - 2011.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_COERCE_HPP
#define BOOST_COERCE_COERCE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/coerce/push_back.hpp>
#include <boost/coerce/reserve.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/end.hpp>
#include <boost/range/has_range_iterator.hpp>
#include <boost/range/size.hpp>
#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/char.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/karma/operator/optional.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/qi/operator/optional.hpp>
#include <boost/spirit/include/version.hpp>
#include <boost/static_assert.hpp>

#include <typeinfo>  // for std::bad_cast

namespace boost { namespace coerce { namespace detail {

    template <typename Target, typename Source>
    struct as {
        static inline bool
        call(Target & target, Source const & source) {
            return do_call(
                target,
                source,
                has_range_const_iterator<Source>(),
                typename detail::has_push_back<Target>::type());
        }

    private:
        static inline bool
        do_call(
            Target & target,
            Source const & source,
            mpl::true_,
            bool
        ) {
            typename range_difference<Source>::type size = 
                boost::size(source);
            call_reserve(target, size);

            typedef typename range_const_iterator<Source>::type iterator_type;
            iterator_type begin = boost::const_begin(source),
                          iterator = begin;
            iterator_type end = boost::const_end(source);

            bool result = spirit::qi::parse(
                iterator, end, target);

            if (!result || !((begin <= iterator && iterator < end && *iterator == 0) || iterator == end))
                return false;

            return true;
        }

        static inline bool
        do_call(
            Target & target,
            Source const & source,
            mpl::false_,
            mpl::true_
        ) {
            call_reserve(
                target,
                traits::reserve_size<Source>::call(source));

            bool result = spirit::karma::generate(
                std::back_inserter(target),
#if SPIRIT_VERSION <= 0x2030
                spirit::karma::auto_,
#endif
                source);

            return result;
        }

        static inline bool
        do_call(
            Target & target,
            Source const & source,
            mpl::false_,
            mpl::false_
        ) {
            BOOST_STATIC_ASSERT(sizeof(Target) == 0);

            return false;
        }
    };

} } }  // namespace boost::coerce::detail

namespace boost { namespace coerce { namespace traits {

    template <typename Target, typename Source, typename Enable = void>
    struct as
        : coerce::detail::as<Target, Source> { };

} } }  // namespace boost::coerce::traits

namespace boost { namespace coerce {

    class bad_cast
        : public std::bad_cast { };

    template <typename Target, typename Source>
    inline Target
    as(Source const & source) {
        Target target;

        bool result = traits::as<
                Target, Source
            >::call(target, source);

        if (!result) {
            throw coerce::bad_cast();
        }

        return target;
    }

    template <typename Target, typename Source>
    inline Target
    as_default(
        Source const & source,
        Target const & default_value = Target()
    ) {
        Target target;

        bool result = traits::as<
                Target, Source
            >::call(target, source);

        if (!result) {
            return default_value;
        }

        return target;
    }

} }  // namespace boost::coerce

#endif  // BOOST_COERCE_COERCE_HPP
