 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_IS_CONSTEXPR_T_HPP
#define CALLABLE_TRAITS_IS_CONSTEXPR_T_HPP

#include <callable_traits/detail/substitution.hpp>
#include <callable_traits/detail/is_integral_constant.hpp>
#include <callable_traits/detail/make_constexpr.hpp>
#include <callable_traits/detail/any_arg.hpp>
#include <callable_traits/config.hpp>

#include <type_traits>
#include <utility>

namespace callable_traits {

    namespace detail {

        template<typename F, typename Seq>
        struct is_constexpr_t {
            auto operator()(...) const -> substitution_failure;
        };

#ifndef CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED

        template<typename F, std::size_t... I>
        struct is_constexpr_t<F, std::index_sequence<I...>> {

            template<typename T>
            auto operator()(T&& t) const -> if_not_integral_constant<T,
                std::integral_constant<int,
                    (CALLABLE_TRAITS_MAKE_CONSTEXPR(T&&)(::callable_traits::detail::any_arg_evaluated<I>{}...), 0)>>;

            template<typename T, typename U = typename std::remove_reference<T>::type>
            auto operator()(T&& t) const -> if_integral_constant<T,
                std::integral_constant<int, (U::value(::callable_traits::detail::any_arg_evaluated<I>{}...), 0)>>;
            
            auto operator()(...) const -> substitution_failure;
        };

        template<typename Pmf, std::size_t... I>
        struct is_constexpr_t<pmf<Pmf>, std::index_sequence<I...>> {

            using class_t = typename pmf<Pmf>::invoke_type;

            template<typename P>
            auto operator()(P&&) const -> if_integral_constant<P,
                std::integral_constant<int,
                    ((CALLABLE_TRAITS_MAKE_CONSTEXPR(class_t).* ::std::remove_reference<P>::type::value)(
                        ::callable_traits::detail::any_arg_evaluated<I>{}...
                    ), 0)>>;

            auto operator()(...) const -> substitution_failure;
        };

        template<typename Pmd, std::size_t... I>
        struct is_constexpr_t<pmd<Pmd>, std::index_sequence<I...>> {
            auto operator()(...) const -> substitution_failure;
        };

#endif //ifndef CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED

    }
}

#endif
