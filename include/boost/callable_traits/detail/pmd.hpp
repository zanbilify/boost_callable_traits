/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_PMD_HPP
#define BOOST_CLBL_TRTS_DETAIL_PMD_HPP


#include <boost/callable_traits/detail/fwd/function_object_fwd.hpp>
#include <boost/callable_traits/detail/function.hpp>
#include <boost/callable_traits/detail/traits.hpp>
#include <boost/callable_traits/detail/default_callable_traits.hpp>
#include <boost/callable_traits/detail/utility.hpp>

BOOST_CLBL_TRTS_DETAIL_NAMESPACE_BEGIN

        template<typename T>
        struct pmd : default_callable_traits<T> {};

        template<typename D, typename T>
        struct pmd<D T::*>
            : default_callable_traits<> {
                
            static constexpr bool value = true;

            using traits = pmd;   
            using class_type = T;
            using invoke_type = T const &;
            using type = D T::*;
            using function_type = typename std::add_lvalue_reference<D>::type(invoke_type);
            using qualified_function_type = D(invoke_type);
            using arg_types = std::tuple<invoke_type>;
            using non_invoke_arg_types = std::tuple<>;

            using return_type = typename std::add_lvalue_reference<D>::type;

            template<typename C>
            using apply_member_pointer = D C::*;

            template<typename R>
            using apply_return = R T::*;

            template<template<class...> class Container>
            using expand_args = Container<invoke_type>;
        };

BOOST_CLBL_TRTS_DETAIL_NAMESPACE_END

#endif
