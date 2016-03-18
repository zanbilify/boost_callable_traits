/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_SUBSTITUTION_HPP
#define CALLABLE_TRAITS_SUBSTITUTION_HPP

#include <cstdint>

namespace callable_traits {

    namespace ctdetail {

        // sizeof(substitution_success<T>) is always greater than sizeof(substitution_failure)

        template<typename T>
        struct substitution_success {
            std::int8_t buffer;
            typename std::remove_reference<T>::type* data;
        };

        using substitution_failure = std::int8_t;
    }
}

#endif