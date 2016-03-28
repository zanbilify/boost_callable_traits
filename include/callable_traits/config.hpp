/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CONFIG_HPP
#define CALLABLE_TRAITS_CONFIG_HPP

#define CALLABLE_TRAITS_EMPTY_
#define CALLABLE_TRAITS_EMPTY CALLABLE_TRAITS_EMPTY_

#ifdef _MSC_VER
#define CALLABLE_TRAITS_VARARGS_CC __cdecl
#else
#define CALLABLE_TRAITS_VARARGS_CC
#endif //_MSC_VER

#include <utility>

namespace callable_traits {

    namespace detail {

        struct dummy {};

        template<bool Value, typename T> 
        struct value_type_pair {
            using type = T;
            static constexpr const bool value = Value;
        };
    }
    
    struct constants {
        static constexpr std::size_t arity_search_limit = 10;
    };

    struct invalid_type { invalid_type() = delete; };
    struct unknown { unknown() = delete; };
}

#endif
