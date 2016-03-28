/*

Copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#include <type_traits>
#include <cstdint>
#include <memory>
#include <callable_traits/callable_traits.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct three_arg_function_object {
    void operator()(char&&, float&, int = 0) {}
};

struct three_arg_function_object_with_varargs {
    void operator()(volatile char&, const float&, int = 0, ...) {}
};

struct void_function_object {
    void operator()() {}
};

struct vararg_function_object {
    void operator()(...) {}
};

struct void_function_object_default {
    void operator()(int = 0) {}
};

struct vararg_function_object_default {
    void operator()(int = 0, ...) {}
};

struct template_function_object {
    template<typename A, typename B, typename C>
    void operator()(A&&, B&, C) {}
};

struct variadic_template_function_object {
    template<typename... Args>
    void operator()(Args&&...) {}
};

struct variadic_template_function_object_plus_one {
    template<typename T, typename... Args>
    void operator()(T&&, Args&&...) {}
};

struct constrained_variadic_template_function_object {
    template<typename... Args>
    std::enable_if_t<sizeof...(Args) < 7, void> operator()(Args...) {}
};

struct simple_overloaded_function_object {
    void operator()(int, int) {}
    void operator()(int, int, int, int, int) {}
};

struct overloaded_function_object {
    void operator()(int) & {}
    void operator()(int, int) && {}
    void operator()(int, int, int) const & {}
    void operator()(int, int, int, int) const && {}
    void operator()(int, int, int, int, int) volatile & {}
    void operator()(int, int, int, int, int, int) volatile && {}
    void operator()(int, int, int, int, int, int, int) const volatile & {}
    void operator()(int, int, int, int, int, int, int, int) const volatile && {}
};

void three_arg_function(char&&, float&, int = 0) {}
void three_arg_function_with_varargs(char&&, float&, int = 0, ...) {}

void void_function() {}
void void_function_with_varargs(...) {}

namespace ct = callable_traits;
using std::is_same;

template<
    typename T,
    int ExpectedArity,
    int ExpectedMinArity,
    int ExpectedMaxArity,
    std::size_t SearchLimit
>
void test_arity() {
    CT_ASSERT(ct::arity<T>() == ExpectedArity);
    CT_ASSERT(ct::min_arity<T, SearchLimit>() == ExpectedMinArity);
    CT_ASSERT(ct::max_arity<T, SearchLimit>() == ExpectedMaxArity);
}

template<
    int ExpectedArity,
    int ExpectedMinArity,
    int ExpectedMaxArity,
    std::size_t SearchLimit,
    typename T
>
void test_arity(T&& t) {

    using arity_result = decltype(ct::arity(t));
    CT_ASSERT(arity_result{} == ExpectedArity);

    using min_arity_result = decltype(ct::min_arity<SearchLimit>(t));
    CT_ASSERT(min_arity_result{} == ExpectedMinArity);

    using max_arity_result = decltype(ct::max_arity<SearchLimit>(t));
    CT_ASSERT(max_arity_result{}  == ExpectedMaxArity);
}

constexpr const auto limit = ct::constants::arity_search_limit;
constexpr const auto limit_plus = limit + 1;
constexpr const auto limit_minus = limit - 1;

static_assert(5 <= limit_minus,
    "constants::arity_search_limit unexpectedly low for these test cases.");

namespace ctd = ct::detail;
int main() {

    {
        //testing pmf without varargs
        using F = three_arg_function_object;
        using T = decltype(&F::operator());
        test_arity<T, 3, 3, 3, limit>();
        test_arity<T, 3, 3, 3, limit_plus>();
        test_arity<T, 3, 3, 3, limit_minus>();
        test_arity<3, 3, 3, limit>(&F::operator());
        test_arity<3, 3, 3, limit_plus>(&F::operator());        
        test_arity<3, 3, 3, limit_minus>(&F::operator());
    } {
        //testing pmf with varargs
        using F = three_arg_function_object_with_varargs;
        using T = decltype(&F::operator());
        test_arity<T, 3, 3, 3, limit>();
        test_arity<T, 3, 3, 3, limit_plus>();
        test_arity<T, 3, 3, 3, limit_minus>();
        test_arity<3, 3, 3, limit>(&F::operator());
        test_arity<3, 3, 3, limit_plus>(&F::operator());
        test_arity<3, 3, 3, limit_minus>(&F::operator());
    } {
        //testing function object without varargs
        //min_arity will recognize default argument
        using T = three_arg_function_object;
        test_arity<T, 3, 2, 3, limit>();
        test_arity<T, 3, 2, 3, limit_plus>();
        test_arity<T, 3, 2, 3, limit_minus>();
        test_arity<3, 2, 3, limit>(T{});
        test_arity<3, 2, 3, limit_plus>(T{});
        test_arity<3, 2, 3, limit_minus>(T{});
    } {
        //testing function object with varargs
        //min_arity will recognize default argument
        //max_arity will recognize the varargs
        using T = three_arg_function_object_with_varargs;
        test_arity<T, 3, 2, limit, limit>();
        test_arity<T, 3, 2, limit_plus, limit_plus>();
        test_arity<T, 3, 2, limit_minus, limit_minus>();
        test_arity<3, 2, limit, limit>(T{});
        test_arity<3, 2, limit_plus, limit_plus>(T{});
        test_arity<3, 2, limit_minus, limit_minus>(T{});
    } {
        //testing void function object without varargs
        using T = void_function_object;
        test_arity<T, 0, 0, 0, limit>();
        test_arity<T, 0, 0, 0, limit_plus>();
        test_arity<T, 0, 0, 0, limit_minus>();
        test_arity<0, 0, 0, limit>(T{});
        test_arity<0, 0, 0, limit_plus>(T{});
        test_arity<0, 0, 0, limit_minus>(T{});
    } {
        //testing void function object with varargs
        //max_arity will recognize the varargs
        using T = vararg_function_object;
        test_arity<T, 0, 0, limit, limit>();
        test_arity<T, 0, 0, limit_plus, limit_plus>();
        test_arity<T, 0, 0, limit_minus, limit_minus>();
        test_arity<0, 0, limit, limit>(T{});
        test_arity<0, 0, limit_plus, limit_plus>(T{});
        test_arity<0, 0, limit_minus, limit_minus>(T{});
    } {
        //testing function object with default arg and no varargs
        //min arity will recognize the default
        using T = void_function_object_default;
        test_arity<T, 1, 0, 1, limit>();
        test_arity<T, 1, 0, 1, limit_plus>();
        test_arity<T, 1, 0, 1, limit_minus>();
        test_arity<1, 0, 1, limit>(T{});
        test_arity<1, 0, 1, limit_plus>(T{});
        test_arity<1, 0, 1, limit_minus>(T{});
    } {
        //testing function object with default arg and varargs
        //min arity will recognize the default
        //max_arity will recognize the varargs
        using T = vararg_function_object_default;
        test_arity<T, 1, 0, limit, limit>();
        test_arity<T, 1, 0, limit_plus, limit_plus>();
        test_arity<T, 1, 0, limit_minus, limit_minus>();
        test_arity<1, 0, limit, limit>(T{});
        test_arity<1, 0, limit_plus, limit_plus>(T{});
        test_arity<1, 0, limit_minus, limit_minus>(T{});
    } {
        //testing templated function object
        using T = template_function_object;
        test_arity<T, -1, 3, 3, limit>();
        test_arity<T, -1, 3, 3, limit_plus>();
        test_arity<T, -1, 3, 3, limit_minus>();
        test_arity<-1, 3, 3, limit>(T{});
        test_arity<-1, 3, 3, limit_plus>(T{});
        test_arity<-1, 3, 3, limit_minus>(T{});
    } {
        //testing templated function object
        using T = variadic_template_function_object;
        test_arity<T, -1, 0, limit, limit>();
        test_arity<T, -1, 0, limit_plus, limit_plus>();
        test_arity<T, -1, 0, limit_minus, limit_minus>();
        test_arity<-1, 0, limit, limit>(T{});
        test_arity<-1, 0, limit_plus, limit_plus>(T{});
        test_arity<-1, 0, limit_minus, limit_minus>(T{});
    } {
        //testing templated function object (plus one required arg)
        using T = variadic_template_function_object_plus_one;
        test_arity<T, -1, 1, limit, limit>();
        test_arity<T, -1, 1, limit_plus, limit_plus>();
        test_arity<T, -1, 1, limit_minus, limit_minus>();
        test_arity<-1, 1, limit, limit>(T{});
        test_arity<-1, 1, limit_plus, limit_plus>(T{});
        test_arity<-1, 1, limit_minus, limit_minus>(T{});
    } {
        //testing overloaded function object with arity gap
        using T = simple_overloaded_function_object;
        test_arity<T, -1, 2, 5, limit>();
        test_arity<T, -1, 2, 5, limit_plus>();
        test_arity<T, -1, 2, 5, limit_minus>();
        test_arity<-1, 2, 5, limit>(T{});
        test_arity<-1, 2, 5, limit_plus>(T{});
        test_arity<-1, 2, 5, limit_minus>(T{});
    } {
        //testing cv/ref qualified overloads
        //TODO make this work
        /*using T = simple_overloaded_function_object;
        test_arity<T&, -1, 1, 1, limit>();
        test_arity<T&&, -1, 2, 2, limit>();
        test_arity<T const &, -1, 3, 3, limit>();
        test_arity<T const &&, -1, 4, 4, limit>();
        test_arity<T volatile &, -1, 5, 5, limit>();
        test_arity<T volatile &&, -1, 6, 6, limit>();
        test_arity<T const volatile &, -1, 7, 7, limit>();
        test_arity<T const volatile &&, -1, 8, 8, limit>();*/
    }
    {
        //testing function without varargs
        using T = decltype(three_arg_function);
        test_arity<T, 3, 3, 3, limit>();
        test_arity<T, 3, 3, 3, limit_plus>();
        test_arity<T, 3, 3, 3, limit_minus>();
        test_arity<3, 3, 3, limit>(&three_arg_function);
        test_arity<3, 3, 3, limit_plus>(&three_arg_function);
        test_arity<3, 3, 3, limit_minus>(&three_arg_function);
    } {
        //testing function with varargs
        using T = decltype(three_arg_function_with_varargs);
        test_arity<T, 3, 3, 3, limit>();
        test_arity<T, 3, 3, 3, limit_plus>();
        test_arity<T, 3, 3, 3, limit_minus>();
        test_arity<3, 3, 3, limit>(&three_arg_function_with_varargs);
        test_arity<3, 3, 3, limit_plus>(&three_arg_function_with_varargs);
        test_arity<3, 3, 3, limit_minus>(&three_arg_function_with_varargs);
    } {
        //testing void function without varargs
        using T = decltype(void_function);
        test_arity<T, 0, 0, 0, limit>();
        test_arity<T, 0, 0, 0, limit_plus>();
        test_arity<T, 0, 0, 0, limit_minus>();
        test_arity<0, 0, 0, limit>(&void_function);
        test_arity<0, 0, 0, limit_plus>(&void_function);
        test_arity<0, 0, 0, limit_minus>(&void_function);
    } {
        //testing void function with varargs
        using T = decltype(void_function_with_varargs);
        test_arity<T, 0, 0, 0, limit>();
        test_arity<T, 0, 0, 0, limit_plus>();
        test_arity<T, 0, 0, 0, limit_minus>();
        test_arity<0, 0, 0, limit>(&void_function_with_varargs);
        test_arity<0, 0, 0, limit_plus>(&void_function_with_varargs);
        test_arity<0, 0, 0, limit_minus>(&void_function_with_varargs);
    }

    return 0;
}