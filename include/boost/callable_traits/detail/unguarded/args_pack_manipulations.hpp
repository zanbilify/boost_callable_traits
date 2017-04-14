/*
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY

*/

static constexpr std::size_t arg_count = sizeof...(BOOST_CLBL_TRTS_ARGS_PACK);

template<std::size_t I, std::size_t RemoveAt, std::size_t Count>
struct map_remove {
    static constexpr bool still_waiting = I < RemoveAt;
    static constexpr std::size_t value =
        still_waiting ? I : I + Count;
};

template<typename, std::size_t Index, std::size_t Count>
struct remove_impl;

template<std::size_t... Is, std::size_t Index, std::size_t Count>
struct remove_impl<BOOST_CLBL_TRTS_IX_SEQ(Is...), Index, Count> {
    using type = sfinae_try<
        BOOST_CLBL_TRTS_BEGIN_PACK_MANIP
        typename std::tuple_element<
        map_remove<Is, Index, Count>::value,
        std::tuple<BOOST_CLBL_TRTS_ARGS_PACK...>>::type...
        BOOST_CLBL_TRTS_END_PACK_MANIP,
        fail_if<!(Index < arg_count), index_out_of_range_for_parameter_list>
    >;
};

//when not removing anything
template<std::size_t... Is, std::size_t Index>
struct remove_impl<BOOST_CLBL_TRTS_IX_SEQ(Is...), Index, 0> {
    using type =
        BOOST_CLBL_TRTS_BEGIN_PACK_MANIP
        BOOST_CLBL_TRTS_ARGS_PACK...
        BOOST_CLBL_TRTS_END_PACK_MANIP;
};

template<std::size_t StartIndex, std::size_t Count = 1>
using remove_args = typename remove_impl<
    BOOST_CLBL_TRTS_MAKE_IX_SEQ(arg_count - Count), StartIndex, Count>::type;

template<typename... NewArgs>
using push_front =
    BOOST_CLBL_TRTS_BEGIN_PACK_MANIP
    NewArgs..., BOOST_CLBL_TRTS_ARGS_PACK...
    BOOST_CLBL_TRTS_END_PACK_MANIP;

template<std::size_t Count>
using pop_front = remove_args<0, arg_count <= Count ? arg_count : Count>;
