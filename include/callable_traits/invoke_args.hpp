/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_INVOKE_ARGS_HPP
#define CALLABLE_TRAITS_INVOKE_ARGS_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct invoke_args_error {

            static_assert(Sfinae,
                "Could not determine the parameters for "
                "T in callable_traits::args<T>. Note: "
                "If T is the type of a generic lambda or "
                " overloaded/templated function object, "
                "the parameters cannot be determined. ");
        };
    }

    namespace permissive {

        // returns callable_traits::invalid_type if parameter types
        // cannot be determined
        template<typename T>
        using invoke_args = typename detail::traits<T>::invoke_arg_types;
    }

    namespace verbose {

        template<typename T>
        using invoke_args = detail::fail_if_invalid<
            typename detail::traits<T>::invoke_arg_types,
            detail::invoke_args_error<false>>;
    }

    template<typename T>
    using invoke_args = detail::fail_if_invalid<
        typename detail::traits<T>::invoke_arg_types,
        detail::invoke_args_error<true>>;
}

#endif //#ifndef CALLABLE_TRAITS_INVOKE_ARGS_HPP
