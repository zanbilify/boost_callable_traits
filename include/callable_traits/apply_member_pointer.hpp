/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_APPLY_MEMBER_POINTER_HPP
#define CALLABLE_TRAITS_APPLY_MEMBER_POINTER_HPP

#include <callable_traits/detail/utility.hpp>
#include <callable_traits/no_sfinae/apply_member_pointer.hpp>

namespace callable_traits {

    namespace detail {

        template<int i = 0>
        struct apply_member_pointer_error {
			static_assert(i != 0,
				"callable_traits::apply_member_pointer<T> is not a meaningful operation for this T.");
        };
    }

    template<typename T, typename C>
    using apply_member_pointer = detail::fail_if_invalid<
		typename no_sfinae::apply_member_pointer<T, C>,
		detail::apply_member_pointer_error<>
	>;
}

#endif
