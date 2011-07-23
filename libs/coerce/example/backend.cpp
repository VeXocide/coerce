//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/coerce.hpp>

#include <cctype>  // for std::isspace
#include <cerrno>  // for errno
#include <cstdio>  // for std::strtol
#include <iostream>

struct strtol {
    template <typename Target, typename Source, typename Tag>
    static inline bool
    call(Target & target, Source const & source, Tag const &) {
        char *end;
        
        if (std::isspace(*source)) {
            return false;
        }

        errno = 0;
        target = std::strtol(source, &end, 10);

        if (errno != 0 || *end != 0 || source == end) {
            return false;
        }

        return true;
    }
};

namespace boost { namespace coerce { namespace traits {

    template <std::size_t N>
    struct as<long int, char [N], tag::none>
        : strtol { };

} } }  // namespace boost::coerce::traits

int
main() {
    using namespace boost;

    // A coerce from char [N] to long int using std::strtol
    std::cout << coerce::as<long int>("23") << std::endl;
}
