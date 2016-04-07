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
#include <callable_traits/no_sfinae/args.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<int i = 0>
        struct args_error {

#ifdef CALLABLE_TRAITS_DEBUG
			static_assert(i != 0,
				"Unable to determine arguments of type T in callable_traits::args<T>.");
#endif
        };
    }
	
    template<typename T>
    using args = detail::fail_if_invalid<no_sfinae::args<T>, detail::args_error<>>;

}

#endif
