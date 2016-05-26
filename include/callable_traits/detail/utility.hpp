/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_UTILITY_HPP
#define CALLABLE_TRAITS_DETAIL_UTILITY_HPP

#include <callable_traits/config.hpp>
#include <type_traits>
#include <tuple>
#include <utility>
#include <cstdint>

namespace callable_traits {

    struct invalid_type { invalid_type() = delete; };

    namespace detail {

        // used to convey "this type doesn't matter" in code
        struct dummy {};

        // used as return type in failed SFINAE tests
        struct substitution_failure : std::false_type{};

        template<bool Value>
        using bool_type = std::integral_constant<bool, Value>;

        // shorthand for std::tuple_element
        template<std::size_t I, typename Tup>
        using at = typename std::tuple_element<I, Tup>::type;


        namespace util_detail {

            template<std::size_t I, typename Tup, typename = std::true_type>
            struct weak_at_t {
                using type = at<I, Tup>;
            };

            template<std::size_t I, typename Tup>
            struct weak_at_t<I, Tup, bool_type<I >= std::tuple_size<Tup>::value>>{
                using type = invalid_type;
            };
        }

        // bounds-checked version of at (see above)
        template<std::size_t I, typename Tup>
        using weak_at = typename util_detail::weak_at_t<I, Tup>::type;

        // a faster version of std::decay_t
        template<typename T>
        using shallow_decay = typename std::remove_cv<
            typename std::remove_reference<T>::type
        >::type;

        namespace util_detail {

            template<typename T>
            struct is_reference_wrapper_t {
                using type = std::false_type;
            };

            template<typename T>
            struct is_reference_wrapper_t<std::reference_wrapper<T>> {
                using type = std::true_type;
            };
        }

        template<typename T>
        using is_reference_wrapper =
            typename util_detail::is_reference_wrapper_t<shallow_decay<T>>::type;

        template<typename T, typename Class>
        using add_member_pointer = T Class::*;

        template<typename Traits>
        using can_accept_member_qualifiers = bool_type<
            Traits::is_function::value || Traits::has_member_qualifiers_function::value>;
        
        namespace util_detail {

            template<typename T>
            struct remove_member_pointer_t {
                using type = T;
            };

            template<typename T, typename U>
            struct remove_member_pointer_t<T U::*>{
                using type = T;
            };
        }

        template<typename T>
        using remove_member_pointer =
            typename util_detail::remove_member_pointer_t<T>::type;

        namespace util_detail {
            template<typename T, bool Value>
            struct type_value {
                static constexpr const bool value = Value;
                using type = T;
            };
        }

        template<typename T, typename FailType>
        using fail_if_invalid = typename CALLABLE_TRAITS_DISJUNCTION(
            util_detail::type_value<T, !std::is_same<T, invalid_type>::value>,
            FailType
        )::type;

        template<typename T, typename Fallback>
        using fallback_if_invalid = typename std::conditional<
            std::is_same<T, invalid_type>::value,
            Fallback,
            T
        >::type;
    }
}

#endif
