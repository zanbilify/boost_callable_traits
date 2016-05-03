/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_PMF_HPP
#define CALLABLE_TRAITS_DETAIL_PMF_HPP

#include <callable_traits/detail/fwd/pmf_fwd.hpp>
#include <callable_traits/detail/calling_conventions.hpp>
#include <callable_traits/detail/set_function_qualifiers.hpp>
#include <callable_traits/qualifier_flags.hpp>
#include <callable_traits/detail/qualifier_traits.hpp>
#include <callable_traits/detail/default_callable_traits.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/config.hpp>
#include <tuple>

namespace callable_traits {

    namespace detail {

        template<flags Applied, typename CallingConvention,
            typename T, typename Return, typename... Args>
        struct set_member_function_qualifiers_t;

        template<flags Applied, typename CallingConvention,
            typename T, typename Return, typename... Args>
        struct set_varargs_member_function_qualifiers_t;

        template<flags Flags, typename... Ts>
        using set_member_function_qualifiers =
            typename set_member_function_qualifiers_t<Flags, Ts...>::type;

        template<flags Flags, typename... Ts>
        using set_varargs_member_function_qualifiers =
            typename set_varargs_member_function_qualifiers_t<Flags, Ts...>::type;

        template<typename T, typename U>
        struct pmf : default_callable_traits {};

        template<typename U, typename T, T Value>
        struct pmf <U, std::integral_constant<T, Value>> {
            using traits = pmf<T, T>;
            static constexpr const bool value = traits::value;
        };

        #define CALLABLE_TRAITS_CC_TAG dummy
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC
        #include <callable_traits/detail/unguarded/pmf.hpp>
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC


        #define CALLABLE_TRAITS_CC_TAG dummy
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC
        #include <callable_traits/detail/unguarded/pmf_varargs.hpp>
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC

        #ifdef CALLABLE_TRAITS_ENABLE_CDECL
        #define CALLABLE_TRAITS_CC_TAG cdecl_tag
        #define CALLABLE_TRAITS_VARARGS_CC __cdecl
        #define CALLABLE_TRAITS_CC __cdecl
        #include <callable_traits/detail/unguarded/pmf.hpp>
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC

        //TODO: not sure how to tell whether __cdecl
        //is implicit for varargs on a given platform...

        #endif //CALLABLE_TRAITS_ENABLE_CDECL

        #ifdef CALLABLE_TRAITS_ENABLE_STDCALL
        #define CALLABLE_TRAITS_CC_TAG stdcall_tag
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC __stdcall
        #include <callable_traits/detail/unguarded/pmf.hpp>
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC
        #endif

        #ifdef CALLABLE_TRAITS_ENABLE_FASTCALL
        #define CALLABLE_TRAITS_CC_TAG fastcall_tag
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC __fastcall
        #include <callable_traits/detail/unguarded/pmf.hpp>
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC
        #endif
    }
}

#endif
