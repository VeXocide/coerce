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
#include <boost/coerce/tag.hpp>

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

#include <typeinfo>  // for std::bad_cast

namespace boost { namespace coerce {

    namespace traits {

        template <
            typename Target
          , typename Source
          , typename Tag
          , typename Enable = void
        >
        struct as
            : detail::backend<
                typename traits::is_sequence<Target>::type,
                typename traits::is_string<Source>::type
            >::type { };

    }  // namespace traits

    class bad_cast
        : public std::bad_cast { };

    template <typename Target, typename Source, typename Tag>
    inline Target
    as(Source const & source, Tag const & tag) {
        Target target;

        bool result = traits::as<
                Target, Source, Tag
            >::BOOST_NESTED_TEMPLATE call<Target, Source, Tag>(
                target, source, tag);

        if (!result) {
            throw_exception(coerce::bad_cast());
        }

        return target;
    }

    template <typename Target, typename Source>
    inline Target
    as(Source const & source) {
        return as<Target, Source, tag::none>(source, tag::none());
    }

    template <typename Target, typename Source, typename Tag>
    inline typename disable_if<
        is_same<Target, Tag>, Target>::type
    as_default(
        Source const & source,
        Tag const & tag,
        Target const & default_value = Target()
    ) {
        Target target;

        bool result = traits::as<
                Target, Source, Tag
            >::BOOST_NESTED_TEMPLATE call<Target, Source, Tag>(
                target, source, tag);

        if (!result) {
            return default_value;
        }

        return target;
    }

    template <typename Target, typename Source>
    inline Target
    as_default(
        Source const & source,
        Target const & default_value = Target()
    ) {
        return as_default<Target, Source, tag::none>(
            source, tag::none(), default_value);
    }

} }  // namespace boost::coerce

#endif  // BOOST_COERCE_COERCE_HPP
