 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_ANY_ARG_HPP
#define CALLABLE_TRAITS_DETAIL_ANY_ARG_HPP

#include <utility>
#include <callable_traits/detail/make_constexpr.hpp>
#include <callable_traits/config.hpp>

namespace callable_traits {

    namespace detail {

        template<typename T, typename U = shallow_decay<T>>
        using int_if_trivial = 
            typename std::enable_if<
                CALLABLE_TRAITS_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE(U),
                T
            >::type;

        template<std::size_t I = 0>
        struct any_arg_evaluated;

        template<std::size_t I>
        struct any_arg_evaluated {

            using type = any_arg_evaluated<I>;

            static const any_arg_evaluated<I> value;

            template<typename T, int_if_trivial<T> = 0>
            inline constexpr operator T& () const {
                return CALLABLE_TRAITS_MAKE_CONSTEXPR(T&);
            }

            template<typename T, int_if_trivial<T> = 0>
            inline constexpr operator T&& () const {
                return CALLABLE_TRAITS_MAKE_CONSTEXPR(T&&);
            }

            any_arg_evaluated() = default;

#if !defined(CALLABLE_TRAITS_MSVC)
            //MSVC doesn't like this because it can deduce 'void'
            template<typename... T>
            any_arg_evaluated(T&&...);
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
        const any_arg_evaluated<I> any_arg_evaluated<I>::value = {};

#undef CALLABLE_TRAITS_CONCAT_
#undef CALLABLE_TRAITS_CONCAT
#undef CALLABLE_TRAITS_INITIALIZE_ANY_ARG_VALUE

        //any_arg is only used in unevaluated contexts
        template<std::size_t I = 0>
        struct any_arg : any_arg_evaluated<I> {
            
#if !defined(CALLABLE_TRAITS_MSVC)
            //msvc doesn't like this
            static constexpr const auto value = any_arg_evaluated<I>{};
#endif //!defined(CALLABLE_TRAITS_MSVC)


            template<typename T>
            operator T& () const;

            template<typename T>
            operator T&& () const;

            any_arg() = default;

#if !defined(CALLABLE_TRAITS_MSVC)
            //MSVC doesn't like this because it can deduce 'void'
            template<typename... T>
            any_arg(T&&...);
#endif //!defined(CALLABLE_TRAITS_MSVC)
            
            any_arg<I> operator+() const;
            any_arg<I> operator-() const;
            any_arg<I> operator*() const;
            any_arg<I> operator&() const;
            any_arg<I> operator!() const;
            any_arg<I> operator~() const;
            any_arg<I> operator()(...) const;                    
        };

#define CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(...)              \
template<std::size_t I, typename T>                               \
constexpr inline auto                                             \
__VA_ARGS__ (any_arg_evaluated<I>, T&&) -> any_arg_evaluated<I> { \
        return any_arg_evaluated<I>{};                            \
}                                                                 \
                                                                  \
template<std::size_t I, typename T>                               \
constexpr inline auto                                             \
__VA_ARGS__ (any_arg<I>, T&&) -> any_arg<I> {                     \
    return any_arg<I>{};                                          \
}                                                                 \
                                                                  \
template<std::size_t I, typename T>                               \
constexpr inline auto                                             \
__VA_ARGS__ (T&&, any_arg_evaluated<I>) -> any_arg_evaluated<I> { \
        return any_arg_evaluated<I>{};                            \
}                                                                 \
                                                                  \
template<std::size_t I, typename T>                               \
constexpr inline auto                                             \
__VA_ARGS__ (T&&, any_arg<I>) -> any_arg<I> {                     \
    return any_arg<I>{};                                          \
}                                                                 \
                                                                  \
template<std::size_t I, std::size_t J>                            \
constexpr inline auto                                             \
__VA_ARGS__ (any_arg_evaluated<I>, any_arg_evaluated<J>)          \
    -> any_arg_evaluated<I> {                                     \
        return any_arg_evaluated<I>{};                            \
}                                                                 \
                                                                  \
template<std::size_t I, std::size_t J>                            \
constexpr inline auto                                             \
__VA_ARGS__ (any_arg<I>, any_arg<J>) -> any_arg<I> {              \
    return any_arg<I>{};                                          \
}                                                                 \
/**/

        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator+)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator-)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator/)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator*)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator==)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator!=)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator&&)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator||)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator|)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator&)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator%)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator,)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator<<)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator>>)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator<)
        CALLABLE_TRAITS_ANY_ARG_BINARY_OPERATOR(operator>)
    }
}

#endif //CALLABLE_TRAITS_ANY_ARG_HPP
