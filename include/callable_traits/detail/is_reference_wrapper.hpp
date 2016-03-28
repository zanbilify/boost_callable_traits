/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_IS_REFERENCE_WRAPPER_HPP
#define CALLABLE_TRAITS_DETAIL_IS_REFERENCE_WRAPPER_HPP

#include <callable_traits/detail/can_dereference.hpp>
#include <type_traits>
#include <memory>


namespace callable_traits {

    namespace detail {

        template<typename T>
        struct is_reference_wrapper_t {
            using type = std::false_type;
        };

        template<typename T>
        struct is_reference_wrapper_t<std::reference_wrapper<T>> {
            using type = std::true_type;
        };

        template<typename T>
        using is_reference_wrapper = typename is_reference_wrapper_t<shallow_decay<T>>::type;
    }
}

#endif