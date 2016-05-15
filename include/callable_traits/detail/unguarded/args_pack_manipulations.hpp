/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

*/

static constexpr std::size_t arg_count = sizeof...(CALLABLE_TRAITS_ARGS_PACK);

template<std::size_t I, std::size_t From, std::size_t To, std::size_t Count>
struct map_insert {

    static constexpr bool still_waiting = I < To;
    static constexpr bool is_inserting = I >= To && I < To + Count;
    static constexpr std::size_t offset = I > To ? I - To : 0;

    static constexpr std::size_t value =
        still_waiting ? I : is_inserting ? From + offset : I - Count;
};

template<typename, typename, std::size_t>
struct insert_impl;

template<std::size_t... I, typename... U, std::size_t StartTo>
struct insert_impl<CALLABLE_TRAITS_IX_SEQ(I...), std::tuple<U...>, StartTo> {

    static_assert(StartTo <= arg_count, "Insert index out of range");

    using type =
        CALLABLE_TRAITS_BEGIN_PACK_MANIP
        typename std::tuple_element<
            map_insert<I, arg_count, StartTo, sizeof...(U)>::value,
            std::tuple<CALLABLE_TRAITS_ARGS_PACK..., U...>>::type...
        CALLABLE_TRAITS_END_PACK_MANIP;
};

template<std::size_t N, typename... U>
using insert_at = typename insert_impl<
    CALLABLE_TRAITS_MAKE_IX_SEQ(arg_count + sizeof...(U)),
    std::tuple<U...>, N>::type;

template<std::size_t I, std::size_t RemoveAt, std::size_t Count>
struct map_remove {

    static constexpr bool still_waiting = I < RemoveAt;

    static constexpr std::size_t value =
        still_waiting ? I : I + Count;
};

template<typename, std::size_t Index, std::size_t Count>
struct remove_impl;

template<std::size_t... Is, std::size_t Index, std::size_t Count>
struct remove_impl<CALLABLE_TRAITS_IX_SEQ(Is...), Index, Count> {

    static_assert(Index < arg_count,
        "Remove index out of range");

    using type =
        CALLABLE_TRAITS_BEGIN_PACK_MANIP
        typename std::tuple_element<
        map_remove<Is, Index, Count>::value,
        std::tuple<CALLABLE_TRAITS_ARGS_PACK...>>::type...
        CALLABLE_TRAITS_END_PACK_MANIP;
};

//when not removing anything
template<std::size_t... Is, std::size_t Index>
struct remove_impl<CALLABLE_TRAITS_IX_SEQ(Is...), Index, 0> {

    using type =
        CALLABLE_TRAITS_BEGIN_PACK_MANIP
        CALLABLE_TRAITS_ARGS_PACK...
        CALLABLE_TRAITS_END_PACK_MANIP;
};

template<std::size_t StartIndex, std::size_t Count = 1>
using remove_at = typename remove_impl<
    CALLABLE_TRAITS_MAKE_IX_SEQ(arg_count - Count), StartIndex, Count>::type;

template<std::size_t I, std::size_t From, std::size_t To, std::size_t Count>
struct map_overwrite {

    static constexpr bool still_waiting = I < To;
    static constexpr bool is_inserting = I >= To && I < To + Count;
    static constexpr std::size_t offset = I > To ? I - To : 0;

    static constexpr std::size_t value =
        still_waiting ? I : is_inserting ? From + offset : I;
};

template<typename, typename, std::size_t>
struct overwrite_impl;

template<std::size_t... I, typename... U, std::size_t StartTo>
struct overwrite_impl<CALLABLE_TRAITS_IX_SEQ(I...), std::tuple<U...>, StartTo> {

    static_assert(StartTo <= arg_count, "Insert index out of range");

    using type =
        CALLABLE_TRAITS_BEGIN_PACK_MANIP
        typename std::tuple_element<
        map_overwrite<I, arg_count, StartTo, sizeof...(U)>::value,
        std::tuple<CALLABLE_TRAITS_ARGS_PACK..., U...>>::type...
        CALLABLE_TRAITS_END_PACK_MANIP;
};

template<std::size_t StartIndex, typename... U>
using replace_arg = typename overwrite_impl<
    CALLABLE_TRAITS_MAKE_IX_SEQ(arg_count <= StartIndex + sizeof...(U) ? StartIndex + sizeof...(U) : arg_count),
    std::tuple<U...>, StartIndex>::type;

template<typename... NewArgs>
using push_front =
    CALLABLE_TRAITS_BEGIN_PACK_MANIP
    NewArgs..., CALLABLE_TRAITS_ARGS_PACK...
    CALLABLE_TRAITS_END_PACK_MANIP;

template<typename... NewArgs>
using push_back =
CALLABLE_TRAITS_BEGIN_PACK_MANIP
CALLABLE_TRAITS_ARGS_PACK..., NewArgs...
CALLABLE_TRAITS_END_PACK_MANIP;

template<std::size_t Count>
using pop_front = remove_at<0, Count>;

template<std::size_t Count>
using pop_back = remove_at<arg_count - Count, Count>;
