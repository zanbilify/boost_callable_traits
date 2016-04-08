/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ARGS_HPP
#define CALLABLE_TRAITS_ARGS_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace permissive {

        template<typename T>
        using args = typename detail::traits<T>::arg_types;
    }

    namespace detail {

        template<bool Sfinae>
        struct args_error {

            static_assert(Sfinae,
                "Could not determine the arguments for "
                "T in callable_traits::args<T>. Note: "
                "If T is the type of a generic lambda or "
                " overloaded/templated function object, "
                "the arguments cannot be determined. ");
        };

        template<typename T, bool Sfinae>
        using args_t = fail_if_invalid<
            permissive::args<T>,
            args_error<Sfinae>>;
    }

    namespace verbose {

        template<typename T>
        using args = detail::args_t<T, false>;
    }

    template<typename T>
    using args = detail::args_t<T, true>;
}

#endif
