/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_VARARGS_HPP
#define CALLABLE_TRAITS_ADD_VARARGS_HPP

#include <callable_traits/detail/utility.hpp>
#include <callable_traits/no_sfinae/add_varargs.hpp>

namespace callable_traits {

    namespace detail {

        template<int i = 0>
        struct add_varargs_error {

#ifdef CALLABLE_TRAITS_DEBUG
			static_assert(i != 0,
				"callable_traits::add_varargs<T> is not a meaningful operation for this T.");
#endif
        };
    }

    template<typename T>
    using add_varargs = detail::fail_if_invalid<
		no_sfinae::add_varargs<T>,
		detail::add_varargs_error<>
	>;
}

#endif
