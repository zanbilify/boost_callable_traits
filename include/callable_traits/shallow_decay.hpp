/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_SHALLOW_DECAY_HPP
#define CALLABLE_TRAITS_SHALLOW_DECAY_HPP

#include <type_traits>

namespace callable_traits {

    namespace ctdetail {

        template<typename T>
        using shallow_decay = typename std::remove_cv<
            typename std::remove_reference<T>::type
        >::type;
    }
}

#endif