/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_REMOVE_MEMBER_CV_HPP
#define CALLABLE_TRAITS_REMOVE_MEMBER_CV_HPP

#include <callable_traits/detail/core.hpp>


namespace callable_traits {

    template<typename T>
    struct remove_member_cv {

        using type = detail::fail_if_invalid<
            typename detail::traits<T>::remove_member_cv,
            member_qualifiers_are_illegal_for_this_type>;
    };

    template<typename T>
    using remove_member_cv_t =
        typename remove_member_cv<T>::type;
}

#endif
