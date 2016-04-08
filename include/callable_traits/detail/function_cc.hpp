/*
Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)


DO NOT INCLUDE THIS HEADER DIRECTLY
*/

template<typename Ret, typename... Args>
struct add_calling_convention_t<
	Ret(*)(Args...), CALLABLE_TRAITS_CC_TAG> {
	using type = CALLABLE_TRAITS_ST Ret(CALLABLE_TRAITS_CC*)(Args...);
};

template<typename Ret, typename... Args>
struct add_calling_convention_t<
	Ret(*)(Args..., ...), CALLABLE_TRAITS_CC_TAG> {
	using type = CALLABLE_TRAITS_ST Ret(CALLABLE_TRAITS_CC*)(Args..., ...);
};

template<typename Ret, typename... Args>
struct has_calling_convention_t<
	CALLABLE_TRAITS_ST Ret(CALLABLE_TRAITS_CC*)(Args...), CALLABLE_TRAITS_CC_TAG> {
	using type = std::true_type;
};

template<typename Ret, typename... Args>
struct has_calling_convention_t<
	CALLABLE_TRAITS_ST Ret(CALLABLE_TRAITS_CC*)(Args..., ...), CALLABLE_TRAITS_CC_TAG> {
	using type = std::true_type;
};