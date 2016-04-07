/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ARG_AT_HPP
#define CALLABLE_TRAITS_ARG_AT_HPP

#include <callable_traits/args.hpp>
#include <callable_traits/detail/required_definitions.hpp>
#include <tuple>

namespace callable_traits {
	
    template<size_t I, typename T>
    using arg_at = typename std::tuple_element<I, args<T>>::type;
}

#endif
