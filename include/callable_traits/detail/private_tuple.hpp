/*!
@copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_PRIVATE_TUPLE_HPP
#define CALLABLE_TRAITS_DETAIL_PRIVATE_TUPLE_HPP

namespace callable_traits { 

    namespace detail { 

    template<typename...> struct private_tuple;

    template<std::size_t i, std::size_t from, std::size_t to>
    struct map_insert {
        static constexpr std::size_t value = i < to ? i : i == to ? from : i - 1;
    };

    template<typename, typename, std::size_t, typename...> struct insert_impl;

    template<std::size_t... Is, typename U, std::size_t N, typename... Ts>
    struct insert_impl<std::index_sequence<Is...>, U, N, Ts...>
    {
        static_assert(N <= sizeof...(Ts), "Insert index out of range");
        using type = private_tuple<std::tuple_element_t<map_insert<Is, sizeof...(Ts), N>::value, std::tuple<Ts..., U>>...>;
    };

    template<std::size_t i, std::size_t idx>
    struct map_remove {
        static constexpr std::size_t value = i < idx ? i : i + 1;
    };

    template<typename, std::size_t, typename...>
    struct remove_impl_2;

    template<std::size_t... Is, std::size_t N, typename... Ts>
    struct remove_impl_2<std::index_sequence<Is...>, N, Ts...> {
        using type = private_tuple<
            typename std::tuple_element<
                map_remove<Is, N>::value, std::tuple<Ts...>>::type...>;
    };

    template<std::size_t N, typename... Ts>
    struct remove_impl {
        static_assert(N < sizeof...(Ts), "Remove index out of range");
        using type = typename remove_impl_2<
            std::make_index_sequence<sizeof...(Ts)-1>,
                N, Ts...>::type;
    };

    template<typename... Ts>
    struct private_tuple {

        template<std::size_t N, typename U>
        using insert = typename insert_impl<
            std::make_index_sequence<sizeof...(Ts)+1>,
                U, N, Ts...>::type;

        template<std::size_t N>
        using remove = typename remove_impl<N, Ts...>::type;
    };

    }
}

#endif
