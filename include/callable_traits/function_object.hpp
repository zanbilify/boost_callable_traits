/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FUNCTION_OBJECT_HPP
#define CALLABLE_TRAITS_FUNCTION_OBJECT_HPP

#include <callable_traits/general.hpp>
#include <callable_traits/pmf.hpp>
#include <callable_traits/has_normal_call_operator.hpp>
#include <callable_traits/tags.hpp>

#include <tuple>

namespace callable_traits {

    namespace ctdetail {

        template<typename General>
        struct ambiguous_function_object {
            using arg_types = std::tuple<ambiguous_type>;
            using return_type = ambiguous_type;
        };

        template<typename General>
        struct function_object
            : public std::conditional<
                has_normal_call_operator<typename General::type>::value,
                pmf<decltype(&default_normal_callable<typename General::type>::operator())>,
                ambiguous_function_object<General>
            >::type {

            using type = typename General::type;
            static constexpr const bool value = std::is_class<type>::value;
            static constexpr const bool is_ambiguous = !has_normal_call_operator<type>::value;
            using dispatch_type = function_object;
            using class_type = invalid_type;
            using invoke_type = invalid_type;
            using is_function_object = std::true_type;
            static constexpr const bool is_member_function_ptr = false;
            static constexpr const bool is_function_ptr = false;
        };

        template<typename T, typename U>
        struct function_object <general<T U::*> > {
            static constexpr const bool is_valid = false;
            static constexpr const bool value = is_valid;
            using dispatch_type = function_object;
        };
    }
}

#endif