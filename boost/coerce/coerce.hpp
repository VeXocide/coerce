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

#include <boost/coerce/detail/backend.hpp>
#include <boost/coerce/sequence.hpp>
#include <boost/coerce/string.hpp>

#include <boost/throw_exception.hpp>

#include <typeinfo>  // for std::bad_cast

namespace boost { namespace coerce {

    namespace traits {

        template <typename Target, typename Source, typename Enable = void>
        struct as
            : detail::backend<
                typename traits::is_sequence<Target>::type,
                typename traits::is_string<Source>::type
            >::type { };

    }  // namespace traits

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
            throw_exception(coerce::bad_cast());
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
