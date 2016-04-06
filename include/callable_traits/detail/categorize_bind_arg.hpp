/*!
Copyright (c) 2001-2004 Peter Dimov and Multi Media Ltd.
Copyright (c) 2001 David Abrahams
Copyright (c) 2005 Peter Dimov
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#ifndef CALLABLE_TRAITS_DETAIL_CATEGORIZE_BIND_ARG_HPP
#define CALLABLE_TRAITS_DETAIL_CATEGORIZE_BIND_ARG_HPP

#include <callable_traits/detail/placeholder.hpp>
#include <callable_traits/detail/fwd/bind_expression_fwd.hpp>
#include <callable_traits/detail/any_arg.hpp>
#include <functional>

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct bind_value {};

        template<typename T, typename NoRef>
        struct categorize_bind_arg {
            using type = typename std::conditional<
                std::is_placeholder< NoRef >::value == 0,
                bind_value<T>,
                placeholder<std::is_placeholder< NoRef >::value>
            >::type;
        };

        template<typename T, typename Ref>
        struct categorize_bind_arg< Ref, bind_value<T>> {
            using type = detail::bind_value<T>;
        };

        template<typename T, typename Ref>
        struct categorize_bind_arg< Ref, std::reference_wrapper<T> > {
            using type = std::reference_wrapper<T>;
        };

        template<int I, typename Ref>
        struct categorize_bind_arg< Ref, placeholder<I> > {
            using type = placeholder<I>;
        };

        template<typename Ref, typename Callable, typename... Args>
        struct categorize_bind_arg<Ref, bind_expression<Callable, Args...>> {

            using return_type = typename bind_expression<Callable, Args...>::return_type;

            using type = typename std::conditional<
                std::is_same<return_type, invalid_type>::value,
                any_arg<>,
                return_type
            >::type;
        };
    }
}

#endif
