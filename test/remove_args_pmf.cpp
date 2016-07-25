#include <tuple>
#include <utility>
#include <type_traits>
#include <callable_traits/callable_traits.hpp>
#include "test.hpp"


template<int I>
struct N {};

struct foo {};

template<typename... Ts>
using sig = void(foo::*)(Ts...);

int main() {

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  remove_args_t<0, f>;
        using expect = sig<N<1>, N<2>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  remove_args_t<1, f>;
        using expect = sig<N<0>, N<2>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  remove_args_t<2, f>;
        using expect = sig<N<0>, N<1>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  remove_args_t<3, f>;
        using expect = sig<N<0>, N<1>, N<2>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  remove_args_t<4, f>;
        using expect = sig<N<0>, N<1>, N<2>, N<3>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  remove_args_t<0, f, 5>;
        using expect = sig<>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  remove_args_t<0, f, 3>;
        using expect = sig<N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  remove_args_t<3, f, 2>;
        using expect = sig<N<0>, N<1>, N<2>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  remove_args_t<4, f, 1>;
        using expect = sig<N<0>, N<1>, N<2>, N<3>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}

