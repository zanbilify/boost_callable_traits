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

#define CALLABLE_TRAITS_VARARGS_CC

#ifdef _MSC_VER
#ifndef __clang__
#undef CALLABLE_TRAITS_VARARGS_CC
#define CALLABLE_TRAITS_VARARGS_CC __cdecl
#define CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED
#define CALLABLE_TRAITS_MSVC
#endif //ifndef __clang__
#endif //_MSC_VER


#if defined(__GNUC__) || defined(__clang__)
// libstdc++ did not implement std::is_trivially_default_constructible 
// until GCC 5. It's difficult to check for this reliably, especially in
// Clang, so I use a compiler hook instead.
#define CALLABLE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE(T) \
    (std::is_default_constructible<T>::value && __has_trivial_constructor(T))
#else
#define CALLABLE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE(T) \
    std::is_trivially_default_constructible<T>::value
#endif //if defined(__GLIBCXX__) && (defined(__GNUC__) || defined(__clang__))

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
