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

#include <boost/coerce/domain.hpp>
#include <boost/coerce/karma.hpp>
#include <boost/coerce/qi.hpp>

#include <typeinfo>  // for std::bad_cast

namespace boost { namespace coerce {

    namespace detail {

        template <typename Target, typename Source, typename Enable = void>
        struct as
            : traits::as<
                typename traits::domain<Target, Source>::type, Target, Source
            > { };

    }  // namespace detail

    class bad_cast
        : public std::bad_cast { };

    template <typename Target, typename Source>
    inline Target
    as(Source const & source) {
        Target target;

        bool result = detail::as<
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

        bool result = detail::as<
                Target, Source
            >::call(target, source);

        if (!result) {
            return default_value;
        }

        return target;
    }

} }  // namespace boost::coerce

#endif  // BOOST_COERCE_COERCE_HPP
