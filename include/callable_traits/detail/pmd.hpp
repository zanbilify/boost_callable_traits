/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_PMD_HPP
#define CALLABLE_TRAITS_DETAIL_PMD_HPP

#include <type_traits>

#include <callable_traits/detail/fwd/function_object_fwd.hpp>
#include <callable_traits/detail/function.hpp>
#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/default_callable_traits.hpp>
#include <callable_traits/detail/utility.hpp>

namespace callable_traits {

    namespace detail {

        template<typename U, typename T>
        struct pmd : default_callable_traits {};

        template<typename U, typename T, T Value>
        struct pmd <U, std::integral_constant<T, Value>> {
            using traits = pmd<T, T>;
            static constexpr const bool value = traits::value;
        };

        template<typename OriginalType, typename D, typename T>
        struct pmd<OriginalType, D T::*>
            : default_callable_traits, qualifier_traits<dummy> {
                
            static constexpr bool value = true;

            using is_member_pointer = std::true_type;
            using traits = pmd;   
            using class_type = T;
            using invoke_type = T const &;
            using type = D T::*;
            using function_type = D(invoke_type);
            using qualified_function_type = D(invoke_type);
            using arg_types = std::tuple<invoke_type>;
            using invoke_arg_types = arg_types;
            using return_type = typename std::add_lvalue_reference<D>::type;
            using remove_member_pointer = D;

            template<typename C>
            using apply_member_pointer = typename copy_cvr<
                D C::*,
                OriginalType
            >::type;

            template<typename R>
            using apply_return = typename copy_cvr<
                R T::*,
                OriginalType
            >::type;
        };
    }
}

#endif
