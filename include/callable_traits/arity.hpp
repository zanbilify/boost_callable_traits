 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ARITY_HPP
#define CALLABLE_TRAITS_ARITY_HPP

#include <callable_traits/disjunction.hpp>
#include <callable_traits/can_invoke_t.hpp>
#include <callable_traits/any_arg.hpp>
#include <cstdint>

namespace callable_traits {

    namespace ctdetail {

        template<typename, typename>
        struct max_args {
            static constexpr bool value = true;
            static constexpr int arg_count = -1;
        };

        template<typename U>
        struct max_args<U, std::index_sequence<0>> {
            static constexpr bool value = true;
            static constexpr int arg_count =
                can_invoke_t<U, const any_arg<0> &>::value ? 1 : (
                    can_invoke_t<U, void>::value ? 0 : -1
                );
        };

        template<typename U, std::size_t... I>
        struct max_args<U, std::index_sequence<I...>> {

            using result_type = disjunction<
                can_invoke_t<U, const any_arg<I>&...>,
                max_args<U, std::make_index_sequence<sizeof...(I)-1> >
            >;

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
        struct min_args<U, Max, std::index_sequence<I...>> {

            using next = std::conditional_t<
                sizeof...(I)+1 <= Max,
                std::make_index_sequence<sizeof...(I)+1>,
                sentinel
            >;

            using result_type = disjunction<
                can_invoke_t<U, const any_arg<I>&...>,
                min_args<U, Max, next>
            >;

            static constexpr bool value = result_type::value;
            static constexpr int arg_count = result_type::arg_count;
        };

        /* useful for debugging
        template<typename U, std::size_t Max>
        struct min_args<U, Max, std::index_sequence<0, 1, 2>> {

            using T = can_invoke_t<U, any_arg<0>, any_arg<1>, any_arg<2>>;
            using g = typename T::asdf;
            using result_type = disjunction<
                T,
                min_args<U, Max, std::make_index_sequence<4>>
            >;

            static constexpr bool value = result_type::value;
            static constexpr int arg_count = result_type::arg_count;
        };*/

        template<typename U, std::size_t Max>
        struct min_args<U, Max, void> {

            using result_type = disjunction<
                can_invoke_t<U, void>,
                min_args<U, Max, std::make_index_sequence<1>>
            >;

            static constexpr int arg_count = result_type::arg_count;
            static constexpr bool value = result_type::value;
        };

        struct dummy_wrapper {
            using arg_types = std::tuple<unknown>;
        };

        template<typename T>
        struct arg_tuple_size {
            static constexpr int value = -1;
        };

        template<>
        struct arg_tuple_size<std::tuple<unknown>> {
            static constexpr int value = -1;
        };

        template<typename... T>
        struct arg_tuple_size<std::tuple<T...>> {
            static constexpr int value = sizeof...(T);
        };
       
        template<typename T, std::size_t SearchLimit = 10>
        struct function_object_min_arity {

        private:

            static constexpr int precient_arity = arg_tuple_size<
                typename T::arg_types
            >::value;

            static constexpr int tentative_min_arity = min_args<
                T, SearchLimit, void
            >::arg_count;

        public:

            static constexpr int value =
                precient_arity == -1
                || (tentative_min_arity < precient_arity && tentative_min_arity >= 0)
                ? tentative_min_arity : precient_arity;
        };

        template<typename T, std::size_t SearchLimit>
        struct function_object_max_arity {

        private:

            static constexpr int precient_arity = arg_tuple_size<
                typename T::arg_types
            >::value;

            static constexpr int tentative_max_arity = max_args<
                T, std::make_index_sequence<SearchLimit>
            >::arg_count;

        public:

            static constexpr int value =
                precient_arity == -1 || tentative_max_arity > precient_arity
                ? tentative_max_arity : precient_arity;
        };

        template<typename Dispatch>
        using arity_t = std::integral_constant<int,
            arg_tuple_size<typename Dispatch::arg_types>::value
        >;

        template<typename Dispatch, std::size_t SearchLimit>
        using min_arity_t = std::integral_constant<int,
            std::conditional<
                Dispatch::is_function_object::value,
                function_object_min_arity<Dispatch, SearchLimit>,
                arity_t<Dispatch>
            >::type::value
        >;

        template<typename Dispatch, std::size_t SearchLimit>
        using max_arity_t = std::integral_constant<int,
            std::conditional<
                Dispatch::is_function_object::value,
                function_object_max_arity<Dispatch, SearchLimit>,
                arity_t<Dispatch>
            >::type::value
        >;
    }
}

#endif