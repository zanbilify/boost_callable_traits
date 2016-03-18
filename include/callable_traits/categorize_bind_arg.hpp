/*!
Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
Copyright (c) 2001 David Abrahams
Copyright (c) 2005 Peter Dimov
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#include <callable_traits/ph.hpp>
#include <functional>

namespace callable_traits {

    namespace ctdetail {

        template<typename T>
        struct bind_value {};

        template<typename T>
        struct categorize_bind_arg {
            using type = typename std::conditional<
                std::is_placeholder< T >::value == 0,
                bind_value<T>,
                ph<std::is_placeholder< T >::value>
            >::type;
        };

        template<typename T>
        struct categorize_bind_arg< bind_value<T> > {
            using type = ctdetail::bind_value<T>;
        };

        template<typename T>
        struct categorize_bind_arg< std::reference_wrapper<T> > {
            using type = std::reference_wrapper<T>;
        };

        template<int I>
        struct categorize_bind_arg< ph<I> > {
            using type = ph<I>;
        };
    }
}