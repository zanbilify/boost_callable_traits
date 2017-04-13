/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP
#define BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

#include <boost/callable_traits/detail/forward_declarations.hpp>

BOOST_CLBL_TRTS_DETAIL_NAMESPACE_BEGIN

    // Here is where the magic happens
    template<typename T>
    using traits = typename BOOST_CLBL_TRTS_DISJUNCTION(
        function_object<T>,
        function<T>,
        pmf<T>,
        pmd<T>,
        default_callable_traits<T>
    )::traits;

BOOST_CLBL_TRTS_DETAIL_NAMESPACE_END

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP
