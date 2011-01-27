//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/coerce.hpp>

#include <iostream>
#include <ostream>
#include <string>

int
main() {
    using namespace boost;
    
    // A coerce from a binary string representation to integer ..
    std::cout << coerce::as<int>("10111", coerce::tag::bin) << std::endl;

    // .. and vice-versa
    std::cout << coerce::as<std::string>(23, coerce::tag::bin) << std::endl;
}
