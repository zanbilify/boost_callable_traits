/*!
@copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_REMOVE_DUPLICATE_PLACEHOLDERS_HPP
#define CALLABLE_TRAITS_REMOVE_DUPLICATE_PLACEHOLDERS_HPP

namespace callable_traits {

    namespace ctdetail {

        template<typename...>
        struct remove_duplicate_placeholders {
            using type = std::tuple<>;
        };

        template <typename... Args>
        struct remove_duplicate_placeholders<std::tuple<Args...> > {
            using type = typename remove_duplicate_placeholders<Args...>::type;
        };

        //if 1st and 2nd elements use the same placeholder index, remove the second element
        template<typename PhRoute1, typename PhRoute2, typename... Tail>
        struct remove_duplicate_placeholders<PhRoute1, PhRoute2, Tail...> {
            using type = typename std::conditional<
                PhRoute1::ph_value == PhRoute2::ph_value,
                typename remove_duplicate_placeholders<PhRoute1, Tail...>::type,
                typename prepend<PhRoute1, typename remove_duplicate_placeholders<PhRoute2, Tail...>::type>::type
            >::type;
        };

        //base case
        template<typename PhRoute1, typename PhRoute2>
        struct remove_duplicate_placeholders<PhRoute1, PhRoute2> {
            using type = typename std::conditional<
                PhRoute1::ph_value == PhRoute2::ph_value,
                std::tuple<PhRoute1>,
                std::tuple<PhRoute1, PhRoute2>
            >::type;
        };

        //base case
        template<typename LastPhRoute>
        struct remove_duplicate_placeholders<LastPhRoute> {
            using type = std::tuple<LastPhRoute>;
        };
    }
}

#endif