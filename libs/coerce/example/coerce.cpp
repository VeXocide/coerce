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
    
    // A coerce from string to integer ..
    std::cout << coerce::as<int>("23") << std::endl;

    // .. and vice-versa
    std::cout << coerce::as<std::string>(23) << std::endl;

    // A no-throw coerce from string to integer with default value
    std::cout << coerce::as_default<int>("XXX", 23) << std::endl;
}
