 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_TEMPLATE_WORM_HPP
#define CALLABLE_TRAITS_DETAIL_TEMPLATE_WORM_HPP

#include <utility>
#include <type_traits>
#include <callable_traits/detail/make_constexpr.hpp>
#include <callable_traits/config.hpp>

namespace callable_traits {

    namespace detail {

        template<typename T, typename U = shallow_decay<T>>
        using int_if_literal =
            typename std::enable_if<is_constexpr_constructible<U>::value, T>::type;

        template<std::size_t I = 0>
        struct constexpr_template_worm;

        template<std::size_t I>
        struct constexpr_template_worm {

            using type = constexpr_template_worm<I>;

            static const constexpr_template_worm<I> value;

            template<typename T, int_if_literal<T> = 0>
            inline constexpr operator T& () const {
                return CALLABLE_TRAITS_MAKE_CONSTEXPR(T&);
            }

            template<typename T, int_if_literal<T> = 0>
            inline constexpr operator T&& () const {
                return CALLABLE_TRAITS_MAKE_CONSTEXPR(T&&);
            }

            constexpr_template_worm() = default;

#if !defined(CALLABLE_TRAITS_MSVC)
            //MSVC doesn't like this because it can deduce 'void'
            template<typename... T>
            constexpr_template_worm(T&&...){}
#endif //!defined(CALLABLE_TRAITS_MSVC)

            inline constexpr auto operator+() const { return type{}; }
            inline constexpr auto operator-() const { return type{}; }
            inline constexpr auto operator*() const { return type{}; }
            inline constexpr auto operator&() const { return type{}; }
            inline constexpr auto operator!() const { return type{}; }
            inline constexpr auto operator~() const { return type{}; }
            inline constexpr auto operator()(...) const { return type{}; }
        };

        template<std::size_t I>
        const constexpr_template_worm<I> constexpr_template_worm<I>::value = {};

        //template_worm is only used in unevaluated contexts
        template<std::size_t I = 0>
        struct template_worm : constexpr_template_worm<I> {
            
#if !defined(CALLABLE_TRAITS_MSVC)
            //msvc doesn't like this
            static constexpr const auto value = constexpr_template_worm<I>{};
#endif //!defined(CALLABLE_TRAITS_MSVC)

            template<typename T>
            operator T& () const;

            template<typename T>
            operator T&& () const;

            template_worm() = default;

#if !defined(CALLABLE_TRAITS_MSVC)
            //MSVC doesn't like this because it can deduce 'void'
            template<typename... T>
            template_worm(T&&...);
#endif //!defined(CALLABLE_TRAITS_MSVC)
            
            template_worm<I> operator+() const;
            template_worm<I> operator-() const;
            template_worm<I> operator*() const;
            template_worm<I> operator&() const;
            template_worm<I> operator!() const;
            template_worm<I> operator~() const;
            template_worm<I> operator()(...) const;
        };

#define CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(...) \
template<std::size_t I, typename T>                        \
constexpr inline auto                                      \
__VA_ARGS__ (constexpr_template_worm<I>, T&&)              \
    -> constexpr_template_worm<I> {                        \
        return constexpr_template_worm<I>{};               \
}                                                          \
                                                           \
template<std::size_t I, typename T>                        \
constexpr inline auto                                      \
__VA_ARGS__ (template_worm<I>, T&&) -> template_worm<I> {  \
    return template_worm<I>{};                             \
}                                                          \
                                                           \
template<std::size_t I, typename T>                        \
constexpr inline auto                                      \
__VA_ARGS__ (T&&, constexpr_template_worm<I>)              \
    -> constexpr_template_worm<I> {                        \
        return constexpr_template_worm<I>{};               \
}                                                          \
                                                           \
template<std::size_t I, typename T>                        \
constexpr inline auto                                      \
__VA_ARGS__ (T&&, template_worm<I>) -> template_worm<I> {  \
    return template_worm<I>{};                             \
}                                                          \
                                                           \
template<std::size_t I, std::size_t J>                     \
constexpr inline auto                                      \
__VA_ARGS__ (constexpr_template_worm<I>,                   \
             constexpr_template_worm<J>)                   \
    -> constexpr_template_worm<I> {                        \
        return constexpr_template_worm<I>{};               \
}                                                          \
                                                           \
template<std::size_t I, std::size_t J>                     \
constexpr inline auto                                      \
__VA_ARGS__ (template_worm<I>, template_worm<J>)           \
    -> template_worm<I> {                                  \
    return template_worm<I>{};                             \
}                                                          \
/**/

        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator+)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator-)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator/)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator*)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator==)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator!=)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator&&)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator||)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator|)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator&)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator%)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator,)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator<<)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator>>)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator<)
        CALLABLE_TRAITS_TEMPLATE_WORM_BINARY_OPERATOR(operator>)
    }
}

#endif //CALLABLE_TRAITS_DETAIL_TEMPLATE_WORM_HPP
