/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_NO_SFINAE_REMOVE_MEMBER_POINTER_HPP
#define CALLABLE_TRAITS_NO_SFINAE_REMOVE_MEMBER_POINTER_HPP

#include <callable_traits/detail/traits.hpp>

namespace callable_traits {

    namespace no_sfinae {

        template<typename T>
        using remove_member_pointer =
            typename detail::traits<T>::remove_member_pointer;
    }
}

#endif
