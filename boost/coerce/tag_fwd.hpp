//              Copyright Jeroen Habraken 2012.
//
// Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file ../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COERCE_TAG_FWD_HPP
#define BOOST_COERCE_TAG_FWD_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace boost { namespace coerce { namespace tag {

    struct none;

    template <unsigned Radix>
    struct base;

    struct bin;

    struct oct;
    
    struct hex;

} } }  // namespace boost::coerce::tag

#endif  // BOOST_COERCE_TAG_FWD_HPP
