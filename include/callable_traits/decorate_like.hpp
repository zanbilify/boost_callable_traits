/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DECORATE_LIKE_HPP
#define CALLABLE_TRAITS_DECORATE_LIKE_HPP

#include <callable_traits/can_dereference.hpp>
#include <callable_traits/function.hpp>
#include <callable_traits/member_pointer_utilities.hpp>
#include <type_traits>
#include <memory>
#include <utility>

namespace callable_traits {

    namespace ctdetail {

        template<typename T>
        struct remove_reference_wrapper {
            using type = T;
        };

        template<typename T>
        struct remove_reference_wrapper<std::reference_wrapper<T>> {
            using type = T;
        };

        template<typename T>
        struct remove_weak_ptr : std::false_type {
            using type = T;
        };

        template<typename T>
        struct remove_weak_ptr<std::weak_ptr<T>> : std::true_type {
            using type = T;
        };

        template<typename T>
        using dereferenceable = typename std::conditional<
            can_dereference<T>::value,
            T,
            typename remove_weak_ptr<T>::type*
        >::type;

        template<typename T>
        using hard_dereference = 
            typename std::remove_reference<
            decltype(*std::declval<dereferenceable<T>>())
        >::type;

        template<typename T, typename U = typename std::conditional<
            std::is_member_pointer<T>::value,
            remove_member_pointer<T>,
            hard_dereference<typename std::remove_reference<T>::type>
        >::type>
        struct dereferenced : std::is_same<T, U> {};

        template<
        typename T, 
        typename U = typename std::remove_reference<
                typename remove_reference_wrapper<T>::type
            >::type
        >
        struct reference_removed : std::is_same<T, U> {};

        template<typename T, typename U = typename std::remove_cv<T>::type>
        struct cv_removed : std::is_same<T, U> {};

        template<typename T>
        struct end_decorator {

            using decay_type = T;

            template<typename U>
            using apply = U;
        };

        template<typename T>
        struct reference_decorator;

        template<typename T>
        struct cv_decorator;

        template<typename T>
        struct pointer_decorator;

        template<typename T>
        using next_decorator_after_cv = typename std::conditional<
            reference_removed<T>::value 
                && dereferenced<T>::value,
            end_decorator<T>,
            reference_decorator<T>
        >::type;


        template<typename T>
        struct cv_decorator {

            using next = next_decorator_after_cv<T>;
            using decay_type = typename next::decay_type;
            
            template<typename U>
            using apply = typename next::template apply<U>;
        };

        template<typename T>
        struct cv_decorator<const T> {

            using next = next_decorator_after_cv<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = typename std::add_const<typename next::template apply<U>>::type;
        };

        template<typename T>
        struct cv_decorator<volatile T> {

            using next = next_decorator_after_cv<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = typename std::add_volatile<typename next::template apply<U>>::type;
        };

        template<typename T>
        struct cv_decorator<const volatile T> {

            using next = next_decorator_after_cv<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = typename std::add_cv<typename next::template apply<U>>::type;
        };

        template<typename T>
        using next_decorator_after_pointer = typename std::conditional <
            cv_removed<T>::value,
            next_decorator_after_cv<T>,
            cv_decorator<T>
        >::type;

        template<typename T>
        struct pointer_decorator {

            using next = next_decorator_after_pointer<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = typename next::template apply<U>;
        };

        template<typename T>
        struct pointer_decorator<T*> {

            using next = next_decorator_after_pointer<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = typename next::template apply<U>*;
        };

        template<typename T>
        struct pointer_decorator<std::shared_ptr<T>> {

            using next = next_decorator_after_pointer<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = std::shared_ptr<typename next::template apply<U>>;
        };

        template<typename T>
        struct pointer_decorator<std::weak_ptr<T>> {

            using next = next_decorator_after_pointer<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = std::weak_ptr<typename next::template apply<U>>;
        };

        template<typename T>
        struct pointer_decorator<std::unique_ptr<T>> {

            using next = next_decorator_after_pointer<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = std::unique_ptr<typename next::template apply<U>>;
        };

        template<typename T, typename C>
        struct pointer_decorator<T C::*> {

            using next = next_decorator_after_pointer<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = typename next::template apply<U> C::*;
        };

        template<typename T>
        using next_decorator_after_reference = typename std::conditional<
            cv_removed<T>::value,
            pointer_decorator<T>,
            cv_decorator<T>
        >::type;

        template<typename T>
        struct reference_decorator {

            using next = next_decorator_after_reference<T>;
            using decay_type = typename next::decay_type;
            
            template<typename U>
            using apply = typename next::template apply<U>;
        };

        template<typename T>
        struct reference_decorator<T&> {

            using next = next_decorator_after_reference<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = typename next::template apply<U>&;
        };

        template<typename T>
        struct reference_decorator<T&&> {

            using next = next_decorator_after_reference<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = typename next::template apply<U>&&;
        };

        template<typename T>
        struct reference_decorator<std::reference_wrapper<T>> {

            using next = next_decorator_after_reference<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = std::reference_wrapper<typename next::template apply<U>>;
        };

        template<typename T>
        struct reference_decorator<std::reference_wrapper<T>&> {

            using next = next_decorator_after_reference<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = std::reference_wrapper<typename next::template apply<U>>&;
        };

        template<typename T>
        struct reference_decorator<std::reference_wrapper<T>&&> {
  
            using next = next_decorator_after_reference<T>;
            using decay_type = typename next::decay_type;

            template<typename U>
            using apply = std::reference_wrapper<typename next::template apply<U>>&&;
        };

    }

    template<typename T>
    using deep_decay = typename ctdetail::reference_decorator<T>::decay_type;

    template<typename Model>
    using decorator =  ctdetail::reference_decorator<Model>;

    template<typename Model, typename Target>
    using decorate_like = typename ctdetail::reference_decorator<Model>::template apply<Target>;
}

#endif