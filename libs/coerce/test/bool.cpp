//              Copyright Jeroen Habraken 2011.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file ../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_TEST_MODULE bool

#include <boost/coerce.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(source) {
    using namespace boost;

    BOOST_CHECK_EQUAL(coerce::as<std::string>(true), "true");
    BOOST_CHECK_EQUAL(coerce::as<std::string>(false), "false");
}

BOOST_AUTO_TEST_CASE(target) {
    using namespace boost;

    BOOST_CHECK_THROW(coerce::as<bool>(""), coerce::bad_cast);

    BOOST_CHECK_EQUAL(coerce::as<bool>("true"), true);
    BOOST_CHECK_EQUAL(coerce::as<bool>("false"), false);

    BOOST_CHECK_THROW(coerce::as<bool>("trueX"), coerce::bad_cast);
    BOOST_CHECK_THROW(coerce::as<bool>("XXX"), coerce::bad_cast);
}

/*  lexical_cast

    BOOST_CHECK_EQUAL(true, lexical_cast<bool>('1'));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>('0'));
    BOOST_CHECK_THROW(lexical_cast<bool>('A'), bad_lexical_cast);
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(1));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(0));
    BOOST_CHECK_THROW(lexical_cast<bool>(123), bad_lexical_cast);
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(1.0));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(0.0));
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(true));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(false));
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>("1"));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>("0"));
    BOOST_CHECK_THROW(lexical_cast<bool>(""), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<bool>("Test"), bad_lexical_cast);
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>("1"));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>("0"));
    BOOST_CHECK_EQUAL(true, lexical_cast<bool>(std::string("1")));
    BOOST_CHECK_EQUAL(false, lexical_cast<bool>(std::string("0")));

    BOOST_CHECK_THROW(lexical_cast<bool>(1.0001L), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<bool>(2), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<bool>(2u), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<bool>(-1), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<bool>(-2), bad_lexical_cast);


    BOOST_CHECK_THROW(
        lexical_cast<bool>(std::string("")), bad_lexical_cast);
    BOOST_CHECK_THROW(
        lexical_cast<bool>(std::string("Test")), bad_lexical_cast);

    BOOST_CHECK(lexical_cast<bool>("+1") == true );
    BOOST_CHECK(lexical_cast<bool>("+0") == false );
    BOOST_CHECK(lexical_cast<bool>("-0") == false );
    BOOST_CHECK_THROW(lexical_cast<bool>("--0"), bad_lexical_cast);
    BOOST_CHECK_THROW(lexical_cast<bool>("-+-0"), bad_lexical_cast);
*/

/*  convert

    convert<bool>::result bool_res1 = convert<bool>::from("1",     false);
    convert<bool>::result bool_res2 = convert<bool>::from("true",  false);
    convert<bool>::result bool_res3 = convert<bool>::from("yes",   false);
    convert<bool>::result bool_res4 = convert<bool>::from(L"1",    false);
    convert<bool>::result bool_res5 = convert<bool>::from(L"true", false);
    convert<bool>::result bool_res6 = convert<bool>::from(L"yes",  false);
    convert<bool>::result bool_res7 = convert<bool>::from("junk",   true);

    BOOST_ASSERT( bool_res1 && bool_res1.value() == true);
    BOOST_ASSERT( bool_res2 && bool_res2.value() == true);
    BOOST_ASSERT( bool_res3 && bool_res3.value() == true);
    BOOST_ASSERT( bool_res4 && bool_res4.value() == true);
    BOOST_ASSERT( bool_res5 && bool_res5.value() == true);
    BOOST_ASSERT( bool_res6 && bool_res6.value() == true);
    BOOST_ASSERT(!bool_res7 && bool_res7.value() == true);

    string bool_str1 = convert<string>::from(true,  "failed");
    string bool_str2 = convert<string>::from(false, "failed");
    string bool_str3 = convert<string>::from(1,     "failed");
    string bool_str4 = convert<string>::from(0,     "failed");

    BOOST_ASSERT(bool_str1 == "1");
    BOOST_ASSERT(bool_str2 == "0");
    BOOST_ASSERT(bool_str3 == "1");
    BOOST_ASSERT(bool_str4 == "0");
*/
