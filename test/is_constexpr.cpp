/*!
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <callable_traits/callable_traits.hpp>

#ifdef CALLABLE_TRAITS_MSVC
//feature is unsupported in MSVC
int main(){ return 0; };
#else

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

namespace ct = callable_traits;

namespace test1 {

    struct A1 {
        int operator()() const { return 0; }
    };

    struct A2 {
        int operator()(int) const { return 0; }
    };

    struct A3 {
        constexpr int operator()(int) const { return 0; }
        int operator()() const { return 0; }
    };

    CT_ASSERT(!ct::is_constexpr(A1{}));
    CT_ASSERT(!ct::is_constexpr<A1>());
    CT_ASSERT(!ct::is_constexpr(A2{}));
    CT_ASSERT(!ct::is_constexpr<A2>());
    CT_ASSERT(!ct::is_constexpr(A3{}));
    CT_ASSERT(!ct::is_constexpr<A3>());

    using A1_pmf = std::integral_constant<decltype(&A1::operator()), &A1::operator()>;
    using A2_pmf = std::integral_constant<decltype(&A2::operator()), &A2::operator()>;

    CT_ASSERT(!ct::is_constexpr(A1_pmf{}));
    CT_ASSERT(!ct::is_constexpr<A1_pmf>());
    CT_ASSERT(!ct::is_constexpr(A2_pmf{}));
    CT_ASSERT(!ct::is_constexpr<A2_pmf>());
}

namespace test2 {

    struct B1 {
        constexpr int operator()(int) const { return 1; }
        constexpr int operator()() const { return 1; }
    };

    struct B2 {
        constexpr int operator()() const { return 1; }
    };

    struct B3 {
        constexpr int operator()(int&) const { return 1; }
    };

    struct B4 {
        constexpr int operator()(int&&) const { return 1; }
    };

    struct B5 {
        constexpr int operator()(const int&) const { return 1; }
    };

    struct B6 {
        constexpr int operator()(int) const { return 1; }
    };

    struct B7 {
        constexpr int operator()(int, int, int, int, int, int, int, int, int, int) const & { return 1; }
    };

    CT_ASSERT(ct::is_constexpr(B1{}));
    CT_ASSERT(ct::is_constexpr<B1>());
    CT_ASSERT(ct::is_constexpr(B2{}));
    CT_ASSERT(ct::is_constexpr<B2>());
    CT_ASSERT(ct::is_constexpr(B3{}));
    CT_ASSERT(ct::is_constexpr<B3>());
    CT_ASSERT(ct::is_constexpr(B4{}));
    CT_ASSERT(ct::is_constexpr<B4>());
    CT_ASSERT(ct::is_constexpr(B5{}));
    CT_ASSERT(ct::is_constexpr<B5>());
    CT_ASSERT(ct::is_constexpr(B6{}));
    CT_ASSERT(ct::is_constexpr<B6>());
    CT_ASSERT(ct::is_constexpr(B7{}));
    CT_ASSERT(ct::is_constexpr<B7>());
}

namespace test3 {

    struct foo {
        constexpr int bar(int) const { return 1; }
    };

    using C = std::integral_constant<decltype(&foo::bar), &foo::bar>;
    CT_ASSERT(ct::is_constexpr(C{}));
    CT_ASSERT(ct::is_constexpr<C>());
}

namespace test4 {

    constexpr int foo(const int&) { return 1; }
    using D = std::integral_constant<decltype(&foo), &foo>;
    CT_ASSERT(ct::is_constexpr(D{}));
    CT_ASSERT(ct::is_constexpr<D>());
}

namespace test5 {

    struct foo { static constexpr int value = 1; };
    using E = std::integral_constant<decltype(&foo::value), &foo::value>;

    //false because &foo::value is not a pointer to member data... it's static
    CT_ASSERT(!ct::is_constexpr(E{}));
    CT_ASSERT(!ct::is_constexpr<E>());
}

namespace test6 {

    struct foo { int value; };
    using F = std::integral_constant<decltype(&foo::value), &foo::value>;
    CT_ASSERT(!ct::is_constexpr(F{}));
    CT_ASSERT(!ct::is_constexpr<F>());
}

namespace test7 {

    // testing mixed constexpr overloads

    struct G1 { 
        int operator()() const { return 1; }
        constexpr int operator()(int) const { return 1; }
    };

    struct G2 {
        constexpr int operator()() const { return 1; }
        int operator()(int) const { return 1; }
    };

    struct G3 {
        constexpr int operator()(char) const { return 1; }
        constexpr int operator()(int) const { return 1; }
    };

    // we determine constexpr-ness by looking at overloads
    // with the fewest args first, so the overload with no
    // args is the determining member function

    CT_ASSERT(!ct::is_constexpr(G1{}));
    CT_ASSERT(!ct::is_constexpr<G1>());

    CT_ASSERT(ct::is_constexpr(G2{}));
    CT_ASSERT(ct::is_constexpr<G2>());

    // we can't resolve the overload in G3, due to the way
    // callable_traits::detail::any_arg_evaluated works
    CT_ASSERT(!ct::is_constexpr(G3{}));
    CT_ASSERT(!ct::is_constexpr<G3>());
}

int main() {}

#endif
