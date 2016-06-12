/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ARG_AT_HPP
#define CALLABLE_TRAITS_ARG_AT_HPP

#include <callable_traits/args.hpp>
#include <callable_traits/detail/core.hpp>
#include <tuple>

namespace callable_traits {

    template<std::size_t I, typename T>
    struct arg_at {

        private:

            using arg_types = typename args<T>::type;

        public:

        // SFINAEs away if index is out of range or if argument
        // types cannot be determined. Simple error messages are
        // provided in case the error occurs outside of a SFINAE context

        using type = detail::sfinae_try<

            detail::at<I, arg_types>,

            detail::fail_if<I >= std::tuple_size<arg_types>::value,
                index_out_of_range_for_parameter_list>
        >;
    };

    template<std::size_t I, typename T>
    using arg_at_t = typename arg_at<I, T>::type;
}

#endif
