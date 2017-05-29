 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_TEST_INVOKE_HPP
#define CALLABLE_TRAITS_DETAIL_TEST_INVOKE_HPP

#include <boost/callable_traits/detail/config.hpp>
#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <type_traits>
#include <utility>

namespace boost { namespace callable_traits { namespace detail {
    
    struct substition_failure {};

    template<typename T>
    using shallow_decay = typename std::remove_const<
        typename std::remove_reference<T>::type>::type;

    template<typename T>
    struct is_reference_wrapper_t {
        using type = std::false_type;
    };

    template<typename T>
    struct is_reference_wrapper_t<std::reference_wrapper<T>> {
        using type = std::true_type;
    };

    template<typename T>
    using is_reference_wrapper =
        typename is_reference_wrapper_t<shallow_decay<T>>::type;


    template<typename T, typename = std::true_type>
    struct unwrap_reference_t {
        using type = T;
    };

    template<typename T>
    struct unwrap_reference_t<T, is_reference_wrapper<T>> {
        using type = decltype(std::declval<T>().get());
    };

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

    //returns std::true_type for pointers and smart pointers
    template<typename T>
    using can_dereference = std::integral_constant<bool,
        can_dereference_t<T>::value>;


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

    // When T is a pointer, generalize<T> is the resulting type of the
    // pointer dereferenced. When T is an std::reference_wrapper, generalize<T>
    // is the underlying reference type. Otherwise, generalize<T> is T.
    template<typename T>
    using generalize = typename generalize_t<T>::type;

    // handles the member pointer rules of INVOKE
    template<typename Base, typename T,
             typename IsBaseOf = std::is_base_of<Base, shallow_decay<T>>,
             typename IsSame = std::is_same<Base, shallow_decay<T>>>
    using generalize_if_dissimilar = typename std::conditional<
        IsBaseOf::value || IsSame::value, T, generalize<T>>::type;

    // removes std::reference_wrapper
    template<typename T>
    using unwrap_reference = typename unwrap_reference_t<T>::type;

    template<typename...>
    struct test_invoke;

    template<typename Pmf, typename T, typename... Args>
    struct test_invoke<pmf<Pmf>, T, Args...> {

        using class_t = typename pmf<Pmf>::class_type;

       template<typename P, typename U, typename... Rgs,
            typename Obj = generalize_if_dissimilar<class_t, U&&>>
        auto operator()(P&& p, U&& u, Rgs&&... rgs) const ->
            success<decltype((std::declval<Obj>().*p)(static_cast<Rgs&&>(rgs)...))>;

        auto operator()(...) const -> substitution_failure;
    };

    template<typename Pmd, typename... Args>
    struct test_invoke<pmd<Pmd>, Args...> {

        using class_t = typename pmd<Pmd>::class_type;

        template<typename P, typename U,
            typename Obj = generalize_if_dissimilar<class_t, U&&>>
        auto operator()(P&& p, U&& u) const ->
            success<decltype((std::declval<Obj>().*p))>;

        auto operator()(...) const -> substitution_failure;
    };

    template<typename F, typename... Args>
    struct test_invoke<F, Args...> {

        template<typename T, typename... Rgs,
            typename U = unwrap_reference<typename std::remove_reference<T>::type>>
        auto operator()(T&& t, Rgs&&... rgs) const ->
            success<decltype(std::declval<U>()(static_cast<Rgs&&>(rgs)...))>;

        auto operator()(...) const -> substitution_failure;
    };

    template<typename T, typename... Args>
    struct is_invocable_impl {
        using traits = detail::traits<T>;
        using test = detail::test_invoke<traits, Args...>;
        using result = decltype(test{}(::std::declval<T>(), ::std::declval<Args>()...));
        using failure = detail::substitution_failure;
        using is_invalid_invoke = std::is_same<result, failure>;
        using type = std::integral_constant<bool, !is_invalid_invoke::value>;
    };

    /*template<typename IsMemberPointer, typename Traits, typename... Args>
    struct build_invoke_t;

    template<typename Traits, typename... Args>
    struct build_invoke_t<std::false_type, Traits, Args...> {
        using test = detail::test_invoke<Traits, Args...>;
        using original_type = typename Traits::type;

        using result = decltype(test{}(
            ::std::declval<original_type>(),
            ::std::declval<Args>()...
        ));

        using failure = detail::substitution_failure;
        using type = std::integral_constant<bool, !std::is_same<result, failure>::value>;
    };

    template<typename Traits, typename... Args>
    struct build_invoke_t<std::true_type, Traits, Args...> {
        using test = test_invoke<Traits, Args...>;
        using original_type = typename Traits::type;
        using invoke_type = typename Traits::invoke_type;

        using result = decltype(test{}(
            ::std::declval<original_type>(),
            ::std::declval<invoke_type>(),
            ::std::declval<Args>()...
        ));

        using failure = detail::substitution_failure;
        using type = std::integral_constant<bool, !std::is_same<result, failure>::value>;
    };

    template<typename Traits>
    struct build_invoke_t<std::false_type, Traits, void> {
        using test = test_invoke<Traits>;
        using original_type = typename Traits::type;
        using result = decltype(test{}(static_cast<original_type>(::std::declval<original_type>())));
        using failure = detail::substitution_failure;
        using type = std::integral_constant<bool, !std::is_same<result, failure>::value>;
    };

    template<typename Traits>
    struct build_invoke_t<std::true_type, Traits, void> {
        using test = test_invoke<Traits>;
        using original_type = typename Traits::type;
        using invoke_type = typename Traits::invoke_type;

        using result = decltype(test{}(
            ::std::declval<original_type>(),
            static_cast<invoke_type>(::std::declval<invoke_type>())
        ));

        using failure = detail::substitution_failure;
        using type = std::integral_constant<bool, !std::is_same<result, failure>::value>;
    };

    template<typename Traits, typename... Args>
    using is_invocable_impl = typename build_invoke_t<
        typename Traits::is_member_pointer, Traits, Args...>::type;*/

}}} // namespace boost::callable_traits::detail

#endif // #ifndef CALLABLE_TRAITS_DETAIL_TEST_INVOKE_HPP
