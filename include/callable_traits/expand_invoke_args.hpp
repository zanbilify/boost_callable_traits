/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_EXPAND_INVOKE_ARGS_HPP
#define CALLABLE_TRAITS_EXPAND_INVOKE_ARGS_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct expand_invoke_args_error {

            static_assert(Sfinae,
                "callable_traits::expand_invoke_args<T, U> is not a valid operation.");
        };
    }

    namespace permissive {

        // returns callable_traits::invalid_type if argument types cannot be determined
        template<typename T, template<class...> class Container>
        using expand_invoke_args = typename detail::traits<T>::template expand_invoke_args<Container>;
    }

    namespace verbose {

        template<typename T, template<class...> class Container>
        using expand_invoke_args = detail::fail_if_invalid<
            typename detail::traits<T>::template expand_invoke_args<Container>,
            detail::expand_invoke_args_error<false>>;
    }

    template<typename T, template<class...> class Container>
    using expand_invoke_args = detail::fail_if_invalid<
        typename detail::traits<T>::template expand_invoke_args<Container>,
        detail::expand_invoke_args_error<true>>;
}

#endif //#ifndef CALLABLE_TRAITS_EXPAND_INVOKE_ARGS_HPP
