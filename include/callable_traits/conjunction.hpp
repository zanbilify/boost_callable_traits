/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CONJUNCTION_HPP
#define CALLABLE_TRAITS_CONJUNCTION_HPP

#include <type_traits>

namespace callable_traits {

    namespace ctdetail {

        template<typename...>
        struct conjunction
            : std::true_type {};

        template<typename T>
        struct conjunction<T>
            : T {};

        template<typename T, typename... Ts>
        struct conjunction<T, Ts...>
            : std::conditional_t<T::value != false, T, conjunction<Ts...>> { };
    }
}

#endif