/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_NEGATE_HPP
#define CALLABLE_TRAITS_DETAIL_NEGATE_HPP

#include <type_traits>

namespace callable_traits {
    
    namespace detail {

        template<typename BoolType>
        using negate = std::integral_constant<bool, !BoolType::value>;
    }
}

#endif
