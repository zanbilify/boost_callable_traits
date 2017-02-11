/*
@copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_SFINAE_ERRORS_HPP
#define CALLABLE_TRAITS_SFINAE_ERRORS_HPP

#include <boost/callable_traits/config.hpp>

CALLABLE_TRAITS_DETAIL_NAMESPACE_BEGIN

        struct sfinae_error{};

        template<typename T>
        struct success {
            static constexpr bool value = true;
            struct _ { using type = T; };
        };
    
        template<bool B, typename T>
        struct fail_if : T {

            static_assert(std::is_base_of<sfinae_error, T>::value,
                "incorrect usage of fail_if");

            static constexpr bool value = B;
        };

        template<typename T, typename... FailIfs>
        using sfinae_try = typename CALLABLE_TRAITS_DISJUNCTION(
                FailIfs..., success<T>)::_::type;

        template<typename FailMsg, typename ForceTwoPhaseLookup>
        struct fail {
            using type = typename std::conditional<sizeof(ForceTwoPhaseLookup*) < 1,
            FailMsg, FailMsg>::type::_::type;
        };

CALLABLE_TRAITS_DETAIL_NAMESPACE_END

#define CALLABLE_TRAITS_PP_CAT_(x, y) x ## y
#define CALLABLE_TRAITS_PP_CAT(x, y) CALLABLE_TRAITS_PP_CAT_(x, y)

#define CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(origin) \
namespace error {                                          \
    template<typename ErrorMessage>                        \
    struct origin :                                        \
        ::boost::callable_traits::detail::sfinae_error     \
        { struct _ {}; };                                  \
}                                                          \
/**/

#define CALLABLE_TRAITS_SFINAE_MSG(origin, name) \
struct CALLABLE_TRAITS_PP_CAT(name, _ ){};       \
struct name : error::origin<                     \
    CALLABLE_TRAITS_PP_CAT(name, _ )>{};         \
/**/

CALLABLE_TRAITS_NAMESPACE_BEGIN

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(parameters)
    CALLABLE_TRAITS_SFINAE_MSG(parameters, index_out_of_range_for_parameter_list)
    CALLABLE_TRAITS_SFINAE_MSG(parameters, cannot_determine_parameters_for_this_type)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(varargs)
    CALLABLE_TRAITS_SFINAE_MSG(varargs, varargs_are_illegal_for_this_type)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(member_qualifiers)
    CALLABLE_TRAITS_SFINAE_MSG(member_qualifiers, member_qualifiers_are_illegal_for_this_type)
    CALLABLE_TRAITS_SFINAE_MSG(member_qualifiers, this_compiler_doesnt_support_abominable_function_types)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(transaction_safe_)
    CALLABLE_TRAITS_SFINAE_MSG(transaction_safe_, transaction_safe_is_not_supported_by_this_configuration)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(expand_args)
    CALLABLE_TRAITS_SFINAE_MSG(expand_args, cannot_expand_the_parameter_list_of_first_template_argument)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(member_pointer_required)
    CALLABLE_TRAITS_SFINAE_MSG(member_pointer_required, type_is_not_a_member_pointer)

    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(reference_error)
    CALLABLE_TRAITS_SFINAE_MSG(reference_error, reference_type_not_supported_by_this_metafunction)

CALLABLE_TRAITS_NAMESPACE_END

#endif // #ifndef CALLABLE_TRAITS_SFINAE_ERRORS_HPP
