/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_NO_SFINAE_ADD_VOLATILE_QUALIFIER_HPP
#define CALLABLE_TRAITS_NO_SFINAE_ADD_VOLATILE_QUALIFIER_HPP

#include <callable_traits/detail/traits.hpp>

namespace callable_traits {

    namespace no_sfinae {

        template<typename T>
        using add_volatile_qualifier =
            typename detail::traits<T>::add_volatile;
    }
}

#endif
