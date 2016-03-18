/*!
Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
Copyright (c) 2001 David Abrahams
Copyright (c) 2005 Peter Dimov
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_BIND_WRAPPER_HPP
#define CALLABLE_TRAITS_BIND_WRAPPER_HPP

#include <callable_traits/traits.hpp>
#include <callable_traits/categorize_bind_arg.hpp>
#include <callable_traits/tags.hpp>
#include <callable_traits/ph.hpp>
#include <callable_traits/sort_tuple.hpp>
#include <callable_traits/placeholder_routes.hpp>
#include <callable_traits/remove_duplicate_placeholders.hpp>
#include <callable_traits/fwd/bind_wrapper_fwd.hpp>

#include <tuple>
#include <functional>

namespace callable_traits {
    
    namespace ctdetail {

        template<typename PhRouteLeft, typename PhRouteRight>
        struct compare_input_index {
            static constexpr bool value = 
                PhRouteLeft::input_index < PhRouteRight::input_index;
        };

        template<typename PhRouteLeft, typename PhRouteRight>
        struct compare_output_index {
            static constexpr bool value = 
                PhRouteLeft::output_index < PhRouteRight::output_index;
        };

        template <typename PhRoutesTuple, typename OriginalArgsTuple, typename Seq>
        struct placeholders_mapped_to_original_signature;

        template <typename PhRoutesTuple, typename OriginalArgsTuple,  std::size_t... I>
        struct placeholders_mapped_to_original_signature<
            PhRoutesTuple, OriginalArgsTuple, std::index_sequence<I...>> {

            //this is where the magic happens
            using type = std::tuple<
                typename std::tuple_element<
                    std::tuple_element<I, PhRoutesTuple>::type::output_index,
                    OriginalArgsTuple
                >::type...
            >;
        };

        template <typename PhRoutesTuple, std::size_t... I>
        struct placeholders_mapped_to_original_signature<
            PhRoutesTuple, std::tuple<>, std::index_sequence<I...>> {
            using type = std::tuple<>;
        };

        template <typename T, std::size_t... I>
        struct placeholders_mapped_to_original_signature<
            T, std::tuple<ambiguous_type>, std::index_sequence<I...>> {
            using type = std::tuple<ambiguous_type>;
        };

        template<typename Callable, typename... Args>
        struct bind_args_t {

        private:

            using bind_args_tuple = std::tuple<
                typename categorize_bind_arg<Args>::type...
            >;

            using placeholder_route_map = typename placeholder_routes<
                bind_args_tuple
            >::type;

            using sorted_placeholder_routes =
                typename remove_duplicate_placeholders<
                    sort_tuple<
                        placeholder_route_map,
                        compare_input_index
                    >
                >::type;

            using placeholder_count = std::tuple_size<
                sorted_placeholder_routes
            >;

            using original_args = typename traits<Callable>::arg_types;

        public:

            using type = typename placeholders_mapped_to_original_signature<
                sorted_placeholder_routes,
                original_args,
                std::make_index_sequence<placeholder_count::value>
            >::type;
        };
    }
}

#endif