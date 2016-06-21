/*!
@copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_SFINAE_ERRORS_HPP
#define CALLABLE_TRAITS_SFINAE_ERRORS_HPP

#include <callable_traits/config.hpp>
#include <type_traits>

namespace callable_traits {

    namespace detail {

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
    }

#define CALLABLE_TRAITS_PP_CAT_(x, y) x ## y
#define CALLABLE_TRAITS_PP_CAT(x, y) CALLABLE_TRAITS_PP_CAT_(x, y)

#define CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(origin)     \
namespace callable_traits_ERROR {                              \
    template<typename ErrorMessage>                            \
    struct origin :                                            \
        ::callable_traits::detail::sfinae_error                \
        { struct _ {}; };                                      \
}                                                              \
/**/

#define CALLABLE_TRAITS_SFINAE_MSG(origin, name)    \
struct CALLABLE_TRAITS_PP_CAT(name, _ ){};                       \
struct name : callable_traits_ERROR::origin<                     \
    CALLABLE_TRAITS_PP_CAT(name, _ )>{};                         \
/**/


    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(parameters)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(clear_args)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(apply_return)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(parent_class)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(apply_member_pointer)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(varargs)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(member_qualifiers)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(transaction_safe_error)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(add_transaction_safe)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(expand_args)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(remove_transaction_safe)
    CALLABLE_TRAITS_DEFINE_SFINAE_ERROR_ORIGIN(return_type)

    CALLABLE_TRAITS_SFINAE_MSG(parameters,              index_out_of_range_for_parameter_list)
    CALLABLE_TRAITS_SFINAE_MSG(parameters,              cannot_determine_parameters_for_this_type)
    CALLABLE_TRAITS_SFINAE_MSG(clear_args,              cannot_clear_the_parameter_list_for_this_type)
    CALLABLE_TRAITS_SFINAE_MSG(apply_return,            invalid_types_for_apply_return)
    CALLABLE_TRAITS_SFINAE_MSG(parent_class,            type_is_not_a_member_pointer)
    CALLABLE_TRAITS_SFINAE_MSG(apply_member_pointer,    members_cannot_have_a_type_of_void)
    CALLABLE_TRAITS_SFINAE_MSG(apply_member_pointer,    second_template_argument_must_be_a_class_or_struct)
    CALLABLE_TRAITS_SFINAE_MSG(member_qualifiers,       member_qualifiers_are_illegal_for_this_type)
    CALLABLE_TRAITS_SFINAE_MSG(varargs,                 varargs_are_illegal_for_this_type)
    CALLABLE_TRAITS_SFINAE_MSG(transaction_safe_error,  transaction_safe_is_not_enabled_on_this_platform)
    CALLABLE_TRAITS_SFINAE_MSG(add_transaction_safe,    cannot_add_transaction_safe_to_this_type)
    CALLABLE_TRAITS_SFINAE_MSG(remove_transaction_safe, cannot_remove_transaction_safe_from_this_type)
    CALLABLE_TRAITS_SFINAE_MSG(expand_args,             cannot_expand_the_parameter_list_of_first_template_argument)
    CALLABLE_TRAITS_SFINAE_MSG(return_type,               unable_to_determine_return_type)
}
#endif // #ifndef CALLABLE_TRAITS_SFINAE_ERRORS_HPP
