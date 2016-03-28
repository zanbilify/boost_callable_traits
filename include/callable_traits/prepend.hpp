/*!
@copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_PREPEND_HPP
#define CALLABLE_TRAITS_PREPEND_HPP

//#include <callable_traits/private_tuple.hpp>

namespace callable_traits { 

    namespace detail { 

        template <typename...> struct prepend;

        template <> struct prepend<> {
            using type = std::tuple<>;
        };

        template <typename T, typename... Args>
        struct prepend<T, std::tuple<Args...> > {
            using type = std::tuple<T, Args...>;
        };

        /*template <typename T, typename... Args>
        struct prepend<T, private_tuple<Args...> > {
            using type = private_tuple<T, Args...>;
        };*/
    }
}

#endif