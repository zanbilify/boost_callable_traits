#include <tuple>
#include <utility>
#include <type_traits>
#include <callable_traits/insert_args.hpp>
#include "test.hpp"


template<int I>
struct N {};

template<typename... Ts>
using sig = int(Ts...);

int main() {

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  insert_args_t<0, f, int, char>;
        using expect = sig<int, char, N<0>, N<1>, N<2>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  insert_args_t<1, f, int, char>;
        using expect = sig<N<0>, int, char, N<1>, N<2>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  insert_args_t<2, f, int, char>;
        using expect = sig<N<0>, N<1>, int, char, N<2>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  insert_args_t<3, f, int, char>;
        using expect = sig<N<0>, N<1>, N<2>, int, char, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  insert_args_t<4, f, int, char>;
        using expect = sig<N<0>, N<1>, N<2>, N<3>, int, char, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test =  insert_args_t<5, f, int, char>;
        using expect = sig<N<0>, N<1>, N<2>, N<3>, N<4>, int, char>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}

