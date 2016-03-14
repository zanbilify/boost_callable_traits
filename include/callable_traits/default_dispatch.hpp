/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DEFAULT_DISPATCH_HPP
#define CALLABLE_TRAITS_DEFAULT_DISPATCH_HPP

template<typename T>
struct default_dispatch {
    static constexpr const bool is_valid = true;
    static constexpr const bool value = is_valid;
    using dispatch_type = T;
};

#endif