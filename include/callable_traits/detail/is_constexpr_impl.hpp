#ifndef CAN_INVOKE_IMPL_HPP
#define CAN_INVOKE_IMPL_HPP

#include <callable_traits/detail/traits.hpp>
#include <callable_traits/detail/arity.hpp>
#include <callable_traits/detail/utility.hpp>
#include <callable_traits/detail/make_constexpr.hpp>
#include <callable_traits/detail/any_arg.hpp>
#include <callable_traits/detail/pmd.hpp>
#include <callable_traits/detail/pmf.hpp>
#include <callable_traits/config.hpp>

#include <type_traits>
#include <utility>
#include <type_traits>

namespace callable_traits {

    namespace detail {

#ifndef CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED

        template<typename F, typename Seq>
        struct is_constexpr_t {
            auto operator()(...) const -> substitution_failure;
        };

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
            using seq = std::make_index_sequence<min_args::value < 0 ? 0 : min_args::value>;
            using test = is_constexpr_t<traits, seq>;
            using result = decltype(test{}(::std::forward<T>(t)));
            using failure = substitution_failure;
            using is_not_constexpr = std::is_same<result, failure>;
            return std::integral_constant<bool, !is_not_constexpr::value>{};
        }

#else
        inline constexpr auto
        is_constexpr_impl(...) {
            return std::false_type{};
        }

#endif //ifndef CALLABLE_TRAITS_CONSTEXPR_CHECKS_DISABLED
    }
}

#endif // CAN_INVOKE_IMPL_HPP

