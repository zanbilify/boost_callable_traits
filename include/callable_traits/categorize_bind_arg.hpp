/*!
Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
Copyright (c) 2001 David Abrahams
Copyright (c) 2005 Peter Dimov
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#include <callable_traits/placeholder.hpp>
#include <callable_traits/fwd/bind_expression_fwd.hpp>
#include <callable_traits/any_arg.hpp>
#include <functional>

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct bind_value {};

        template<typename T>
        struct categorize_bind_arg {
            using type = typename std::conditional<
                std::is_placeholder< T >::value == 0,
                bind_value<T>,
                placeholder<std::is_placeholder< T >::value>
            >::type;
        };

        template<typename T>
        struct categorize_bind_arg< bind_value<T> > {
            using type = detail::bind_value<T>;
        };

        template<typename T>
        struct categorize_bind_arg< std::reference_wrapper<T> > {
            using type = std::reference_wrapper<T>;
        };

        template<int I>
        struct categorize_bind_arg< placeholder<I> > {
            using type = placeholder<I>;
        };

        template<typename Callable, typename... Args>
        struct categorize_bind_arg<bind_expression<Callable, Args...>> {

            using return_type =  typename bind_expression<Callable, Args...>::return_type;

            using type = typename std::conditional<
                std::is_same<return_type, unknown>::value,
                any_arg<>,
                return_type
            >::type;
        };
    }
}
