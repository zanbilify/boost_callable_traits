/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_MEMBER_POINTER_HPP
#define CALLABLE_TRAITS_REMOVE_MEMBER_POINTER_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T>
    struct remove_member_pointer {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::remove_member_pointer,
            cannot_remove_member_pointer_from_this_type>;
    };

    template<typename T>
    using remove_member_pointer_t =
        typename remove_member_pointer<T>::type;
}

#endif
