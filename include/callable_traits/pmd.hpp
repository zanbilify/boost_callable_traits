/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_PMD_HPP
#define CALLABLE_TRAITS_PMD_HPP

#include <type_traits>

#include <callable_traits/fwd/function_object_fwd.hpp>
#include <callable_traits/function.hpp>
#include <callable_traits/traits.hpp>
#include <callable_traits/member_pointer_utilities.hpp>

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct pmd : std::false_type {
            static constexpr const bool is_ambiguous = true;
            using traits = pmd;
        };

        namespace msvc_workaround {
            template<typename Traits, typename Ret>
            using apply_return_helper =
                typename Traits::template apply_return<Ret>;
        }

        template<typename D, typename T>
        struct pmd<D T::*>
            : traits<D> {
                
            static constexpr bool value = true;

            using is_member_pointer = std::true_type;
            using is_function_object = std::false_type;
            using is_member_function_pointer = typename detail::traits<D>::is_function;
            using is_function_reference = std::false_type;
            using is_function_pointer = std::false_type;
            using is_function = std::false_type;
            using is_function_general = std::false_type;
            using traits = pmd;   
            using class_type = T;
            using invoke_type = T;
            using base = detail::traits<D>;

            using remove_member_pointer = D;

            using remove_reference = invalid_type;
            using add_lvalue_reference = invalid_type;
            using add_rvalue_reference = invalid_type;
            using add_const = invalid_type;
            using add_volatile = invalid_type;
            using add_cv = invalid_type;
            using remove_const = invalid_type;
            using remove_volatile = invalid_type;
            using remove_cv = invalid_type;

            template<typename>
            using apply_return = invalid_type;
        };
    }
}

#endif