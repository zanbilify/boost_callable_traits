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

    namespace detail {

        template<typename T>
        struct sub_success {};

        using substitution_failure = std::int8_t;
    }
}

#endif
