/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_CV_QUALIFIERS_HPP
#define CALLABLE_TRAITS_ADD_CV_QUALIFIERS_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace permissive {

        template<typename T>
        using add_cv_qualifiers =
            typename detail::traits<T>::add_cv;
    }

    namespace detail {

        template<bool Sfinae>
        struct add_cv_qualifiers_error {

            static_assert(Sfinae,
                "callable_traits::add_cv_qualifiers<T> "
                "is not a meaningful operation for this T.");
        };

        template<typename T, bool Sfinae>
        using add_cv_qualifiers_t = fail_if_invalid<
            permissive::add_cv_qualifiers<T>,
            add_cv_qualifiers_error<Sfinae>>;
    }

    namespace verbose {

        template<typename T>
        using add_cv_qualifiers =
            detail::add_cv_qualifiers_t<T, false>;
    }

    template<typename T>
    using add_cv_qualifiers =
        detail::add_cv_qualifiers_t<T, true>;
}

#endif
