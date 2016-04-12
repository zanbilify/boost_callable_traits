/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/add_function_cv.hpp>

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

        CT_ASSERT(std::is_same<cv,   ct::add_function_cv<f>>{});
        CT_ASSERT(std::is_same<cv,   ct::add_function_cv<c>>{});
        CT_ASSERT(std::is_same<cvl,  ct::add_function_cv<l>>{});
        CT_ASSERT(std::is_same<cvl,  ct::add_function_cv<cl>>{});
        CT_ASSERT(std::is_same<cvr,  ct::add_function_cv<r>>{});
        CT_ASSERT(std::is_same<cvr,  ct::add_function_cv<cr>>{});
        CT_ASSERT(std::is_same<cv,  ct::add_function_cv<v>>{});
        CT_ASSERT(std::is_same<cv,  ct::add_function_cv<cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_function_cv<vl>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_function_cv<cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_function_cv<vr>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_function_cv<cvr>>{});
    }

    {
        using f =   void(foo::* volatile)(int, int);
        using l =   void(foo::* volatile)(int, int) &;
        using r =   void(foo::* volatile)(int, int) && ;
        using c =   void(foo::* volatile)(int, int) const;
        using cl =  void(foo::* volatile)(int, int) const &;
        using cr =  void(foo::* volatile)(int, int) const &&;
        using v =   void(foo::* volatile)(int, int) volatile;
        using vl =  void(foo::* volatile)(int, int) volatile &;
        using vr =  void(foo::* volatile)(int, int) volatile &&;
        using cv =  void(foo::* volatile)(int, int) const volatile;
        using cvl = void(foo::* volatile)(int, int) const volatile &;
        using cvr = void(foo::* volatile)(int, int) const volatile &&;

        CT_ASSERT(std::is_same<cv,   ct::add_function_cv<f>>{});
        CT_ASSERT(std::is_same<cv,   ct::add_function_cv<c>>{});
        CT_ASSERT(std::is_same<cvl,  ct::add_function_cv<l>>{});
        CT_ASSERT(std::is_same<cvl,  ct::add_function_cv<cl>>{});
        CT_ASSERT(std::is_same<cvr,  ct::add_function_cv<r>>{});
        CT_ASSERT(std::is_same<cvr,  ct::add_function_cv<cr>>{});
        CT_ASSERT(std::is_same<cv,  ct::add_function_cv<v>>{});
        CT_ASSERT(std::is_same<cv,  ct::add_function_cv<cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_function_cv<vl>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_function_cv<cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_function_cv<vr>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_function_cv<cvr>>{});
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

        CT_ASSERT(std::is_same<cv,   ct::add_function_cv<f>>{});
        CT_ASSERT(std::is_same<cv,   ct::add_function_cv<c>>{});
        CT_ASSERT(std::is_same<cvl,  ct::add_function_cv<l>>{});
        CT_ASSERT(std::is_same<cvl,  ct::add_function_cv<cl>>{});
        CT_ASSERT(std::is_same<cvr,  ct::add_function_cv<r>>{});
        CT_ASSERT(std::is_same<cvr,  ct::add_function_cv<cr>>{});
        CT_ASSERT(std::is_same<cv,  ct::add_function_cv<v>>{});
        CT_ASSERT(std::is_same<cv,  ct::add_function_cv<cv>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_function_cv<vl>>{});
        CT_ASSERT(std::is_same<cvl, ct::add_function_cv<cvl>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_function_cv<vr>>{});
        CT_ASSERT(std::is_same<cvr, ct::add_function_cv<cvr>>{});
    }
}
