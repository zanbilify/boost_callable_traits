 /*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_MAKE_CONSTEXPR_HPP
#define CALLABLE_TRAITS_DETAIL_MAKE_CONSTEXPR_HPP

#include <callable_traits/detail/shallow_decay.hpp>

#include <type_traits>
#include <utility>

#define CALLABLE_TRAITS_MAKE_CONSTEXPR(T)                                                \
static_cast<T>(                                                                          \
    const_cast<typename ::callable_traits::detail::make_constexpr<T>::const_cast_type>(  \
        ::callable_traits::detail::make_constexpr<T>::value                              \
    )                                                                                    \
)                                                                                        \
/**/

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct make_constexpr {
            
            using decayed = shallow_decay<T>;
            
            static constexpr decayed value = decayed{};

            using const_cast_type = typename std::conditional<
                std::is_rvalue_reference<T>::value,
                decayed&&,
                decayed&
            >::type;
        };
    }
}

#endif
