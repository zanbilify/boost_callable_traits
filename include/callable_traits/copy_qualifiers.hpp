/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_COPY_QUALIFIERS_HPP
#define CALLABLE_TRAITS_COPY_QUALIFIERS_HPP

#include <callable_traits/detail/core.hpp>
#include <callable_traits/detail/copy_qualifiers_impl.hpp>

namespace callable_traits {

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(copy_qualifiers)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_FOR(copy_qualifiers,
        cannot_copy_qualifiers_for_these_types)

    template<typename To, typename From>
    struct copy_qualifiers {

        using type = detail::fail_if_invalid<
            typename detail::copy_qualifiers_impl<
                detail::traits<To>, detail::traits<From>>::type,
            cannot_copy_qualifiers_for_these_types>;
    };

    template<typename To, typename From>
    using copy_qualifiers_t =
        typename copy_qualifiers<To, From>::type;
}

#endif //#ifndef CALLABLE_TRAITS_COPY_QUALIFIERS_HPP
