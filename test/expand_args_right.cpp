#include <tuple>
#include <utility>
#include <type_traits>
#include <callable_traits/expand_args_right.hpp>
#include "test.hpp"

struct foo;

template<int I>
struct N {};

int main() {

    {
        using f = void(N<0>, N<1>);
        using test =  expand_args_right_t<f, std::tuple, char, int>;
        using expect = std::tuple<char, int, N<0>, N<1>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

#ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS
    {
        using f = void(N<0>, N<1>) const volatile;
        using test =  expand_args_right_t<f, std::tuple, char, int>;
        using expect = std::tuple<char, int, N<0>, N<1>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }
#endif // #ifndef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS

    {
        using f = void(&)(N<0>, N<1>);
        using test =  expand_args_right_t<f, std::tuple, char, int>;
        using expect = std::tuple<char, int, N<0>, N<1>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(*)(N<0>, N<1>);
        using test =  expand_args_right_t<f, std::tuple, char, int>;
        using expect = std::tuple<char, int, N<0>, N<1>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(foo::*)(N<0>, N<1>);
        using test =  expand_args_right_t<f, std::tuple, char, int>;
        using expect = std::tuple<char, int, foo&, N<0>, N<1>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(foo::*)(N<0>, N<1>) const;
        using test =  expand_args_right_t<f, std::tuple, char, int>;
        using expect = std::tuple<char, int, foo const &, N<0>, N<1>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}
