/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_RESULT_OF_HPP
#define CALLABLE_TRAITS_RESULT_OF_HPP

#include <callable_traits/detail/utility.hpp>
#include <callable_traits/no_sfinae/result_of.hpp>
#include <callable_traits/detail/required_definitions.hpp>

namespace callable_traits {

    namespace detail {

        template<int i = 0>
        struct result_of_error {

#ifdef CALLABLE_TRAITS_DEBUG
			static_assert(i != 0,
				"Unable to determine the return type of T in callable_traits::result_of<T>.");
#endif
        };
    }

    template<typename T>
    using result_of = detail::fail_if_invalid<
		no_sfinae::result_of<T>,
		detail::result_of_error<>
	>;
}

#endif
