/*
Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_CALLING_CONVENTIONS_HPP
#define CALLABLE_TRAITS_DETAIL_CALLING_CONVENTIONS_HPP

#include <callable_traits/detail/utility.hpp>
#include <tuple>

namespace callable_traits {

    struct cdecl_tag{};
    struct stdcall_tag{};
    struct fastcall_tag{};
    struct pascal_tag{};

    namespace detail {

        template<typename T, typename Tag>
        struct add_calling_convention_t {
            using type = invalid_type;
        };

        template<typename T, typename Tag>
        struct has_calling_convention_t {
            using type = std::false_type;
        };
    }
}

#endif
