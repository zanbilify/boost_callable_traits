/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_AT_HPP
#define CALLABLE_TRAITS_DETAIL_AT_HPP

#include <callable_traits/detail/disjunction.hpp>
#include <tuple>
#include <functional>

namespace callable_traits {
    
    namespace detail {

        template<std::size_t I, typename Tup>
        using at = typename std::tuple_element<I, Tup>::type;

        template<std::size_t I, typename Tup, typename = std::true_type>
        struct weak_at_t {
            using type = at<I, Tup>;
        };

        template<std::size_t I, typename Tup>
        struct weak_at_t<I, Tup, std::integral_constant<bool, I >= std::tuple_size<Tup>::value>>{
            using type = invalid_type;
        };

        template<std::size_t I, typename Tup>
        using weak_at = typename weak_at_t<I, Tup>::type;

    }
}

#endif
