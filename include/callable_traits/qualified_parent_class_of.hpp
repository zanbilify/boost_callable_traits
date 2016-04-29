/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_QUALIFIED_PARENT_CLASS_OF_HPP
#define CALLABLE_TRAITS_QUALIFIED_PARENT_CLASS_OF_HPP

#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct qualified_parent_class_of_error {

            static_assert(Sfinae,
                "TODO: error message for callable_traits::qualified_parent_class_of");
        };
    }

    namespace permissive {

        // returns callable_traits::invalid_type if parameter types
        // cannot be determined
        template<typename T>
        using qualified_parent_class_of =
			typename detail::traits<T>::invoke_type;
    }

    namespace verbose {

        template<typename T>
        using qualified_parent_class_of = detail::fail_if_invalid<
            typename detail::traits<T>::invoke_type,
            detail::qualified_parent_class_of_error<false>>;
    }

    template<typename T>
    using qualified_parent_class_of = detail::fail_if_invalid<
        typename detail::traits<T>::invoke_type,
        detail::qualified_parent_class_of_error<true>>;
}

#endif //#ifndef CALLABLE_TRAITS_QUALIFIED_PARENT_CLASS_OF_HPP
