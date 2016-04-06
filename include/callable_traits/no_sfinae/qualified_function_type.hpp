/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_NO_SFINAE_QUALIFIED_FUNCTION_TYPE_HPP
#define CALLABLE_TRAITS_NO_SFINAE_QUALIFIED_FUNCTION_TYPE_HPP

#include <callable_traits/detail/traits.hpp>

#include <type_traits>
#include <functional>
#include <utility>

namespace callable_traits {

    namespace no_sfinae {

        template<typename T>
        using qualified_function_type =
            typename detail::traits<T>::abominable_type;
		
    }
}

#endif
