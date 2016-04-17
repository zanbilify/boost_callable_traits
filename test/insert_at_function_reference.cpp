#include <tuple>
#include <utility>
#include <type_traits>
#include <callable_traits/insert_at.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

namespace ct = callable_traits;

template<int I>
struct N {};

template<typename... Ts>
using sig = int(&)(Ts...);

int main() {

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = ct::insert_at<0, f, int, char>;
        using expect = sig<int, char, N<0>, N<1>, N<2>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = ct::insert_at<1, f, int, char>;
        using expect = sig<N<0>, int, char, N<1>, N<2>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = ct::insert_at<2, f, int, char>;
        using expect = sig<N<0>, N<1>, int, char, N<2>, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = ct::insert_at<3, f, int, char>;
        using expect = sig<N<0>, N<1>, N<2>, int, char, N<3>, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = ct::insert_at<4, f, int, char>;
        using expect = sig<N<0>, N<1>, N<2>, N<3>, int, char, N<4>>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using f = sig<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = ct::insert_at<5, f, int, char>;
        using expect = sig<N<0>, N<1>, N<2>, N<3>, N<4>, int, char>;
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}

