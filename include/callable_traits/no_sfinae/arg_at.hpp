/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_NO_SFINAE_ARG_AT_HPP
#define CALLABLE_TRAITS_NO_SFINAE_ARG_AT_HPP

#include <callable_traits/no_sfinae/args.hpp>
#include <callable_traits/detail/utility.hpp>

namespace callable_traits {

    namespace no_sfinae {

        template<size_t I, typename T>
        using arg_at = detail::weak_at<I, args<T>>;
    }
}

#endif
