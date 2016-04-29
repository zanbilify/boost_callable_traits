/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_COPY_QUALIFIERS_IMPL_HPP
#define CALLABLE_TRAITS_DETAIL_COPY_QUALIFIERS_IMPL_HPP

#include <callable_traits/detail/set_function_qualifiers.hpp>

namespace callable_traits {

    namespace detail {

		template<typename ToTraits, typename FromTraits,
			bool IsSignature = can_accept_member_qualifiers<ToTraits>::value
								&& can_accept_member_qualifiers<FromTraits>::value>
		struct copy_qualifiers_impl;
		
		template<typename ToTraits, typename FromTraits>
		struct copy_qualifiers_impl<ToTraits, FromTraits, true> {
			
			using type = typename ToTraits::template set_qualifiers<FromTraits::q_flags>;
		};
		
		template<typename ToTraits, typename FromTraits>
		struct copy_qualifiers_impl<ToTraits, FromTraits, false> {
			
			using type = set_other_qualifiers<FromTraits::q_flags, typename ToTraits::type>;
		};
	}
}

#endif //#ifndef CALLABLE_TRAITS_DETAIL_COPY_QUALIFIERS_IMPL_HPP
