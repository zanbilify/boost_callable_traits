 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_ANY_ARG_HPP
#define CALLABLE_TRAITS_DETAIL_ANY_ARG_HPP

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
    }
}

#endif //CALLABLE_TRAITS_ANY_ARG_HPP