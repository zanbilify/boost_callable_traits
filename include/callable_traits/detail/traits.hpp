/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_TRAITS_HPP
#define CALLABLE_TRAITS_DETAIL_TRAITS_HPP

#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/fwd/pmd_fwd.hpp>
#include <callable_traits/detail/fwd/pmf_fwd.hpp>
#include <callable_traits/detail/fwd/function_fwd.hpp>
#include <callable_traits/detail/fwd/function_object_fwd.hpp>
#include <callable_traits/detail/bind_expression_traits.hpp>
#include <type_traits>

namespace callable_traits {

    namespace detail {

        template<typename T>
        using decay_if_ptr_or_integral_constant = typename std::conditional<
            std::is_pointer<typename std::remove_reference<T>::type>::value
            || is_integral_constant<T>::value,
            shallow_decay<T>,
            T
        >::type;

        template<typename T, typename Decayed = shallow_decay<T>>
        using traits = typename disjunction<
            bind_expression_traits<Decayed>,
            function_object<T>,
            function<T, decay_if_ptr_or_integral_constant<T>>,
            pmf<T>,
            pmd<T, shallow_decay<T>>,
            function_object<Decayed>
        >::traits;
    }
}

#endif
