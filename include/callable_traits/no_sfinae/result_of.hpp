/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_NO_SFINAE_RESULT_OF_HPP
#define CALLABLE_TRAITS_NO_SFINAE_RESULT_OF_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace no_sfinae {

        template<typename T>
        using result_of = typename detail::traits<T>::return_type;
    }
}

#endif
