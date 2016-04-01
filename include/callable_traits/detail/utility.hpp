/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_UTILITY_HPP
#define CALLABLE_TRAITS_DETAIL_UTILITY_HPP

#include <type_traits>
#include <tuple>
#include <utility>

namespace callable_traits {

struct constants {
    static constexpr std::size_t arity_search_limit = 10;
};

struct invalid_type { invalid_type() = delete; };

struct unknown { unknown() = delete; };


    namespace detail {

        struct dummy {};

        struct substitution_failure{};

        template<std::size_t I, typename Tup>
        using at = typename std::tuple_element<I, Tup>::type;

        template<std::size_t I, typename Tup, typename = std::true_type>
        struct weak_at_t {
            using type = at<I, Tup>;
        };

        template<std::size_t I, typename Tup>
        struct weak_at_t<I, Tup, std::integral_constant<bool, I >= std::tuple_size<Tup>::value>>{
            using type = invalid_type;
        };

        template<std::size_t I, typename Tup>
        using weak_at = typename weak_at_t<I, Tup>::type;

        template<bool Value, typename T>
        struct value_type_pair {
            using type = T;
            static constexpr const bool value = Value;
        };

        template<typename T>
        using shallow_decay = typename std::remove_cv<
            typename std::remove_reference<T>::type
        >::type;

        template<typename...>
        struct conjunction
            : std::true_type {};

        template<typename T>
        struct conjunction<T>
            : T {};

        template<typename T, typename... Ts>
        struct conjunction<T, Ts...>
            : std::conditional<T::value != false, T, conjunction<Ts...>>::type { };

        template<typename...>
        struct disjunction
            : std::false_type {};

        template<typename T>
        struct disjunction<T>
            : T {};

        template<typename T, typename... Ts>
        struct disjunction<T, Ts...>
            : std::conditional<T::value != false, T, disjunction<Ts...>>::type { };

        template<typename BoolType>
        using negate = std::integral_constant<bool, !BoolType::value>;

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

        template<typename T, typename = std::true_type>
        struct unwrap_reference_t {
            using type = T;
        };

        template<typename T>
        struct unwrap_reference_t<T, is_reference_wrapper<T>> {
            using type = decltype(std::declval<T>().get());
        };

        template<typename T>
        using unwrap_reference = typename unwrap_reference_t<T>::type;

        template<typename T>
        struct is_integral_constant_t {
            static constexpr bool value = false;
        };

        template<typename T, T Value>
        struct is_integral_constant_t<std::integral_constant<T, Value>> {
            static constexpr bool value = true;
        };

        template<typename T>
        using is_integral_constant = std::integral_constant<bool,
            is_integral_constant_t<shallow_decay<T>>::value>;

        template<typename Check, typename Result>
        using if_integral_constant =
            typename std::enable_if<is_integral_constant<Check>::value, Result>::type;

        template<typename Check, typename Result>
        using if_not_integral_constant =
            typename std::enable_if<!is_integral_constant<Check>::value, Result>::type;

        template<typename T, typename Class>
        using add_member_pointer = T Class::*;

        template<typename T>
        struct remove_member_pointer_t {
            using type = T;
        };

        template<typename T, typename U>
        struct remove_member_pointer_t<T U::*>{
            using type = T;
        };

        template<typename T>
        using remove_member_pointer =
            typename remove_member_pointer_t<T>::type;

        template<typename T, typename U = shallow_decay<T>>
        using is_constexpr_constructible = std::integral_constant<bool,
            std::is_literal_type<U>::value && std::is_default_constructible<U>::value
        >;

        template<typename...>
        struct build_function_t;

        template<typename Return, typename... Args>
        struct build_function_t<Return, std::tuple<Args...>>{
            using type = Return(Args...);
        };

        template<typename Ret, typename Tup>
        using build_function = typename build_function_t<Ret, Tup>::type;

        template <typename...> struct prepend;

        template <> struct prepend<> {
            using type = std::tuple<>;
        };

        template <typename T, typename... Args>
        struct prepend<T, std::tuple<Args...> > {
            using type = std::tuple<T, Args...>;
        };

        /*template <typename T, typename... Args>
        struct prepend<T, private_tuple<Args...> > {
            using type = private_tuple<T, Args...>;
        };*/
    }
}

#endif
