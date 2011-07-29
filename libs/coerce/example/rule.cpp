//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_SPIRIT_NO_PREDEFINED_TERMINALS

#include <boost/coerce.hpp>
#include <boost/spirit/include/karma_uint.hpp>
#include <boost/spirit/include/karma_sequence.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/karma_rule.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_uint.hpp>
#include <boost/spirit/include/qi_sequence.hpp>
#include <boost/spirit/include/qi_rule.hpp>

#include <iostream>
#include <string>

namespace tag {
    using namespace boost;

    struct hexadecimal {
        template <typename Iterator, typename Target, typename Source>
        struct parser
            : spirit::qi::rule<Iterator, Target()> {
            parser(tag::hexadecimal const &)
                : spirit::qi::rule<Iterator, Target()>(
                        spirit::qi::lit_type()("0x")
                    >>  spirit::qi::hex_type()
                ) { }
        };

        template <typename Iterator, typename Target, typename Source>
        struct generator
            : spirit::karma::rule<Iterator, Source()> {
            generator(tag::hexadecimal const &)
                : spirit::karma::rule<Iterator, Source()>(
                        spirit::karma::lit_type()("0x")
                    <<  spirit::karma::hex_type()
                ) { }
        };
    };

}  // namespace tag

namespace boost { namespace coerce { namespace traits {

    template <typename T>
    struct reserve_size<T, ::tag::hexadecimal> {
        typedef std::size_t type;

        static inline type
        call(T const &, ::tag::hexadecimal const &) {
            return 2 + 8;
        }
    };

} } }  // namespace boost::coerce::traits

int
main() {
    using namespace boost;

    // A coerce from hexadecimal string to unsigned integer ..
    std::cout
        << coerce::as<unsigned int>("0x23", tag::hexadecimal()) << std::endl;

    // .. and vice-versa
    std::cout << coerce::as<std::string>(23u, tag::hexadecimal()) << std::endl;
}
