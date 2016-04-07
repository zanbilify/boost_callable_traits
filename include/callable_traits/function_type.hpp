/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FUNCTION_TYPE_HPP
#define CALLABLE_TRAITS_FUNCTION_TYPE_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/no_sfinae/function_type.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<int i = 0>
        struct function_type_error {

#ifdef CALLABLE_TRAITS_DEBUG
			static_assert(i != 0,
				"Unable to determine a function type for type T in callable_traits::function_type<T>.");
#endif
        };
    }
	
    template<typename T>
    using function_type = detail::fail_if_invalid<
		no_sfinae::function_type<T>,
        detail::function_type_error<>
	>;
}

#endif
