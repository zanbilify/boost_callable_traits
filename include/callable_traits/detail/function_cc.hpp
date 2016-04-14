/*
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

template<typename Ret, typename... Args>
struct add_calling_convention_t<
    Ret(*)(Args...), CALLABLE_TRAITS_CC_TAG> {
    using type = CALLABLE_TRAITS_ST Ret(CALLABLE_TRAITS_CC*)(Args...);
};

template<typename Ret, typename... Args>
struct has_calling_convention_t<
    CALLABLE_TRAITS_ST Ret(CALLABLE_TRAITS_CC*)(Args...), CALLABLE_TRAITS_CC_TAG> {
    using type = std::true_type;
};

template<typename OriginalType, typename Return, typename... Args>
struct function<OriginalType, CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_CC *)(Args...)>
 : qualifier_traits<dummy>, default_callable_traits {

    static constexpr bool value = true;

    using is_function = std::true_type;
    using is_functionish = std::true_type;
    using traits = function;
    using return_type = Return;
    using arg_types = std::tuple<Args...>;
    using invoke_arg_types = arg_types;
    using remove_calling_convention = Return(*)(Args...);

    using type =
        CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_CC *)(Args...);

    using function_type = Return(Args...);
    using qualified_function_type = function_type;
    using remove_varargs = OriginalType;

    using add_varargs = typename copy_cvr<
        CALLABLE_TRAITS_ST Return (CALLABLE_TRAITS_VARARGS_CC *)(Args..., ...),
        OriginalType
    >::type;

    using remove_member_pointer = OriginalType;

    template<typename U>
    using apply_member_pointer = typename copy_cvr<
        CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_CC U::*)(Args...),
        OriginalType
    >::type;

    template<typename NewReturn>
    using apply_return = typename copy_cvr<
        CALLABLE_TRAITS_ST NewReturn(CALLABLE_TRAITS_CC *)(Args...),
        OriginalType
    >::type;

	using clear_args = typename copy_cvr<
		CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_CC *)(),
		OriginalType
	>::type;
	
    template<typename... NewArgs>
    using push_args_front = typename copy_cvr<
		CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_CC *)(NewArgs..., Args...),
		OriginalType
	>::type;

	template<typename... NewArgs>
	using push_args_back = typename copy_cvr<
		CALLABLE_TRAITS_ST Return(CALLABLE_TRAITS_CC *)(Args..., NewArgs...),
        OriginalType
	>::type;
};

