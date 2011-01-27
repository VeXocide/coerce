//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/coerce.hpp>
#include <boost/optional.hpp>

#include <iostream>
#include <ostream>

namespace std {

    template <typename T>
    std::ostream &
    operator<<(std::ostream & out, boost::optional<T> const & optional) {
        if (optional)
            return out << *optional;

        return out;
    }

}  // namespace std

int
main() {
    using namespace boost;
    
    // A no-throw coerce returning an optional<int>(23)
    std::cout << coerce::as_default<optional<int> >("23") << std::endl;

    // A no-throw coerce returning an empty, default constructed optional<int>
    std::cout << coerce::as_default<optional<int> >("XXX") << std::endl;
}
