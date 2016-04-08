/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FUNCTION_TYPE_HPP
#define CALLABLE_TRAITS_FUNCTION_TYPE_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace permissive {

        template<typename T>
        using function_type =
            typename detail::traits<T>::function_type;
    }

    namespace detail {

        template<bool Sfinae>
        struct function_type_error {

            static_assert(Sfinae,
                "Unable to derive a function type from "
                "T in callable_traits::function_type<T>.");
        };

        template<typename T, bool Sfinae>
        using function_type_t = fail_if_invalid<
            permissive::function_type<T>,
            function_type_error<Sfinae>>;
    }
	
    namespace verbose {

        template<typename T>
        using function_type =
            detail::function_type_t<T, false>;
    }

    template<typename T>
    using function_type =
        detail::function_type_t<T, true>;
}

#endif
