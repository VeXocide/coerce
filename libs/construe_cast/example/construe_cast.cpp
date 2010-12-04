//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/construe_cast.hpp>

#include <iostream>
#include <ostream>
#include <string>

int main(int argc, char** argv) {
    // A construe_cast from string to integer ..
    std::cout << boost::construe_cast<int>("23") << std::endl;

    // .. and vice-versa
    std::cout << boost::construe_cast<std::string>(23) << std::endl;

    // A no-throw construe_cast from string to integer with fallback value
    std::cout << boost::construe_cast<int>("XXX", 42) << std::endl;
}
