/*!
Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_PLACEHOLDER_HPP
#define CALLABLE_TRAITS_DETAIL_PLACEHOLDER_HPP

#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/tuple_sort.hpp>
#include <type_traits>
#include <functional>

namespace callable_traits {

    namespace detail {

    template<int I>
        struct placeholder {

            placeholder() = default;

            template<typename T>
            placeholder(T const &) {
                static_assert(I == std::is_placeholder<T>::value, "Invalid placeholder");
            }
        };
    }
}
namespace std {

    template<int I> 
    struct is_placeholder< callable_traits::detail::placeholder<I> > {
        static constexpr const int value = I;
    };
}

namespace callable_traits {

    namespace detail {

        template<typename Expression, std::size_t OriginalArgIndex, std::size_t PhValue>
        struct ph_route {
            using expression = Expression;
            static constexpr const auto original_arg_index = OriginalArgIndex;
            static constexpr const auto ph_value = PhValue;
        };

        template<typename Expression, typename, typename> struct argument_routing {};

        template<typename Expression, std::size_t... I, typename Tuple>
        struct argument_routing<Expression, std::index_sequence<I...>, Tuple> {
            using type =
                std::tuple<
                    ph_route<
                        Expression,
                        I,
                        std::is_placeholder<typename std::tuple_element<I, Tuple>::type>::value
                    >...
                >;
        };

        //base case
        template <typename...> struct placeholder_routes_detail;
        template <> struct placeholder_routes_detail<> {
            using type = std::tuple<>;
        };

        template <typename Head, typename ...Tail>
        struct placeholder_routes_detail<Head, Tail...> {
            //TODO - is there a faster way to do this?
            using type = typename std::conditional<
                Head::ph_value == 0,
                typename placeholder_routes_detail<Tail...>::type,
                typename prepend<
                    Head,
                    typename placeholder_routes_detail<Tail...>::type
                >::type
            >::type;
        };

        template <typename... Args>
        struct placeholder_routes_detail<std::tuple<Args...> > {
            using type = typename placeholder_routes_detail<Args...>::type;
        };

        template<typename PhLeft, typename PhRight>
        struct compare_placeholders {
            static constexpr bool value = 
                std::is_placeholder<PhLeft>::value < std::is_placeholder<PhRight>::value;
        };

        template <typename Expression, typename...> struct placeholder_routes;
        template <typename Expression> struct placeholder_routes<Expression> { using type = std::tuple<>; };

        template <typename Expression, typename... Args>
        struct placeholder_routes<Expression, std::tuple<Args...> >
        {
            using routed_placeholders = typename placeholder_routes_detail<
                typename argument_routing<
                    Expression,
                    std::make_index_sequence<sizeof...(Args)>,
                    std::tuple<Args...>
                >::type
            >::type;

            using type = tuple_sort<routed_placeholders, compare_placeholders>;
        };
    }
}
#endif
