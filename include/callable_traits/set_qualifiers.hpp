/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_SET_QUALIFIERS_HPP
#define CALLABLE_TRAITS_SET_QUALIFIERS_HPP

#include <callable_traits/detail/set_qualifiers_impl.hpp>
#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T, flags Flags>
    struct set_qualifiers {
        using type = typename detail::set_qualifiers_impl<T, Flags>::type;
    };

    template<typename T, flags Flags>
    using set_qualifiers_t = typename set_qualifiers<T, Flags>::type;
}

#endif //#ifndef CALLABLE_TRAITS_SET_QUALIFIERS_HPP
