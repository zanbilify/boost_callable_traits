/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_QUALIFIED_PARENT_CLASS_OF_HPP
#define CALLABLE_TRAITS_QUALIFIED_PARENT_CLASS_OF_HPP

#include <callable_traits/detail/core.hpp>

namespace callable_traits {

    template<typename T>
    struct qualified_parent_class_of {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::invoke_type,
            type_is_not_a_member_pointer>;
    };

    template<typename T>
    using qualified_parent_class_of_t =
        typename qualified_parent_class_of<T>::type;
}

#endif //#ifndef CALLABLE_TRAITS_QUALIFIED_PARENT_CLASS_OF_HPP
