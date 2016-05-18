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
        using traits = typename CALLABLE_TRAITS_DISJUNCTION(
            bind_expression_traits<shallow_decay<T>>,
            function_object<T>,
            function<T>,
            pmf<T>,
            pmd<T>,
            function_object<T>
        )::traits;
    }
}

#endif
