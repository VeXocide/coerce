// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_HPP
#define BOOST_COERCE_HPP

#include <boost/coerce/container.hpp>
#include <boost/coerce/iterable.hpp>
#include <boost/coerce/reserve.hpp>
#include <boost/coerce/spirit.hpp>
#include <boost/coerce/tag.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/spirit/home/karma/auto.hpp>
#include <boost/spirit/home/karma/char.hpp>
#include <boost/spirit/home/karma/numeric.hpp>
#include <boost/spirit/home/karma/operator/optional.hpp>
#include <boost/spirit/home/qi/auto.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/qi/operator/optional.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/include/version.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

#include <typeinfo>  // for std::bad_cast

namespace boost {

    namespace coerce {

        class bad_cast
            : public std::bad_cast { };

        namespace detail {

            template <typename Target, typename Source, typename Tag>
            struct as {
                static inline bool
                call(Target & target, Source const & source) {
                    return do_call(
                        target,
                        source,
                        traits::is_iterable<Source>(),
                        traits::is_container<Target>());
                }

                private:
                    static inline bool
                    do_call(
                        Target & target,
                        Source const & source,
                        mpl::true_ const,
                        bool const
                    ) {
                        typedef traits::iterable<Source> iterable_type;
                        typedef typename iterable_type::const_iterator iterator_type;

                        iterable_type iterable(source);

                        if (iterable.size() < 1)
                            return false;

                        call_reserve(target, iterable.size());

                        iterator_type begin = iterable.begin(), iterator = begin;
                        iterator_type end = iterable.end();

                        bool result = spirit::qi::parse(
                            iterator, end, wrap<Tag>::call(target));

                        if (!result || !((begin < iterator && iterator < end && *iterator == 0) || iterator == end))
                            return false;

                        return true;
                    }

                    static inline bool
                    do_call(
                        Target & target,
                        Source const & source,
                        mpl::false_ const,
                        mpl::true_ const
                    ) {
                        call_reserve(
                            target,
                            traits::reserve_size<Source, Tag>::call(source));

                        bool result = spirit::karma::generate(
                            std::back_inserter(target),
#if SPIRIT_VERSION <= 0x2030
                            spirit::karma::auto_,
#endif
                            wrap<Tag>::call(source));

                        return result;
                    }

                    static inline void
                    do_call(
                        Target & target,
                        Source const & source,
                        mpl::false_ const,
                        mpl::false_ const
                    ) {
                        // TODO, implement a lexical_cast fallback
                        
                        BOOST_STATIC_ASSERT(sizeof(Target) == 0);
                    }
            };

        }  // namespace detail

        namespace traits {

            template <typename Target, typename Source, typename Tag, typename Enable = void>
            struct as
                : coerce::detail::as<Target, Source, Tag> { };

        }  // namespace traits

        template <typename Target, typename Source, typename Tag>
        inline Target
        as(Source const & source, Tag const &) {
            Target target;

            bool result = traits::as<
                    Target, Source, Tag
                >::call(target, source);

            if (!result)
                throw coerce::bad_cast();

            return target;
        }

        template <typename Target, typename Source>
        inline Target
        as(Source const & source) {
            return as<Target, Source>(source, spirit::unused);
        }

        template <typename Target, typename Source, typename Tag>
        inline typename disable_if<
            is_same<Target, Tag>, Target>::type
        as_default(
            Source const & source,
            Tag const &,
            Target const & default_value = Target()
        ) {
            Target target;

            bool result = traits::as<
                    Target, Source, Tag
                >::call(target, source);

            if (!result)
                return default_value;

            return target;
        }

        template <typename Target, typename Source>
        inline Target
        as_default(
            Source const & source,
            Target const & default_value = Target()
        ) {
            return as_default<Target, Source>(
                source, spirit::unused, default_value);
        }

    }  // namespace coerce

}  // namespace boost

#endif  // BOOST_COERCE_HPP
