/*

Copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

//useless MSVC /Wall warnings
#pragma warning(disable: 4514 4711)

#include <type_traits>
#include <cstdint>
#include <memory>
#include <callable_traits/callable_traits.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct foo1 {
    int bar(char, float&, int = 0) { return{}; }
};

struct foo2 {
    int bar(char, float&, int = 0, ...) { return{}; }
};

struct foo3 {
    int operator()(char, float&, int = 0) { return{}; }
};

struct foo4 {
    int operator()(char, float&, int = 0, ...) { return{}; }
};

int foo5(char, float&, int = 0) { return{}; }

int foo6(char, float&, int = 0, ...) { return{}; }

namespace ct = callable_traits;
using std::is_same;

int main() {

    {
        using pmf = decltype(&foo1::bar);
        CT_ASSERT(std::is_same<ct::result_of<pmf>, int>{});
    } {
        using pmf = decltype(&foo2::bar);
        CT_ASSERT(std::is_same<ct::result_of<pmf>, int>{});
    } {
        CT_ASSERT(std::is_same<ct::result_of<foo3>, int>{});
    } {
        CT_ASSERT(std::is_same<ct::result_of<foo4>, int>{});
    } {
        CT_ASSERT(std::is_same<ct::result_of<decltype(foo5)>, int>{});
    } {
        CT_ASSERT(std::is_same<ct::result_of<decltype(foo6)>, int>{});
    }

    return 0;
}