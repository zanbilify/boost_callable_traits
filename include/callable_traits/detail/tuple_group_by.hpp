/*!
@file

@coyright Modified Work Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_TUPLE_GROUP_BY_HPP
#define CALLABLE_TRAITS_DETAIL_TUPLE_GROUP_BY_HPP

#include <callable_traits/detail/tuple_sort.hpp>
#include <callable_traits/detail/utility.hpp>
#include <tuple>
#include <type_traits>

namespace callable_traits { 

    namespace detail {

        template<typename T, template<class> class Pred>
        struct group_by_value {
            static constexpr auto value = Pred<T>::value;
        };

        template<typename Tup, template<class> class Pred>
        struct distinct_group_by_values;

        template<typename Last, template<class> class Pred>
        struct distinct_group_by_values<std::tuple<Last>, Pred> {
            using type = std::tuple<group_by_value<Last, Pred>>;
        };

        template<typename Head, typename Next, typename... Tail, template<class> class Pred>
        struct distinct_group_by_values<std::tuple<Head, Next, Tail...>, Pred> {

            static constexpr const auto is_in_same_group =
                Pred<Head>::value == Pred<Next>::value;

            using next = typename distinct_group_by_values<std::tuple<Next, Tail...>, Pred>::type;

            using type = typename std::conditional<
                is_in_same_group,
                next,
                typename prepend<group_by_value<Head, Pred>, next>::type
            >::type;
        };

        template <typename Pred, typename...> struct group_by_filter_impl;

        template <typename Pred> struct group_by_filter_impl<Pred> {
            using type = std::tuple<>;
        };

        template <typename Pred, typename Head, typename ...Tail>
        struct group_by_filter_impl<Pred, Head, Tail...> {
            using pred_result = decltype(std::declval<Pred>()(std::declval<Head>()));
            using type = typename std::conditional<
                pred_result::value,
                typename prepend<Head, typename group_by_filter_impl<Pred, Tail...>::type>::type,
                typename group_by_filter_impl<Pred, Tail...>::type
            >::type;
        };

        template <typename Pred, typename Tup>
        struct group_by_filter;

        template <typename Pred, typename... Ts>
        struct group_by_filter<Pred, std::tuple<Ts...>> {
            using type = typename group_by_filter_impl<Pred, Ts...>::type;
        };

        template<typename DistinctGroupByValues, template<class> class Pred, std::size_t I>
        struct filter_predicate {

            using compare_against = at<I, DistinctGroupByValues>;

            template<typename T>
            auto operator()(T) ->
                std::integral_constant<bool, Pred<T>::value == compare_against::value>;
        };

        template<typename Tup, typename DistinctGroupByValues, template<class> class Pred, typename ValuesSeq>
        struct group_by_impl;

        template<typename Tup, typename DistinctGroupByValues, template<class> class Pred, std::size_t... I>
        struct group_by_impl<Tup, DistinctGroupByValues, Pred, CALLABLE_TRAITS_IX_SEQ(I...)> {

            using type = std::tuple<
                typename group_by_filter<
                    filter_predicate<DistinctGroupByValues, Pred, I>,
                    Tup
                >::type...
            >;
        };

        template<typename Tup, template<class> class Pred>
        struct group_by_t {

            template<typename T, typename U>
            struct sort_predicate {
                static constexpr const auto left = Pred<T>::value;
                static constexpr const auto right = Pred<U>::value;
                static constexpr const bool value = left < right;
            };

            using group_by_values = typename distinct_group_by_values<Tup, Pred>::type;

            using type = typename group_by_impl<
                tuple_sort<Tup, sort_predicate>,
                group_by_values,
                Pred,
                CALLABLE_TRAITS_MAKE_IX_SEQ(std::tuple_size<group_by_values>::value)
            >::type;
        };

        template<typename Tup, template<class> class Pred>
        using tuple_group_by = typename group_by_t<Tup, Pred>::type;
    }
}

#endif
