 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_CONSTRAINTS_HPP
#define CALLABLE_TRAITS_CONSTRAINTS_HPP

#include <type_traits>
#include <callable/has_normal_call_operator.hpp>
#include <callable/can_dereference.hpp>

// CALLABLE_TRAITS_REQUIRES_ and CALLABLE_TRAITS_REQUIRES adapted from Range-v3 here:
// https://github.com/ericniebler/range-v3/blob/6600e6054513202e61a067de48c4a05ca2b11099/include/range/v3/utility/concepts.hpp#L861
// Copyright Eric Niebler 2013-2014

#define CALLABLE_TRAITS_PP_CAT_(X, Y) X ## Y
#define CALLABLE_TRAITS_PP_CAT(X, Y)  CALLABLE_TRAITS_PP_CAT_(X, Y)

#define CALLABLE_TRAITS_REQUIRES_(...) \
    int CALLABLE_TRAITS_PP_CAT(callable_traits_requires_, __LINE__) = 42,                        \
    typename std::enable_if<                                                                     \
        (CALLABLE_TRAITS_PP_CAT(callable_traits_requires_, __LINE__) == 43) || (__VA_ARGS__),    \
        bool                                                                                     \
    >::type constraint_success = true                                                            \
/**/

#define CALLABLE_TRAITS_REQUIRES(...) \
    template<                                                                                    \
        int CALLABLE_TRAITS_PP_CAT(callable_traits_requires_, __LINE__) = 42,                    \
        typename std::enable_if<                                                                 \
            (CALLABLE_TRAITS_PP_CAT(callable_traits_requires_, __LINE__) == 43) || (__VA_ARGS__),\
            bool                                                                                 \
        >::type constraint_success = true>                                                       \
/**/

namespace callable_traits {

    namespace ctdetail {

        struct callable_dummy {
            void operator()() {}
        };

        template<typename T>
        using default_normal_callable = typename std::conditional<
            has_normal_call_operator<T>::value,
            T,
            callable_dummy
        >::type;

    }
}

#endif