/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_REFERNCE_IF_PTR_HPP
#define CALLABLE_TRAITS_REMOVE_REFERNCE_IF_PTR_HPP

#include <type_traits>

namespace callable_traits {

    namespace detail {

        template<typename T>
        using remove_reference_if_ptr = typename std::conditional<
            std::is_pointer<typename std::remove_reference<T>::type>::value,
            typename std::remove_reference<T>::type,
            T
        >::type;
    }
}

#endif