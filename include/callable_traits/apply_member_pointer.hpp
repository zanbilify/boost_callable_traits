/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_APPLY_MEMBER_POINTER_HPP
#define CALLABLE_TRAITS_APPLY_MEMBER_POINTER_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    template<typename T, typename C>
    struct apply_member_pointer {
        using type = detail::fallback_if_invalid<
        typename detail::traits<T>::template apply_member_pointer<C>,
        typename std::remove_reference<T>::type C::*>;
    };

    template<typename T, typename C>
    using apply_member_pointer_t =
        typename apply_member_pointer<T, C>::type;
}

#endif
