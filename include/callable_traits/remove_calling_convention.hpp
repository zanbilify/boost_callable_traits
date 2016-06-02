/*
@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_CALLING_CONVENTION_HPP
#define CALLABLE_TRAITS_REMOVE_CALLING_CONVENTION_HPP

#include <callable_traits/detail/calling_conventions.hpp>
#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct remove_calling_convention_error : sfinae_error {

            static_assert(Sfinae,
                "Unable to remove calling convention from type T in"
                "callable_traits::remove_calling_convention.");
        };
    }

    template<typename T>
    using remove_calling_convention = detail::fail_if_invalid<
        typename detail::traits<T>::remove_calling_convention,
        detail::remove_calling_convention_error<true>>;
}

#endif //CALLABLE_TRAITS_REMOVE_CALLING_CONVENTION_HPP
