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
#include <callable_traits/is_bind_expression.hpp>
#include <callable_traits/bind_expression_traits.hpp>
#include <callable_traits/shallow_decay.hpp>

#include <type_traits>

namespace callable_traits {

    namespace ctdetail {

        template<typename T, typename Decayed = shallow_decay<T>>
        using traits = 

            //if is bind expression
            typename std::conditional<
                bind_expression_traits<Decayed>::value,

                //return bind expression traits
                bind_expression_traits<Decayed>,

            //else if valid function object
            typename std::conditional<function_object<general<T>>::value,

                //return function object traits
                function_object<general<T>>,

           //else if valid function type/function ptr/function reference
           typename std::conditional<function<remove_reference_if_ptr<T>>::value,

                //return function traits
                function<remove_reference_if_ptr<T>>,

           //else if valid pointer to member function
           typename std::conditional<pmf<Decayed>::value,
                        
               //return pointer to member function traits
               pmf<Decayed>,

          //else if valid pointer to member data
          typename std::conditional<pmd<Decayed>::value,

               //return pointer to member data traits
               pmd<Decayed>,

          //else default to function object
          function_object<general<T>>

          >::type>::type>::type>::type>::type::traits;


        /* this produces the same result, but appears to compile slower. TODO benchmark
        template<typename T>
        using traits = typename disjunction<
            bind_expression_traits<shallow_decay<T>>,
            function_object<general<T>>,
            function<remove_reference_if_ptr<T>>,
            pmf<shallow_decay<T>>,
            pmd<shallow_decay<T>>,
            function_object<general<T>>
        >::traits;*/
    }
}

#endif
