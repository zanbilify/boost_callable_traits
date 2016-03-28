/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_BEST_MATCH_HPP
#define CALLABLE_TRAITS_BEST_MATCH_HPP

#include <callable_traits/tuple_sort.hpp>
#include <callable_traits/prepend.hpp>
#include <tuple>
#include <type_traits>

namespace callable_traits {
    
    namespace detail {
        template <template<class> class, typename...>
        struct filter_impl;

        template <template<class> class Pred>
        struct filter_impl<Pred> {
            using type = std::tuple<>;
        };

        template <template<class> class Pred, typename Head, typename ...Tail>
        struct filter_impl<Pred, Head, Tail...>
        {
            using type = typename std::conditional<Pred<Head>::value,
                typename prepend<Head, typename filter_impl<Pred, Tail...>::type>::type,
                typename filter_impl<Pred, Tail...>::type
            >::type;
        };

        template<template<class> class Pred, typename... Ts>
        using filter = typename filter_impl<Pred, Ts...>::type;

        template<typename T>
        struct can_convert {
            
            //todo - this should probably use std::is_convertible instead
            template<typename K>
            struct apply {
                
                struct bad{};
                
                template<typename U, typename Ret = decltype(std::declval<U>()(std::declval<T>()))>
                static Ret test(U);
                    
                template<typename>
                static bad test(...);
                
                using test_type = void(*)(K);
                using result = decltype(test<test_type>(test_type{}));
                
                static constexpr const bool value = !std::is_same<result, bad>::value;
            };  
        };

        template<typename T, typename Tup>
        struct conversion_result {
            using key = T;
            using successful_conversions = Tup;
            static constexpr const std::size_t count = std::tuple_size<Tup>::value;
        };

        template<typename T, typename... Ts>
        using map_conversions =
            conversion_result<T, filter<can_convert<T>::template apply, Ts...>>;

        template<typename T, typename U>
        struct conversion_result_sort_predicate {
            
            using candidate = typename T::key;
            using other = typename U::key;
            
            using no_ref = typename std::remove_reference<candidate>::type;
            using no_ref_other = typename std::remove_reference<other>::type;
            
            static constexpr bool const is_better_match = T::count > U::count;
            static constexpr bool const is_same_match = T::count == U::count;
            
            static constexpr bool const is_lref = std::is_lvalue_reference<candidate>::value;
            static constexpr bool const is_rref = std::is_rvalue_reference<candidate>::value;
            static constexpr bool const is_ref = is_lref || is_rref;
            static constexpr bool const is_const = std::is_const<no_ref>::value;
            
            static constexpr bool const is_other_lref = std::is_lvalue_reference<other>::value;
            static constexpr bool const is_other_rref = std::is_rvalue_reference<other>::value;
            static constexpr bool const is_other_ref = is_other_lref || is_other_rref;
            static constexpr bool const is_other_const = std::is_const<no_ref_other>::value;
            
            static constexpr bool const has_better_reference =
                (!is_ref && is_other_ref) || (is_lref && is_other_rref);
            
            static constexpr bool const has_same_reference =
                is_lref == is_other_lref && is_rref == is_other_rref;

            static constexpr bool const has_better_const = (is_const && !is_other_const);
            
            static constexpr bool const has_same_const =is_const == is_other_const;

            static constexpr const bool value =
                is_better_match
                || (is_same_match && has_better_reference)
                || (is_same_match && has_same_reference && has_better_const);
        };

        template<typename... Ts>
        using sorted_cartesian_product_of_conversions = tuple_sort<
            std::tuple<map_conversions<Ts, Ts...>...>,
            conversion_result_sort_predicate
        >;

        template<typename... Ts>
        using best_conversion_result =
            typename std::tuple_element<0, sorted_cartesian_product_of_conversions<Ts...>>::type;

        template<typename... Ts>
        using best_match = typename best_conversion_result<Ts...>::key;

        template<typename... Ts>
        using has_valid_match = std::integral_constant<bool,
            best_conversion_result<Ts...>::count == sizeof...(Ts)
        >;
    }
}

#endif