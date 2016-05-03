/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_SET_QUALIFIERS_IMPL_HPP
#define CALLABLE_TRAITS_SET_QUALIFIERS_IMPL_HPP

namespace callable_traits {

    namespace detail {
    
        template<typename T, flags QFlags>
        struct set_qualifiers_impl {
            using type = T;
            static_assert(sizeof(T) < 0, "Unexpected qualifier flags.");
        };

        template<typename T>
        struct set_qualifiers_impl<T, 0 /*default*/> {
            using type = T;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 1 /*const*/> {
            using type = T const;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 2 /*volatile*/> {
            using type = T volatile;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 3 /*const volatile*/> {
            using type = T const volatile;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 4 /*&*/> {
            using type = typename std::add_lvalue_reference<T>::type;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 5 /*const &*/> {
            using type = typename std::add_lvalue_reference<T const>::type;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 6 /*volatile &*/> {
            using type = typename std::add_lvalue_reference<T volatile>::type;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 7 /*const volatile &*/> {
            using type = typename std::add_lvalue_reference<T const volatile>::type;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 8 /*&&*/> {
            using type = T&&;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 9 /*const &&*/> {
            using type = typename std::remove_reference<T>::type const &&;
        };

        template<typename T>
        struct set_qualifiers_impl<T&, 9 /*const &&*/> {
            using type = T const &;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 10 /*volatile &&*/> {
            using type = typename std::remove_reference<T>::type volatile &&;
        };

        template<typename T>
        struct set_qualifiers_impl<T&, 10 /*volatile &&*/> {
            using type = T volatile &;
        };

        template<typename T>
        struct set_qualifiers_impl<T, 11 /*const volatile &&*/> {
            using type = typename std::remove_reference<T>::type const volatile &&;
        };

        template<typename T>
        struct set_qualifiers_impl<T&, 11 /*const volatile &&*/> {
            using type = T const volatile &;
        };
    }

    template<typename T, flags Flags>
    using qualify = typename detail::set_qualifiers_impl<T, Flags>::type;
}

#endif //#ifndef CALLABLE_TRAITS_SET_QUALIFIERS_IMPL_HPP
