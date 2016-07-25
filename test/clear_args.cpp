#include <tuple>
#include <utility>
#include <type_traits>
#include <callable_traits/clear_args.hpp>
#include "test.hpp"

struct foo;

int main() {

    {
        using f = void(int, int, int, int, int);
        using test =  clear_args_t<f>;
        using expect = void();
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(int, int, int, int, int) const;
        using test =  clear_args_t<f>;
        using expect = void() const;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(*)(int, int, int, int, int);
        using test =  clear_args_t<f>;
        using expect = void(*)();
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(&)(int, int, int, int, int);
        using test =  clear_args_t<f>;
        using expect = void(&)();
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(&)(int, int, int, int, int);
        using test =  clear_args_t<f>;
        using expect = void(&)();
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(foo::*)(int, int, int, int, int);
        using test =  clear_args_t<f>;
        using expect = void(foo::*)();
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(foo::*)(int, int, int, int, int) volatile;
        using test =  clear_args_t<f>;
        using expect = void(foo::*)() volatile;
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}

