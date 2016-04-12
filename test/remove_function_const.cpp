/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/remove_function_const.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct foo {};

namespace ct = callable_traits;

int main() {

    {
        using f =   void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...);
        using l =   void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) &;
        using r =   void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) && ;
        using c =   void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const;
        using cl =  void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const &;
        using cr =  void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const &&;
        using v =   void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) volatile;
        using vl =  void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) volatile &;
        using vr =  void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) volatile &&;
        using cv =  void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const volatile;
        using cvl = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const volatile &;
        using cvr = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(...) const volatile &&;

        CT_ASSERT(std::is_same<f,   ct::remove_function_const<f>>{});
        CT_ASSERT(std::is_same<f,   ct::remove_function_const<c>>{});
        CT_ASSERT(std::is_same<l,  ct::remove_function_const<l>>{});
        CT_ASSERT(std::is_same<l,  ct::remove_function_const<cl>>{});
        CT_ASSERT(std::is_same<r,  ct::remove_function_const<r>>{});
        CT_ASSERT(std::is_same<r,  ct::remove_function_const<cr>>{});
        CT_ASSERT(std::is_same<v,  ct::remove_function_const<v>>{});
        CT_ASSERT(std::is_same<v,  ct::remove_function_const<cv>>{});
        CT_ASSERT(std::is_same<vl, ct::remove_function_const<vl>>{});
        CT_ASSERT(std::is_same<vl, ct::remove_function_const<cvl>>{});
        CT_ASSERT(std::is_same<vr, ct::remove_function_const<vr>>{});
        CT_ASSERT(std::is_same<vr, ct::remove_function_const<cvr>>{});
    }

    {
        using f =   foo const & (foo::* const volatile &)(int, int);
        using l =   foo const & (foo::* const volatile &)(int, int) &;
        using r =   foo const & (foo::* const volatile &)(int, int) && ;
        using c =   foo const & (foo::* const volatile &)(int, int) const;
        using cl =  foo const & (foo::* const volatile &)(int, int) const &;
        using cr =  foo const & (foo::* const volatile &)(int, int) const &&;
        using v =   foo const & (foo::* const volatile &)(int, int) volatile;
        using vl =  foo const & (foo::* const volatile &)(int, int) volatile &;
        using vr =  foo const & (foo::* const volatile &)(int, int) volatile &&;
        using cv =  foo const & (foo::* const volatile &)(int, int) const volatile;
        using cvl = foo const & (foo::* const volatile &)(int, int) const volatile &;
        using cvr = foo const & (foo::* const volatile &)(int, int) const volatile &&;

        CT_ASSERT(std::is_same<f,   ct::remove_function_const<f>>{});
        CT_ASSERT(std::is_same<f,   ct::remove_function_const<c>>{});
        CT_ASSERT(std::is_same<l,  ct::remove_function_const<l>>{});
        CT_ASSERT(std::is_same<l,  ct::remove_function_const<cl>>{});
        CT_ASSERT(std::is_same<r,  ct::remove_function_const<r>>{});
        CT_ASSERT(std::is_same<r,  ct::remove_function_const<cr>>{});
        CT_ASSERT(std::is_same<v,  ct::remove_function_const<v>>{});
        CT_ASSERT(std::is_same<v,  ct::remove_function_const<cv>>{});
        CT_ASSERT(std::is_same<vl, ct::remove_function_const<vl>>{});
        CT_ASSERT(std::is_same<vl, ct::remove_function_const<cvl>>{});
        CT_ASSERT(std::is_same<vr, ct::remove_function_const<vr>>{});
        CT_ASSERT(std::is_same<vr, ct::remove_function_const<cvr>>{});
    }

    {
        using f =   void();
        using l =   void() &;
        using r =   void() && ;
        using c =   void() const;
        using cl =  void() const &;
        using cr =  void() const &&;
        using v =   void() volatile;
        using vl =  void() volatile &;
        using vr =  void() volatile &&;
        using cv =  void() const volatile;
        using cvl = void() const volatile &;
        using cvr = void() const volatile &&;

        CT_ASSERT(std::is_same<f,   ct::remove_function_const<f>>{});
        CT_ASSERT(std::is_same<f,   ct::remove_function_const<c>>{});
        CT_ASSERT(std::is_same<l,  ct::remove_function_const<l>>{});
        CT_ASSERT(std::is_same<l,  ct::remove_function_const<cl>>{});
        CT_ASSERT(std::is_same<r,  ct::remove_function_const<r>>{});
        CT_ASSERT(std::is_same<r,  ct::remove_function_const<cr>>{});
        CT_ASSERT(std::is_same<v,  ct::remove_function_const<v>>{});
        CT_ASSERT(std::is_same<v,  ct::remove_function_const<cv>>{});
        CT_ASSERT(std::is_same<vl, ct::remove_function_const<vl>>{});
        CT_ASSERT(std::is_same<vl, ct::remove_function_const<cvl>>{});
        CT_ASSERT(std::is_same<vr, ct::remove_function_const<vr>>{});
        CT_ASSERT(std::is_same<vr, ct::remove_function_const<cvr>>{});
    }
}
