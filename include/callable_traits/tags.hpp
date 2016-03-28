/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_TAGS_HPP
#define CALLABLE_TRAITS_TAGS_HPP

#define CALLABLE_TRAITS_EMPTY_
#define CALLABLE_TRAITS_EMPTY CALLABLE_TRAITS_EMPTY_

#ifdef _MSC_VER
#define CALLABLE_TRAITS_VARARGS_CC __cdecl
#else
#define CALLABLE_TRAITS_VARARGS_CC
#endif //_MSC_VER

namespace callable_traits {

    namespace detail {
        struct pmf_tag {};
        struct pmd_tag {};
        struct function_tag {};
        struct function_reference_tag : function_tag {};
        struct function_ptr_tag : function_tag {};
        struct function_object_tag {};
        struct ambiguous_function_object_tag : function_object_tag {};
        struct dummy {};
    }
    
    struct constants {
        static constexpr std::size_t arity_search_limit = 10;
    };

    struct invalid_type { invalid_type() = delete; };
    struct unknown { unknown() = delete; };
}


#endif