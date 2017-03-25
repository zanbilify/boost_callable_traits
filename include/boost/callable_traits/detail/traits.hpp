/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP
#define BOOST_CLBL_TRTS_DETAIL_TRAITS_HPP

#include <boost/callable_traits/detail/utility.hpp>
#include <boost/callable_traits/detail/fwd/pmd_fwd.hpp>
#include <boost/callable_traits/detail/fwd/pmf_fwd.hpp>
#include <boost/callable_traits/detail/fwd/function_fwd.hpp>
#include <boost/callable_traits/detail/fwd/function_object_fwd.hpp>

BOOST_CLBL_TRTS_DETAIL_NAMESPACE_BEGIN

		// Here is where the magic happens
        template<typename T>
        using traits = typename BOOST_CLBL_TRTS_DISJUNCTION(
            function_object<T>,
            function<T>,
            pmf<T>,
            pmd<T>,
            function_object<T>,
            default_callable_traits<T>
        )::traits;

BOOST_CLBL_TRTS_DETAIL_NAMESPACE_END

#endif
