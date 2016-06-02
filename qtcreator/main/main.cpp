#include <tuple>
#include <utility>
#include <type_traits>
#include <callable_traits/callable_traits.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

namespace ct = callable_traits;

template<int I>
struct N {};

struct foo;

template<typename... Ts>
using sig = int(&)(Ts...);

int main() {

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = ct::args_push_front_t<f, int, char>;
        using expect = sig<int, char, N<0>, N<1>, N<2>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}

