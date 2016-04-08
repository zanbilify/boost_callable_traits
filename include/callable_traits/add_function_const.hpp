/*!
@file add_function_const

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_FUNCTION_CONST_HPP
#define CALLABLE_TRAITS_ADD_FUNCTION_CONST_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace permissive {

        template<typename T>
        using add_function_const =
            typename detail::traits<T>::add_function_const;
    }

    namespace detail {

        template<bool Sfinae>
        struct add_function_const_error {

            static_assert(Sfinae,
                "callable_traits::add_function_const<T> "
                "is not a meaningful operation for this T.");
        };

        template<typename T, bool Sfinae>
        using add_function_const_t = fail_if_invalid<
            permissive::add_function_const<T>,
            add_function_const_error<Sfinae>>;
    }

    namespace verbose {

        template<typename T>
        using add_function_const =
            detail::add_function_const_t<T, false>;
    }

    template<typename T>
    using add_function_const =
        detail::add_function_const_t<T, true>;
}

#endif
