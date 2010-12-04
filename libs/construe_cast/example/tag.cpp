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
    // A construe_cast from hexadecimal string to integer, "0x23", "0X23" as well as "23" is accepted
    std::cout << boost::construe_cast<unsigned int, boost::construe::tag::hex>("0x23") << std::endl;

    // A no-throw construe_cast from integer to hexadecimal string
    std::cout << "0x" << boost::construe_cast<std::string, boost::construe::tag::hex>(42) << std::endl;
}
