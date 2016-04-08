/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_APPLY_RETURN_HPP
#define CALLABLE_TRAITS_APPLY_RETURN_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace permissive {

        template<typename T, typename C>
        using apply_return =
            typename detail::traits<T>::template apply_return<C>;
    }

    namespace detail {

        template<bool Sfinae>
        struct apply_return_error {

            static_assert(Sfinae,
                "callable_traits::apply_return<T> is "
                "not a meaningful operation for this T.");
        };

        template<typename T, typename C, bool Sfinae>
        using apply_return_t = fail_if_invalid<
            typename permissive::apply_return<T, C>,
            apply_return_error<Sfinae>>;
    }

    namespace verbose {

        template<typename T, typename C>
        using apply_return =
            detail::apply_return_t<T, C, false>;
    }

    template<typename T, typename C>
    using apply_return =
        detail::apply_return_t<T, C, true>;
}

#endif
