/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_MEMBER_POINTER_HPP
#define CALLABLE_TRAITS_REMOVE_MEMBER_POINTER_HPP

#include <callable_traits/detail/utility.hpp>
#include <callable_traits/no_sfinae/remove_member_pointer.hpp>

namespace callable_traits {

    namespace detail {

        template<int i = 0>
        struct remove_member_pointer_error {
			static_assert(i != 0,
				"callable_traits::remove_member_pointer<T> is not a meaningful operation for this T.");
        };
    }

    template<typename T>
    using remove_member_pointer = detail::fail_if_invalid<
		no_sfinae::remove_member_pointer<T>,
		detail::remove_member_pointer_error<>
	>;
}

#endif
