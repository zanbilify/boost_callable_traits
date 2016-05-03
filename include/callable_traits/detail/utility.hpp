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

    struct constants {
        static constexpr std::size_t arity_search_limit = CALLABLE_TRAITS_ARITY_SEARCH_LIMIT;
    };

    struct invalid_type { invalid_type() = delete; };


    namespace detail {

        // used to convey "this type doesn't matter" in code
        struct dummy {};

        // used as return type in failed SFINAE tests
        struct substitution_failure{};


        // shorthand for std::tuple_element
        template<std::size_t I, typename Tup>
        using at = typename std::tuple_element<I, Tup>::type;


        namespace util_detail {

            template<std::size_t I, typename Tup, typename = std::true_type>
            struct weak_at_t {
                using type = at<I, Tup>;
            };

            template<std::size_t I, typename Tup>
            struct weak_at_t<I, Tup, std::integral_constant<bool, I >= std::tuple_size<Tup>::value>>{
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

        //polyfill for C++17 negation
        //TODO rename and move to polyfills folder
        template<typename BoolType>
        using negate = std::integral_constant<bool, !BoolType::value>;


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


        template<typename T, typename = std::true_type>
        struct unwrap_reference_t {
            using type = T;
        };

        template<typename T>
        struct unwrap_reference_t<T, is_reference_wrapper<T>> {
            using type = decltype(std::declval<T>().get());
        };

        // removes std::reference_wrapper
        template<typename T>
        using unwrap_reference = typename unwrap_reference_t<T>::type;


        namespace util_detail {

            template<typename T>
            struct is_integral_constant_t {
                using type = std::false_type;
            };

            template<typename T, T Value>
            struct is_integral_constant_t<std::integral_constant<T, Value>> {
                using type = std::true_type;
            };
        }

        template<typename T>
        using is_integral_constant = typename util_detail::is_integral_constant_t<
            shallow_decay<T>>::type;


        template<typename Check, typename Result>
        using if_integral_constant =
            typename std::enable_if<is_integral_constant<Check>::value, Result>::type;

        template<typename Check, typename Result>
        using if_not_integral_constant =
            typename std::enable_if<!is_integral_constant<Check>::value, Result>::type;


        template<typename T, typename Class>
        using add_member_pointer = T Class::*;

        template<typename Traits>
        using can_accept_member_qualifiers = std::integral_constant<bool,
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


        template<typename T, typename U = shallow_decay<T>>
        using is_constexpr_constructible = std::integral_constant<bool,
            std::is_literal_type<U>::value && std::is_default_constructible<U>::value
        >;


        namespace util_detail {

            template<typename...>
            struct build_function_t;

            template<typename Return, typename... Args>
            struct build_function_t<Return, std::tuple<Args...>>{
                using type = Return(Args...);
            };
        }

        template<typename Ret, typename Tup>
        using build_function =
            typename util_detail::build_function_t<Ret, Tup>::type;

        namespace util_detail {

            template<typename T>
            struct can_dereference_t
            {
                template<typename>
                struct check {};

                template<typename U>
                static std::int8_t test(
                    check<typename std::remove_reference<decltype(*std::declval<U>())>::type>*
                );

                template<typename>
                static std::int16_t test(...);

                static constexpr const bool value =
                    sizeof(test<T>(nullptr)) == sizeof(std::int8_t);
            };
        }

        //returns std::true_type for pointers and smart pointers
        template<typename T>
        using can_dereference = std::integral_constant<bool,
            util_detail::can_dereference_t<T>::value
        >;


        namespace util_detail {

            template<typename T, typename = std::true_type>
            struct generalize_t {
                using type = T;
            };

            template<typename T>
            struct generalize_t<T, std::integral_constant<bool,
                    can_dereference<T>::value && !is_reference_wrapper<T>::value
            >>{
                using type = decltype(*std::declval<T>());
            };

            template<typename T>
            struct generalize_t<T, is_reference_wrapper<T>> {
                using type = decltype(std::declval<T>().get());
            };
        }

        // When T is a pointer, generalize<T> is the resulting type of the
        // pointer dereferenced. When T is an std::reference_wrapper, generalize<T>
        // is the underlying reference type. Otherwise, generalize<T> is T.
        template<typename T>
        using generalize = typename util_detail::generalize_t<T>::type;


        // handles the member pointer rules of INVOKE
        template<typename Base, typename T,
                 typename IsBaseOf = std::is_base_of<Base, shallow_decay<T>>,
                 typename IsSame = std::is_same<Base, shallow_decay<T>>>
        using generalize_if_dissimilar = typename std::conditional<
            IsBaseOf::value || IsSame::value, T, generalize<T>
        >::type;


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

        template<class T, class U>
        struct copy_cvr {
            
        private:

            using no_ref_U = typename std::remove_reference<U>::type;
            using no_ref_T = typename std::remove_reference<T>::type;
            
            using C = typename std::conditional<
                std::is_const<no_ref_U>::value,
                typename std::add_const<no_ref_T>::type,
                no_ref_T
            >::type;
            
            using V = typename std::conditional<
                std::is_volatile<no_ref_U>::value,
                typename std::add_volatile<C>::type,
                C
            >::type;

        public:

            using type = typename std::conditional<
                std::is_lvalue_reference<U>::value,
                V &,
                typename std::conditional<
                    std::is_rvalue_reference<U>::value,
                    V &&,
                    V
                >::type
            >::type;
        };

        //used to prepend a type to a tuple
        template <typename...> struct prepend;

        template <> struct prepend<> {
            using type = std::tuple<>;
        };

        template <typename T, typename... Args>
        struct prepend<T, std::tuple<Args...> > {
            using type = std::tuple<T, Args...>;
        };

        /*template <typename T, typename... Args>
        struct prepend<T, private_tuple<Args...> > {
            using type = private_tuple<T, Args...>;
        };*/
    }
}

#endif
