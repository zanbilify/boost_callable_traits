 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_BIND_EXPRESSION_HPP
#define CALLABLE_TRAITS_IS_BIND_EXPRESSION_HPP

#include <callable_traits/fwd/bind_expression_fwd.hpp>

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct is_bind_expression {
            static constexpr const bool value = false;
        };

        template<typename Callable, typename... Args>
        struct is_bind_expression<bind_expression<Callable, Args...>> {
            static constexpr const bool value = true;
        };
    }
}

#endif
