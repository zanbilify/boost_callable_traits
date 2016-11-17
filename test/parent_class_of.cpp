#include <tuple>
#include <utility>
#include <type_traits>
#include <boost/callable_traits/parent_class_of.hpp>
#include "test.hpp"

struct foo;

int main() {

    {
        using f = void(foo::*)();
        using test =  parent_class_of_t<f>;
        using expect = foo;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(foo::*)() const;
        using test =  parent_class_of_t<f>;
        using expect = foo;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(foo::*)() volatile;
        using test =  parent_class_of_t<f>;
        using expect = foo;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = void(CALLABLE_TRAITS_DEFAULT_VARARGS_CC foo::*)(int, ...) const volatile;
        using test =  parent_class_of_t<f>;
        using expect = foo;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = int foo::*;
        using test =  parent_class_of_t<f>;
        using expect = foo;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = const int foo::*;
        using test =  parent_class_of_t<f>;
        using expect = foo;
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}
