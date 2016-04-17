/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/


#ifndef CALLABLE_TRAITS_IS_CONSTEXPR_IMPL_HPP
#define CALLABLE_TRAITS_IS_CONSTEXPR_IMPL_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/arity.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/make_constexpr.hpp>
#include <callable_traits/detail/template_worm.hpp>
#include <callable_traits/detail/pmd.hpp>
#include <callable_traits/detail/pmf.hpp>
#include <callable_traits/config.hpp>

#include <type_traits>
#include <utility>
#include <type_traits>

namespace callable_traits {

    namespace detail {

#ifdef CALLABLE_TRAITS_DISABLE_CONSTEXPR_CHECKS

        inline constexpr auto
        is_constexpr_impl(...) {
            return std::false_type{};
        }

#else

        template<typename F, typename Seq>
        struct is_constexpr_t {
            auto operator()(...) const -> substitution_failure;
        };

        template<typename F, std::size_t... I>
        struct is_constexpr_t<F, CALLABLE_TRAITS_IX_SEQ(I...)> {

            // An arbitrary expression as the left-hand argument to a non-overloaded
            // comma operator expression that is passed as a template value argument
            // will trigger a substitution failure when the expression is not constexpr
            template<typename T>
            auto operator()(T&& t) const -> if_not_integral_constant<T,
                std::integral_constant<int,

            // Where U = std::remove_reference_t<T>, CALLABLE_TRAITS_MAKE_CONSTEXPR(T&&)
            // resolves to a matching reference to a constexpr U object. Hence, U must be
            // a literal type with a constexpr default constructor. constexpr_template_worm<I>
            // is a "chameleon" type that tries to pass as anything. Generally, if U is
            // templated and uses dependent names, this will fail. However, There are a few
            // exceptions: Unary/binary operators, value member `value`, and member alias
            // `type` are all defined in terms of constexpr_template_worm<I>, so usage of
            // these will succeed in U.

                    (
                        CALLABLE_TRAITS_MAKE_CONSTEXPR(T&&)(
                            ::callable_traits::detail::constexpr_template_worm<I>{}...
                        ),
                        0
                    )
                >>;

            template<typename T, typename U = typename std::remove_reference<T>::type>
            auto operator()(T&& t) const -> if_integral_constant<T,
                std::integral_constant<int, (U::value(::callable_traits::detail::constexpr_template_worm<I>{}...), 0)>>;

            auto operator()(...) const -> substitution_failure;
        };

        template<typename Pmf, std::size_t... I>
        struct is_constexpr_t<pmf<Pmf>, CALLABLE_TRAITS_IX_SEQ(I...)> {

            // When `Pmf` is `int(foo::*)() const &&`, invoke_type is `foo const &&`
            using invoke_type = typename pmf<Pmf>::invoke_type;

            //see comments on specialization above
            template<typename P>
            auto operator()(P&&) const -> if_integral_constant<P,
                std::integral_constant<int,
                    ((CALLABLE_TRAITS_MAKE_CONSTEXPR(invoke_type).* ::std::remove_reference<P>::type::value)(
                        ::callable_traits::detail::constexpr_template_worm<I>{}...
                    ), 0)>>;

            auto operator()(...) const -> substitution_failure;
        };

        // Since constexpr data members must be static, you cannot create PMDs to them
        template<typename OriginalType, typename Pmd, std::size_t... I>
        struct is_constexpr_t<pmd<OriginalType, Pmd>, CALLABLE_TRAITS_IX_SEQ(I...)> {
            auto operator()(...) const -> substitution_failure;
        };

        template<typename T>
        inline constexpr auto
        is_constexpr_impl(T&&, std::false_type){
            return std::false_type{};
        }

        template<typename T>
        inline constexpr auto
        is_constexpr_impl(T&& t, std::true_type){
            using traits = traits<T&&>;
            using min_args = min_arity_t<traits, constants::arity_search_limit>;
            using seq = CALLABLE_TRAITS_MAKE_IX_SEQ(min_args::value < 0 ? 0 : min_args::value);
            using test = is_constexpr_t<traits, seq>;
            using result = decltype(test{}(::std::forward<T>(t)));
            using failure = substitution_failure;
            using is_not_constexpr = std::is_same<result, failure>;
            return std::integral_constant<bool, !is_not_constexpr::value>{};
        }

#endif //ifdef CALLABLE_TRAITS_DISABLE_CONSTEXPR_CHECKS

    }
}

#endif // CALLABLE_TRAITS_IS_CONSTEXPR_IMPL_HPP

