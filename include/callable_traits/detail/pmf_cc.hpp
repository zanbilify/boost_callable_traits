/*
Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)


DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define CALLABLE_TRAITS_SPECIALIZE_PMF_CC(QUAL)                                       \
                                                                                      \
	template<typename Ret, typename T, typename... Args>                              \
	struct add_calling_convention_t<                                                  \
		Ret(T::*)(Args...) QUAL, CALLABLE_TRAITS_CC_TAG> {                            \
		using type = Ret(CALLABLE_TRAITS_CC T::*)(Args...);                           \
	};                                                                                \
	                                                                                  \
	template<typename Ret, typename T, typename... Args>                              \
	struct add_calling_convention_t<                                                  \
		Ret(T::*)(Args..., ...) QUAL, CALLABLE_TRAITS_CC_TAG> {                       \
		using type = Ret(CALLABLE_TRAITS_CC T::*)(Args..., ...);                      \
	};                                                                                \
	                                                                                  \
    template<typename Ret, typename T, typename... Args>                              \
	struct has_calling_convention_t<                                                  \
		Ret(CALLABLE_TRAITS_CC T::*)(Args...) QUAL, CALLABLE_TRAITS_CC_TAG> {         \
		using type = std::true_type;                                                  \
	};                                                                                \
	                                                                                  \
    template<typename Ret, typename T, typename... Args>                              \
	struct has_calling_convention_t<                                                  \
		Ret(CALLABLE_TRAITS_CC T::*)(Args..., ...) QUAL, CALLABLE_TRAITS_CC_TAG> {    \
		using type = std::true_type;                                                  \
    }                                                                                 \
/**/

CALLABLE_TRAITS_SPECIALIZE_PMF_CC(CALLABLE_TRAITS_EMPTY);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(&);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(&&);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(const);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(volatile);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(const volatile);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(const &);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(volatile &);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(const volatile &);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(const &&);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(volatile &&);
CALLABLE_TRAITS_SPECIALIZE_PMF_CC(const volatile &&);

#undef CALLABLE_TRAITS_SPECIALIZE_PMF_CC
