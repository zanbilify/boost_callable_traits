 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_ARITY_HPP
#define CALLABLE_TRAITS_DETAIL_ARITY_HPP

#include <callable_traits/detail/test_invoke.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/template_worm.hpp>
#include <callable_traits/config.hpp>
#include <cstdint>
#include <type_traits>

namespace callable_traits {

    namespace detail {

        template<typename, typename>
        struct max_args {
            static constexpr bool value = true;
            static constexpr int arg_count = -1;
        };

        template<typename U>
        struct max_args<U, CALLABLE_TRAITS_IX_SEQ(0)> {
            static constexpr bool value = true;
            static constexpr int arg_count =
                is_invokable<U, const template_worm<0> &>::value ? 1 : (
                    is_invokable<U, void>::value ? 0 : -1
                );
        };

        template<typename U, std::size_t... I>
        struct max_args<U, CALLABLE_TRAITS_IX_SEQ(I...)> {

            using result_type = CALLABLE_TRAITS_DISJUNCTION(
                is_invokable<U, const template_worm<I>&...>,
                max_args<U, CALLABLE_TRAITS_MAKE_IX_SEQ(sizeof...(I)-1) >
            );

            static constexpr bool value = result_type::value;
            static constexpr int arg_count = result_type::arg_count;
        };

        template<typename U, std::size_t Max, typename = int>
        struct min_args;

        struct sentinel {};

        template<typename U, std::size_t Max>
        struct min_args<U, Max, sentinel> {
            static constexpr bool value = true;
            static constexpr int arg_count = -1;
        };

        template<typename U, std::size_t Max, std::size_t... I>
        struct min_args<U, Max, CALLABLE_TRAITS_IX_SEQ(I...)> {

            using next = typename std::conditional<
                sizeof...(I)+1 <= Max,
                CALLABLE_TRAITS_MAKE_IX_SEQ(sizeof...(I)+1),
                sentinel
            >::type;

            using result_type = CALLABLE_TRAITS_DISJUNCTION(
                is_invokable<U, const template_worm<I>&...>,
                min_args<U, Max, next>
            );

            static constexpr bool value = result_type::value;
            static constexpr int arg_count = result_type::arg_count;
        };

        template<typename U, std::size_t Max>
        struct min_args<U, Max, void> {

            using result_type = CALLABLE_TRAITS_DISJUNCTION(
                is_invokable<U, void>,
                min_args<U, Max, CALLABLE_TRAITS_MAKE_IX_SEQ(1)>
            );

            static constexpr int arg_count = result_type::arg_count;
            static constexpr bool value = result_type::value;
        };

        template<typename T>
        struct arg_tuple_size {
            static constexpr int value = -1;
        };

        template<typename... T>
        struct arg_tuple_size<std::tuple<T...>> {
            static constexpr int value = sizeof...(T);
        };
       
        template<typename T, std::size_t SearchLimit = 10>
        struct function_object_min_arity {

            static constexpr int precient_arity = arg_tuple_size<
                typename T::arg_types
            >::value;

            static constexpr int tentative_min_arity = min_args<
                T, SearchLimit, void
            >::arg_count;

            static constexpr int value =
                precient_arity == -1
                || (tentative_min_arity < precient_arity && tentative_min_arity >= 0)
                ? tentative_min_arity : precient_arity;
        };

        template<typename T, std::size_t SearchLimit>
        struct function_object_max_arity {

            static constexpr int precient_arity = arg_tuple_size<
                typename T::arg_types
            >::value;

            static constexpr int tentative_max_arity = max_args<
                T, CALLABLE_TRAITS_MAKE_IX_SEQ(SearchLimit)
            >::arg_count;

            static constexpr int value =
                precient_arity == -1 || tentative_max_arity > precient_arity
                ? tentative_max_arity : precient_arity;
        };

        template<typename Traits>
        using arity_t = std::integral_constant<int,
            arg_tuple_size<typename Traits::arg_types>::value
        >;

        template<typename Traits, std::size_t SearchLimit>
        using min_arity_t = std::integral_constant<int,
            std::conditional<
                Traits::is_function_object::value,
                function_object_min_arity<Traits, SearchLimit>,
                arg_tuple_size<typename Traits::arg_types>
            >::type::value
        >;

        template<typename Traits, std::size_t SearchLimit>
        using max_arity_t = std::integral_constant<int,
            std::conditional<
                Traits::is_function_object::value,
                function_object_max_arity<Traits, SearchLimit>,
                arg_tuple_size<typename Traits::arg_types>
            >::type::value
        >;
    }
}

#endif
