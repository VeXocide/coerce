//              Copyright Jeroen Habraken 2010.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/construe_cast.hpp>

#include <iostream>
#include <ostream>

int main(int argc, char** argv) {
    std::cout << boost::construe_cast<int>("23") << std::endl
              << boost::construe_cast<unsigned int, boost::construe::tag::hex>("2c") << std::endl
              << boost::construe_cast<int>("XXX", 42) << std::endl;
}
