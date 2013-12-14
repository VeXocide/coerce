//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/coerce.hpp>

#include <iostream>
#include <string>
#include <utility>

template <typename Target, typename Source, typename Tag>
inline std::pair<Target, bool>
as_pair(Source const & source, Tag const & tag) {
    Target target;

    bool result = boost::coerce::traits::as<
            Target, Source, Tag
        >::template call<Target, Source, Tag>(
            target, source, tag);

    return std::make_pair(target, result);
}

template <typename Target, typename Source>
inline std::pair<Target, bool>
as_pair(Source const & source) {
    return as_pair<Target, Source, boost::coerce::tag::none>(
        source, boost::coerce::tag::none());
}

int
main() {
    // A coerce from string to integer
    std::pair<int, bool> result = as_pair<int>("23");

    if (result.second) {
        std::cout << result.first << std::endl;
    }
}
