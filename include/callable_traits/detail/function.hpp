/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_FUNCTION_HPP
#define CALLABLE_TRAITS_DETAIL_FUNCTION_HPP

#include <callable_traits/qualifier_flags.hpp>
#include <callable_traits/detail/qualifier_traits.hpp>
#include <callable_traits/detail/fwd/function_fwd.hpp>
#include <callable_traits/detail/calling_conventions.hpp>
#include <callable_traits/detail/set_function_qualifiers.hpp>
#include <callable_traits/detail/default_callable_traits.hpp>
#include <callable_traits/config.hpp>


#include <tuple>

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct function : default_callable_traits<> {};

#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS
#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS

#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS const
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS

#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS volatile
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS

#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS const volatile
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS

#ifndef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS

#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS &
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS


#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS &&
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS

#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS const &
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS


#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS const &&
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS

#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS volatile &
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS


#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS volatile &&
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS

#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS const volatile &
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS


#define CALLABLE_TRAITS_INCLUDE_QUALIFIERS const volatile &&
        #include <callable_traits/detail/unguarded/function.hpp>
#undef CALLABLE_TRAITS_INCLUDE_QUALIFIERS

#endif //#ifndef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
#endif //#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

        #undef CALLABLE_TRAITS_SPECIALIZE_FUNCTION

        // function pointers

        #define CALLABLE_TRAITS_CC_TAG dummy
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC
        #define CALLABLE_TRAITS_ST
        #include <callable_traits/detail/unguarded/function_ptr.hpp>
        #include <callable_traits/detail/unguarded/function_ptr_varargs.hpp>
        #undef CALLABLE_TRAITS_ST
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC

        /* ?
        #ifdef CALLABLE_TRAITS_ENABLE_CDECL
        #define CALLABLE_TRAITS_CC_TAG cdecl_tag
        #define CALLABLE_TRAITS_VARARGS_CC __cdecl
        #define CALLABLE_TRAITS_CC __cdecl
        #define CALLABLE_TRAITS_ST
        #include <callable_traits/detail/unguarded/function_ptr.hpp>
        #undef CALLABLE_TRAITS_ST
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC
        #endif*/

        #ifdef CALLABLE_TRAITS_ENABLE_STDCALL
        #define CALLABLE_TRAITS_CC_TAG stdcall_tag
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC __stdcall
        #define CALLABLE_TRAITS_ST
        #include <callable_traits/detail/unguarded/function_ptr.hpp>
        #undef CALLABLE_TRAITS_ST
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC
        #endif

        #ifdef CALLABLE_TRAITS_ENABLE_FASTCALL
        #define CALLABLE_TRAITS_CC_TAG fastcall_tag
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC __fastcall
        #define CALLABLE_TRAITS_ST
        #include <callable_traits/detail/unguarded/function_ptr.hpp>
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_ST
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC
        #endif

        #ifdef CALLABLE_TRAITS_ENABLE_PASCAL
        #define CALLABLE_TRAITS_CC_TAG pascal_tag
        #define CALLABLE_TRAITS_VARARGS_CC CALLABLE_TRAITS_DEFAULT_VARARGS_CC
        #define CALLABLE_TRAITS_CC
        #define CALLABLE_TRAITS_ST pascal
        #include <callable_traits/detail/unguarded/function_ptr.hpp>
        #undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_ST
        #undef CALLABLE_TRAITS_CC_TAG
        #undef CALLABLE_TRAITS_VARARGS_CC
        #endif

        template<typename T>
        struct function<T&> : function<T> {

            static constexpr const bool value = !std::is_pointer<T>::value;

            using traits = function;
            using base = function<T>;
            using type = T&;
            using remove_varargs = typename base::remove_varargs&;
            using add_varargs = typename base::add_varargs&;
            using remove_member_pointer = type;

            using remove_member_reference = invalid_type;
            using add_member_lvalue_reference = invalid_type;
            using add_member_rvalue_reference = invalid_type;
            using add_member_const = invalid_type;
            using add_member_volatile = invalid_type;
            using add_member_cv = invalid_type;
            using remove_member_const = invalid_type;
            using remove_member_volatile = invalid_type;
            using remove_member_cv = invalid_type;

            template<typename NewReturn>
            using apply_return = typename base::template apply_return<NewReturn>&;
            
            using clear_args = typename base::clear_args&;
            
            template<typename... NewArgs>
            using push_front = typename base::template push_front<NewArgs...>&;

            template<typename... NewArgs>
            using push_back = typename base::template push_back<NewArgs...>&;

            template<std::size_t Count>
            using pop_back = typename base::template pop_back<Count>&;

            template<std::size_t Count>
            using pop_front = typename base::template pop_front<Count>&;

            template<std::size_t Index, typename... NewArgs>
            using insert_args = typename base::template insert_args<Index, NewArgs...>&;

            template<std::size_t Index, std::size_t Count>
            using remove_args = typename base::template remove_args<Index, Count>&;

            template<std::size_t Index, typename... NewArgs>
            using replace_args = typename base::template replace_args<Index, NewArgs...>&;
        };

        template<typename T, T Value>
        struct function<std::integral_constant<T, Value>> {
            using traits = function<T>;
            static constexpr const bool value = traits::value;
        };
    }
}

#endif
