/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_COPY_QUALIFIERS_HPP
#define CALLABLE_TRAITS_COPY_QUALIFIERS_HPP

#include <callable_traits/detail/required_definitions.hpp>
#include <callable_traits/detail/copy_qualifiers_impl.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct copy_qualifiers_error {

            static_assert(Sfinae,
                "TODO: error message for callable_traits::copy_qualifiers");
        };
    }

    namespace permissive {

        // returns callable_traits::invalid_type if parameter types
        // cannot be determined
        template<typename To, typename From>
        using copy_qualifiers =
			typename detail::copy_qualifiers_impl<detail::traits<To>, detail::traits<From>>::type;
    }

    namespace verbose {

        template<typename To, typename From>
        using copy_qualifiers = detail::fail_if_invalid<
            typename detail::copy_qualifiers_impl<detail::traits<To>, detail::traits<From>>::type,
            detail::invoke_args_error<false>>;
    }

    template<typename To, typename From>
    using copy_qualifiers = detail::fail_if_invalid<
        typename detail::copy_qualifiers_impl<detail::traits<To>, detail::traits<From>>::type,
        detail::invoke_args_error<true>>;
}

#endif //#ifndef CALLABLE_TRAITS_COPY_QUALIFIERS_HPP
