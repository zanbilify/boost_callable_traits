 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_ANY_ARG_HPP
#define CALLABLE_TRAITS_DETAIL_ANY_ARG_HPP

#include <utility>
#include <callable_traits/detail/make_constexpr.hpp>
#include <callable_traits/config.hpp>

namespace callable_traits {

    namespace detail {

        //any_arg is only used in unevaluated contexts
        template<std::size_t I = 0>
        struct any_arg {

            template<typename T>
            operator T& () const;

            template<typename T>
            operator T&& () const;

            any_arg() = default;

#if !defined(_MSC_VER)
            //MSVC doesn't like this because it can deduce 'void'
            template<typename... T>
            any_arg(T&&...);
#endif //!defined(_MSC_VER)
            
        };

        template<typename T, typename U = shallow_decay<T>>
        using int_if_trivial = 
            typename std::enable_if<
                CALLABLE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE(U),
                T
            >::type;

        template<std::size_t I = 0>
        struct any_arg_evaluated {

            template<typename T, int_if_trivial<T> = 0>
            inline constexpr operator T& () const {
                return CALLABLE_TRAITS_MAKE_CONSTEXPR(T&);
            }

            template<typename T, int_if_trivial<T> = 0>
            inline constexpr operator T&& () const {
                return CALLABLE_TRAITS_MAKE_CONSTEXPR(T&&);
            }

            any_arg_evaluated() = default;
        };
    }
}

#endif //CALLABLE_TRAITS_ANY_ARG_HPP