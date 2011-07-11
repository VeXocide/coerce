//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/coerce.hpp>
#include <boost/spirit/include/support_unused.hpp>

#include <cerrno>  // for errno
#include <cstdio>  // for std::strtol
#include <iostream>

struct strtol {
    template <typename Target, typename Source, typename Tag>
    static inline bool
    call(Target & target, Source const & source) {
        target = std::strtol(source, NULL, 10);

        return (errno != EINVAL);
    }
};

namespace boost { namespace coerce { namespace traits {

    template <std::size_t N>
    struct as<long int, char [N], spirit::unused_type>
        : strtol { };

} } }  // namespace boost::coerce::traits

int
main() {
    using namespace boost;

    // A coerce from char [N] to long int using std::strtol
    std::cout << coerce::as<long int>("23") << std::endl;
}
