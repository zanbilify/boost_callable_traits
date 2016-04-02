/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_COMMON_SIGNATURE_T_HPP
#define CALLABLE_TRAITS_DETAIL_COMMON_SIGNATURE_T_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/tuple_group_by.hpp>
#include <callable_traits/detail/tuple_sort.hpp>
#include <callable_traits/detail/bind_expression.hpp>
#include <callable_traits/detail/fwd/bind_expression_parser_fwd.hpp>
#include <callable_traits/detail/best_match.hpp>
#include <callable_traits/detail/utility.hpp>
#include <tuple>
#include <functional>

namespace callable_traits {
    
    namespace detail {

        template<typename Tup, typename Seq>
        struct reverse_impl;

        template<typename Tup, size_t... I>
        struct reverse_impl<Tup, std::index_sequence<I...>> {
            using type = std::tuple<at<sizeof...(I) - 1 - I, Tup>...>;
        };

        template<typename Tup>
        using reverse = typename reverse_impl<Tup,
                std::make_index_sequence<std::tuple_size<Tup>::value>>::type;

        template<typename Tup, std::size_t EndSize>
        struct trim_left;

        template<typename Arg, std::size_t EndSize>
        struct trim_left<std::tuple<Arg>, EndSize> {
            using type = typename std::conditional<
                EndSize == 1,
                std::tuple<Arg>,
                std::tuple<>
            >::type;
        };

        template<std::size_t EndSize>
        struct trim_left<std::tuple<>, EndSize> {
            using type = std::tuple<>;
        };

        template<typename Front, typename... Args, std::size_t EndSize>
        struct trim_left<std::tuple<Front, Args...>, EndSize> {

            using type = typename std::conditional<
                EndSize == sizeof...(Args) + 1,
                std::tuple<Front, Args...>,
                typename trim_left<std::tuple<Args...>, EndSize>::type
            >::type;
        };

        template<typename Tup, std::size_t EndSize>
        struct trim_right {
            using reversed = reverse<Tup>;
            using type = reverse<typename trim_left<reversed, EndSize>::type>;
        };

        template<typename Tup, std::size_t I, typename Seq>
        struct best_match_cross_section;

        template<typename Tup, std::size_t I, std::size_t... J>
        struct best_match_cross_section<Tup, I, std::index_sequence<J...>>{
            using result = best_match<weak_at<I, weak_at<J, Tup>>...>;

            using type = typename std::conditional<
                std::is_rvalue_reference<result>::value,
                typename std::remove_reference<result>::type,
                result
            >::type;
        };

        template<typename ArgsTuplesTuple, typename Seq>
        struct common_args;

        template<typename Tup, std::size_t... I>
        struct common_args<Tup, std::index_sequence<I...>> {
            using seq = std::index_sequence<I...>;
            using type = std::tuple<typename best_match_cross_section<Tup, I, seq>::type...>;
        };

        template<typename TraitsTup, typename Seq>
        struct common_signature_t;

        template<typename TraitsTup, std::size_t... I>
        struct common_signature_t<TraitsTup, std::index_sequence<I...>> {

            using common_return = typename std::common_type<
                typename at<I, TraitsTup>::return_type...
            >::type;

            using args_tuples = std::tuple<
                typename at<I, TraitsTup>::arg_types...
            >;

            using first_args = at<0, args_tuples>;

            using arg_count = std::tuple_size<first_args>;

            using seq = std::make_index_sequence<
                arg_count::value <= sizeof...(I) ? sizeof...(I) : arg_count::value
            >;

            using common_arg_types = typename common_args<args_tuples, seq>::type;
            using trimmed_arg_types = typename trim_right<
                common_arg_types, arg_count::value>::type;

            using type = build_function<common_return, trimmed_arg_types>;
        };
    }
}

#endif
