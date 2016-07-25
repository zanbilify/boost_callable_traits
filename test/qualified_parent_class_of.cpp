#include <tuple>
#include <utility>
#include <type_traits>
#include <callable_traits/qualified_parent_class_of.hpp>
#include "test.hpp"

struct foo;

int main() {

    {
        using f = void(foo::*)();
        using test =  qualified_parent_class_of_t<f>;
        using expect = foo &;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(foo::*)() const;
        using test =  qualified_parent_class_of_t<f>;
        using expect = foo const &;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(foo::*)() volatile;
        using test =  qualified_parent_class_of_t<f>;
        using expect = foo volatile &;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int, ...) const volatile;
        using test =  qualified_parent_class_of_t<f>;
        using expect = foo const volatile &;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = int foo::*;
        using test =  qualified_parent_class_of_t<f>;
        using expect = foo const &;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = const int foo::*;
        using test =  qualified_parent_class_of_t<f>;
        using expect = foo const &;
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}
