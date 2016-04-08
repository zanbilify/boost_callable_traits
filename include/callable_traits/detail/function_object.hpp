/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_FUNCTION_OBJECT_HPP
#define CALLABLE_TRAITS_DETAIL_FUNCTION_OBJECT_HPP

#include <callable_traits/detail/generalized_class.hpp>
#include <callable_traits/detail/pmf.hpp>
#include <callable_traits/detail/utility.hpp>

#include <tuple>

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct has_normal_call_operator
        {
            template<typename N, N Value> struct check { check(std::nullptr_t) {} };

            template<typename U>
            static std::int8_t test(check<decltype(&U::operator()), &U::operator()>);

            template<typename>
            static std::int16_t test(...);
                 
            static constexpr bool value = sizeof(test<T>(nullptr)) == sizeof(std::int8_t);
            
        };
        
        struct callable_dummy {
            void operator()() {}
        };

        template<typename T>
        using default_normal_callable = typename std::conditional<
            has_normal_call_operator<T>::value,
            T,
            callable_dummy
        >::type;
        
        template<typename General>
        struct ambiguous_function_object {
            using arg_types = invalid_type;
            using return_type = invalid_type;
            using has_varargs = std::false_type;
            using function_type = invalid_type;
            using function_object_type = function_type;
        };

        template<typename General>
        struct function_object
            : std::conditional<
                has_normal_call_operator<typename General::type>::value,
                pmf<decltype(&default_normal_callable<typename General::type>::operator())>,
                ambiguous_function_object<General>
            >::type {

            using base = typename std::conditional<
                has_normal_call_operator<typename General::type>::value,
                pmf<decltype(&default_normal_callable<typename General::type>::operator())>,
                ambiguous_function_object<General>
            >::type;

            using type = typename General::original_type;
            using general_type = typename General::type;
            using function_type = typename base::function_object_type;
            using invoke_arg_types = typename base::arg_types;

            static constexpr const bool value =
                std::is_class<type>::value && !is_integral_constant<type>::value;

            using is_ambiguous = std::integral_constant<bool,
                !has_normal_call_operator<general_type>::value>;

            using traits = function_object;
            using class_type = invalid_type;
            using invoke_type = invalid_type;

            using is_function_object = std::integral_constant<bool,
                std::is_class<general_type>::value>;

            using is_member_pointer = std::false_type;
            using is_member_function_pointer = std::false_type;
            using is_function_reference = std::false_type;
            using is_function_pointer = std::false_type;
            using is_function = std::false_type;
            using is_function_general = std::false_type;
            using remove_member_pointer = type;
            using remove_varargs = invalid_type;
            using add_varargs = invalid_type;

            template<typename>
            using apply_member_pointer = invalid_type;

            template<typename>
            using apply_return = invalid_type;

            using remove_reference = type;
            using add_lvalue_reference = type;
            using add_rvalue_reference = type;
            using add_const = type;
            using add_volatile = type;
            using add_cv = type;
            using remove_const = type;
            using remove_volatile = type;
            using remove_cv = type;
        };

        template<typename T, typename U>
        struct function_object <generalized_class<T U::*> > {
            static constexpr const bool value = false;
            using traits = function_object;
        };
    }
}

#endif
