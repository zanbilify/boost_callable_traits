/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_FUNCTION_OBJECT_HPP
#define CALLABLE_TRAITS_DETAIL_FUNCTION_OBJECT_HPP

#include <callable_traits/detail/pmf.hpp>
#include <callable_traits/detail/default_callable_traits.hpp>
#include <callable_traits/detail/fwd/function_fwd.hpp>
#include <callable_traits/detail/fwd/function_object_fwd.hpp>
#include <callable_traits/detail/utility.hpp>

#include <tuple>

CALLABLE_TRAITS_DETAIL_NAMESPACE_BEGIN

        template<typename T, typename Base>
        struct function_object : Base {

            using type = T;

            using function_type = typename Base::function_object_signature;

            using arg_types = typename Base::non_invoke_arg_types;
            using non_invoke_arg_types = arg_types;

            static constexpr const bool value = std::is_class<T>::value;

            using traits = function_object;
            using class_type = invalid_type;
            using invoke_type = invalid_type;

            using remove_varargs = invalid_type;

            using add_varargs = invalid_type;

            using is_transaction_safe = typename Base::is_transaction_safe;

            using add_transaction_safe = invalid_type;

            using remove_transaction_safe = invalid_type;

            using clear_args = invalid_type;

            template<template<class...> class Container>
            using expand_args = typename function<function_type>::template
                expand_args<Container>;

            template<template<class...> class Container, typename... RightArgs>
            using expand_args_left = typename function<function_type>::template
                expand_args_left<Container, RightArgs...>;

            template<template<class...> class Container, typename... LeftArgs>
            using expand_args_right = typename function<function_type>::template
                expand_args_right<Container, LeftArgs...>;

            template<typename C, typename U = T>
            using apply_member_pointer =
                typename std::remove_reference<U>::type C::*;

            template<typename>
            using apply_return = invalid_type;

            template<typename...>
            using push_front = invalid_type;
            
            template<typename...>
            using push_back = invalid_type;
            
            template<std::size_t ElementCount>
            using pop_args_front = invalid_type;

            template<std::size_t ElementCount>
            using pop_args_back = invalid_type;
            
            template<std::size_t Index, typename... NewArgs>
            using insert_args = invalid_type;
            
            template<std::size_t Index, std::size_t Count>
            using remove_args = invalid_type;

            template<std::size_t Index, typename... NewArgs>
            using replace_args = invalid_type;

            template<std::size_t Count>
            using pop_front = invalid_type;

            template<std::size_t Count>
            using pop_back = invalid_type;

            using remove_member_reference = invalid_type;
            using add_member_lvalue_reference = invalid_type;
            using add_member_rvalue_reference = invalid_type;
            using add_member_const = invalid_type;
            using add_member_volatile = invalid_type;
            using add_member_cv = invalid_type;
            using remove_member_const = invalid_type;
            using remove_member_volatile = invalid_type;
            using remove_member_cv = invalid_type;
        };

        template<typename T, typename U, typename Base>
        struct function_object <T U::*, Base>
            : default_callable_traits<> {};

CALLABLE_TRAITS_DETAIL_NAMESPACE_END

#endif
