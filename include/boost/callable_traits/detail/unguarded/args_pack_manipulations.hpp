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

    using type = sfinae_try<
        CALLABLE_TRAITS_BEGIN_PACK_MANIP
        typename std::tuple_element<
            map_insert<I, arg_count, StartTo, sizeof...(U)>::value,
            std::tuple<CALLABLE_TRAITS_ARGS_PACK..., U...>>::type...
        CALLABLE_TRAITS_END_PACK_MANIP,

        fail_if<!(StartTo <= arg_count), index_out_of_range_for_parameter_list>
    >;
};

template<std::size_t N, typename... U>
using insert_args = typename insert_impl<
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

    using type = sfinae_try<
        CALLABLE_TRAITS_BEGIN_PACK_MANIP
        typename std::tuple_element<
        map_remove<Is, Index, Count>::value,
        std::tuple<CALLABLE_TRAITS_ARGS_PACK...>>::type...
        CALLABLE_TRAITS_END_PACK_MANIP,

        fail_if<!(Index < arg_count), index_out_of_range_for_parameter_list>
    >;
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
using remove_args = typename remove_impl<
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

    using type = sfinae_try<
        CALLABLE_TRAITS_BEGIN_PACK_MANIP
        typename std::tuple_element<
        map_overwrite<I, arg_count, StartTo, sizeof...(U)>::value,
        std::tuple<CALLABLE_TRAITS_ARGS_PACK..., U...>>::type...
        CALLABLE_TRAITS_END_PACK_MANIP,

        fail_if<!(StartTo <= arg_count), index_out_of_range_for_parameter_list>
    >;
};

template<std::size_t StartIndex, typename... U>
using replace_args = typename overwrite_impl<
    CALLABLE_TRAITS_MAKE_IX_SEQ(arg_count <= StartIndex + sizeof...(U) ?
        StartIndex + sizeof...(U) : arg_count),
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
using pop_front = remove_args<0, arg_count <= Count ? arg_count : Count>;

template<std::size_t Count>
using pop_back = remove_args<
    arg_count <= Count ? 0 : arg_count - Count,
    arg_count <= Count ? arg_count : Count>;
