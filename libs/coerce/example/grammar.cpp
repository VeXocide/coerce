//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/coerce.hpp>
#include <boost/spirit/include/karma_grammar.hpp>
#include <boost/spirit/include/karma_uint.hpp>
#include <boost/spirit/include/karma_sequence.hpp>
#include <boost/spirit/include/karma_string.hpp>
#include <boost/spirit/include/qi_grammar.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_uint.hpp>
#include <boost/spirit/include/qi_sequence.hpp>

#include <iostream>
#include <limits>
#include <string>

namespace tag {
    using namespace boost;

    struct hexadecimal {
        template <typename Iterator, typename Target, typename Source>
        struct parser
            : spirit::qi::grammar<Iterator, Target()> {
            parser(tag::hexadecimal const &)
                : parser::base_type(start) {
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
                start =     spirit::qi::lit("0x")
                        >>  spirit::qi::hex;
#else
                start =     spirit::qi::lit_type()("0x")
                        >>  spirit::qi::hex_type();
#endif
                }

            spirit::qi::rule<Iterator, Target()> start;
        };

        template <typename Iterator, typename Target, typename Source>
        struct generator
            : spirit::karma::grammar<Iterator, Source()> {
            generator(tag::hexadecimal const &)
                : generator::base_type(start) {
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
                start =     spirit::karma::lit("0x")
                        <<  spirit::karma::hex;
#else
                start =     spirit::karma::lit_type()("0x")
                        <<  spirit::karma::hex_type();
#endif
            }

            spirit::karma::rule<Iterator, Source()> start;
        };
    };

}  // namespace tag

namespace boost { namespace coerce { namespace traits {

    template <typename T>
    struct reserve_size<T, ::tag::hexadecimal> {
        typedef std::size_t type;

        static inline type
        call(T const &, ::tag::hexadecimal const &) {
            return 2 + std::numeric_limits<unsigned int>::digits / 4;
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
