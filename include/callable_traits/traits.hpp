/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_TRAITS_HPP
#define CALLABLE_TRAITS_TRAITS_HPP


#include <callable_traits/general.hpp>
#include <callable_traits/disjunction.hpp>
#include <callable_traits/remove_reference_if_ptr.hpp>
#include <callable_traits/default_dispatch.hpp>
#include <callable_traits/fwd/pmd_fwd.hpp>
#include <callable_traits/fwd/pmf_fwd.hpp>
#include <callable_traits/fwd/function_fwd.hpp>
#include <callable_traits/fwd/function_object_fwd.hpp>

#include <type_traits>

namespace callable_traits {

    namespace ctdetail {

        template<typename T>
        using shallow_decay = typename std::remove_cv<
            typename std::remove_reference<T>::type
        >::type;

        template<typename T>
        using traits = 

            //if function object
            typename std::conditional<function_object<general<T>>::value,

                // return function object traits
                function_object<general<T>>,

                //else if valid function/function ptr/function reference
                typename std::conditional<function<remove_reference_if_ptr<T>>::value,

                    //return function traits
                    function<remove_reference_if_ptr<T>>,

                    //else if valid pointer to member function
                    typename std::conditional<pmf<shallow_decay<T>>::value,
                        
                        //return pointer to member function traits
                        pmf<shallow_decay<T>>,

                        //else if valid pointer to member data
                        typename std::conditional<pmd<shallow_decay<T>>::value,

                            //return pointer to member data traits
                            pmd<shallow_decay<T>>,

                            //else return default
                            function_object<general<T>>
                        >::type
                    >::type
                >::type
            >::type::traits;

        /* TODO this is eqivalent to code below - see which compiles faster.
        template<typename T>
        using traits = typename disjunction<
        function_object<general<T>>,
        function<remove_reference_if_ptr<T>>,
        pmf<typename std::remove_reference<T>::type>,
        default_dispatch<general<T>>
        >;
        */
    }
}

#endif