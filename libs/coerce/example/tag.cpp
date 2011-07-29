//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/coerce.hpp>

#include <iostream>
#include <string>

int
main() {
    using namespace boost;
    
    // A coerce from hexadecimal string to integer -- "23", "0x23" as well as "0X23" are accepted ..
    std::cout << coerce::as<int>("0x23", coerce::tag::hex()) << std::endl;

    // .. and vice-versa
    std::cout
        << "0x"
        << coerce::as<std::string>(23, coerce::tag::hex()) << std::endl;
}
