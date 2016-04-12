/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_FWD_FUNCTION_FWD_HPP
#define CALLABLE_TRAITS_DETAIL_FWD_FUNCTION_FWD_HPP

namespace callable_traits {

    namespace detail {

        template<typename T>
        using decay_if_ptr_or_integral_constant = typename std::conditional<
            std::is_pointer<typename std::remove_reference<T>::type>::value
                || is_integral_constant<T>::value,
            shallow_decay<T>,
            T
        >::type;

        template<typename T>
        struct function;

    }
}

#endif
