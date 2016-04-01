/*!
@copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_PRIVATE_TUPLE_HPP
#define CALLABLE_TRAITS_DETAIL_PRIVATE_TUPLE_HPP

namespace callable_traits { 

    namespace detail { 

        template<typename... Ts>
        struct private_tuple {
            using to_std_tuple = std::tuple<Ts...>;
        };

    }
}

#endif