#include <callable_traits/detail/make_constexpr.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

struct foo {

    constexpr int operator()(int&) & {
        return 1;
    }

    constexpr int operator()(const int&) & {
        return 2;
    }

    constexpr int operator()(int&&) & {
        return 3;
    }

    constexpr int operator()(int&) && {
        return 4;
    }
    
    constexpr int operator()(const int&) && {
        return 5;
    }
    
    constexpr int operator()(int&&) && {
        return 6;
    }

    constexpr int operator()(int&) const & {
        return 7;
    }
    
    constexpr int operator()(const int&) const & {
        return 8;
    }
    
    constexpr int operator()(int&&) const & {
        return 9;
    }

    constexpr int operator()(int&) const && {
        return 10;
    }
    
    constexpr int operator()(const int &) const && {
        return 11;
    }
    
    constexpr int operator()(int&&) const && {
        return 12;
    }
};


CT_ASSERT(1 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&)));
CT_ASSERT(2 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(const int&)));
CT_ASSERT(3 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&&)));
CT_ASSERT(3 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int)));

CT_ASSERT(4 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo&&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&)));
CT_ASSERT(4 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&)));
CT_ASSERT(5 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo&&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(const int&)));
CT_ASSERT(5 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo)(CALLABLE_TRAITS_MAKE_CONSTEXPR(const int&)));
CT_ASSERT(6 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo&&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&&)));
CT_ASSERT(6 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&&)));
CT_ASSERT(6 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo&&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int)));
CT_ASSERT(6 == CALLABLE_TRAITS_MAKE_CONSTEXPR(foo)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int)));

CT_ASSERT(7 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&)));
CT_ASSERT(8 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(const int&)));
CT_ASSERT(9 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&&)));
CT_ASSERT(9 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int)));

CT_ASSERT(10 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo&&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&)));
CT_ASSERT(10 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&)));
CT_ASSERT(11 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo&&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(const int&)));
CT_ASSERT(11 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo)(CALLABLE_TRAITS_MAKE_CONSTEXPR(const int&)));
CT_ASSERT(12 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo&&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&&)));
CT_ASSERT(12 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int&&)));
CT_ASSERT(12 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo&&)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int)));
CT_ASSERT(12 == CALLABLE_TRAITS_MAKE_CONSTEXPR(const foo)(CALLABLE_TRAITS_MAKE_CONSTEXPR(int)));

int main() { return 0; }