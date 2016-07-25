#include <tuple>
#include <utility>
#include <type_traits>
#include <callable_traits/callable_traits.hpp>
#include "test.hpp"




template<int I>
struct N {};

struct foo;

template<typename... Ts>
using sig = int(foo::*)(Ts...) const volatile RREF;

int main() {

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  push_front_args_t<f, int, char>;
        using expect = sig<int, char, N<0>, N<1>, N<2>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}

