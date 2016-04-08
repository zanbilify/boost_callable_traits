/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_REFERENCE_QUALIFIER_HPP
#define CALLABLE_TRAITS_REMOVE_REFERENCE_QUALIFIER_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace permissive {

        template<typename T>
        using remove_reference_qualifier =
            typename detail::traits<T>::remove_reference;
    }

    namespace detail {

        template<bool Sfinae>
        struct remove_reference_qualifier_error {

            static_assert(Sfinae,
                "callable_traits::remove_reference_qualifier<T> "
                "is not a meaningful operation for this T.");
        };

        template<typename T, bool Sfinae>
        using remove_reference_qualifier_t = fail_if_invalid<
            permissive::remove_reference_qualifier<T>,
            remove_reference_qualifier_error<Sfinae>>;
    }

    namespace verbose {

        template<typename T>
        using remove_reference_qualifier =
            detail::remove_reference_qualifier_t<T, false>;
    }

    template<typename T>
    using remove_reference_qualifier =
        detail::remove_reference_qualifier_t<T, true>;
}

#endif
