/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_TRAITS_HPP
#define CALLABLE_TRAITS_TRAITS_HPP

#include <callable_traits/disjunction.hpp>
#include <callable_traits/general.hpp>
#include <callable_traits/function_object.hpp>
#include <callable_traits/function.hpp>
#include <callable_traits/pmf.hpp>
#include <callable_traits/default_dispatch.hpp>

#include <type_traits>

namespace callable_traits {

    namespace ctdetail {

        template<typename T>
        using remove_reference_if_ptr = typename std::conditional<
            std::is_pointer<typename std::remove_reference<T>::type>::value,
            typename std::remove_reference<T>::type,
            T
        >::type;

        template<typename T>
        using traits = typename std::conditional<
            function_object<general<T>>::value,
            typename function_object<general<T>>::dispatch_type,
            typename std::conditional<
                function<remove_reference_if_ptr<T>>::value,
                typename function<remove_reference_if_ptr<T>>::dispatch_type,
                typename std::conditional<
                    pmf<typename std::remove_reference<T>::type>::value,
                    typename pmf<typename std::remove_reference<T>::type>::dispatch_type,
                    typename default_dispatch<general<T>>::dispatch_type
                >::type
            >::type
        >::type;

        /* TODO this is eqivalent to code below - see which compiles faster.
        template<typename T>
        using traits = typename disjunction<
        function_object<general<T>>,
        function<remove_reference_if_ptr<T>>,
        pmf<typename std::remove_reference<T>::type>,
        default_dispatch<general<T>>
        >::dispatch_type;
        */
    }
}

#endif