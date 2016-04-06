/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_VOLATILE_QUALIFIER_HPP
#define CALLABLE_TRAITS_ADD_VOLATILE_QUALIFIER_HPP

#include <callable_traits/detail/utility.hpp>
#include <callable_traits/no_sfinae/add_volatile_qualifier.hpp>

namespace callable_traits {

    namespace detail {

        template<int i = 0>
        struct add_volatile_qualifier_error {

#ifdef CALLABLE_TRAITS_DEBUG
			static_assert(i != 0,
				"callable_traits::add_volatile_qualifier<T> is not a meaningful operation for this T.");
#endif
        };
    }

    template<typename T>
    using add_volatile_qualifier = detail::fail_if_invalid<
		no_sfinae::add_volatile_qualifier<T>,
		detail::add_volatile_qualifier_error<>
	>;
}

#endif
