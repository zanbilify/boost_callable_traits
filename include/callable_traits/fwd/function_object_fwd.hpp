/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FWD_FUNCTION_OBJECT_FWD_HPP
#define CALLABLE_TRAITS_FWD_FUNCTION_OBJECT_FWD_HPP

#if defined (CALLABLE_TRAITS_FUNCTION_OBJECT_HPP)
static_assert(false, "<callable_traits/fwd/function_object_fwd.hpp> must be included before <callable_traits/function_object.hpp>.");
#endif

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct function_object;

    }
}

#endif