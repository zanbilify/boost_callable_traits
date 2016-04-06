/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_APPLY_RETURN_HPP
#define CALLABLE_TRAITS_APPLY_RETURN_HPP

#include <callable_traits/detail/utility.hpp>
#include <callable_traits/no_sfinae/apply_return.hpp>

namespace callable_traits {

    namespace detail {

        template<int i = 0>
        struct apply_return_error {

#ifdef CALLABLE_TRAITS_DEBUG
			static_assert(i != 0,
				"callable_traits::apply_return<T> is not a meaningful operation for this T.");
#endif
        };
    }

    template<typename T, typename C>
    using apply_return = detail::fail_if_invalid<
		typename no_sfinae::apply_return<T, C>,
		detail::apply_return_error<>
	>;
}

#endif
