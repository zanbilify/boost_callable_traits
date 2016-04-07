/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_NO_SFINAE_REMOVE_CV_QUALIFIERS_HPP
#define CALLABLE_TRAITS_NO_SFINAE_REMOVE_CV_QUALIFIERS_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace no_sfinae {

        template<typename T>
        using remove_cv_qualifiers =
            typename detail::traits<T>::remove_cv;
    }
}

#endif
