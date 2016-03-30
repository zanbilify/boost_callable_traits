/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_BUILD_FUNCTION_HPP
#define CALLABLE_TRAITS_DETAIL_BUILD_FUNCTION_HPP

#include <tuple>

namespace callable_traits {
    
    namespace detail {

        template<typename...>
        struct build_function_t;

        template<typename Return, typename... Args>
        struct build_function_t<Return, std::tuple<Args...>>{
            using type = Return(Args...);
        };

        template<typename Ret, typename Tup>
        using build_function = typename build_function_t<Ret, Tup>::type;
    }
}

#endif
