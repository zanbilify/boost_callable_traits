/*

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#include <cassert>
#include <type_traits>
#include <functional>
#include <iostream>
#include <sstream>
#include <memory>
#include <iostream>
#include <cstdint>
#include <callable_traits/callable_traits.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

using namespace std::placeholders;
namespace ct = callable_traits;

struct Letter {
    virtual operator const char*() const volatile = 0;
};

#define DEFINE_TEST_LETTER(L) \
struct L : Letter { operator const char*() const volatile override { return #L; } }

DEFINE_TEST_LETTER(A);
DEFINE_TEST_LETTER(B);
DEFINE_TEST_LETTER(C);
DEFINE_TEST_LETTER(D);
DEFINE_TEST_LETTER(E);
DEFINE_TEST_LETTER(F);
DEFINE_TEST_LETTER(G);

auto letters(
    const Letter& l1,
    const Letter& l2,
    const Letter& l3,
    const Letter& l4,
    const Letter& l5,
    const Letter& l6,
    const Letter& l7
    ) {
    auto ss = std::stringstream{};
    ss << l1 << l2 << l3 << l4 << l5 << l6 << l7;
    return ss.str();
}

auto ordered_letters(A a, B b, C c, D d, E e, F f, G g) {
    auto ss = std::stringstream{};
    ss << a << b << c << d << e << f << g;
    return ss.str();
}

template <typename F, typename Tuple, std::size_t... I>
constexpr decltype(auto)
apply_helper(F&& f, Tuple&& t, std::index_sequence<I...>) {
    return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
}

template <typename F, typename Tuple>
constexpr decltype(auto)
apply(F&& f, Tuple&& t) {
    return apply_helper(
        std::forward<F>(f),
        std::forward<Tuple>(t),
        std::make_index_sequence<
            std::tuple_size<std::remove_reference_t<Tuple>>::value
        >{}
    );
}

int main() {

    auto a = A{};
    auto b = B{};
    auto c = C{};
    auto d = D{};
    auto e = E{};
    auto f = F{};
    auto g = G{};

    assert(letters(a, b, c, d, e, f, g) == "ABCDEFG");
    assert(ordered_letters(a, b, c, d, e, f, g) == "ABCDEFG");

    {
        using args = decltype(ct::bind_args(
            &ordered_letters, _1, _2, _3, _4, _5, _6, _7));
        using expected_args = std::tuple<A, B, C, D, E, F, G>;
        CT_ASSERT(std::is_same<args, expected_args>{});

        auto test = std::bind(&ordered_letters, _1, _2, _3, _4, _5, _6, _7);
        assert(apply(test, expected_args{}) == "ABCDEFG");
    } {   
        using args = decltype(ct::bind_args(
            &ordered_letters, a, b, c, _1, _2, _3, _4));
        using expected_args = std::tuple<D, E, F, G>;
        CT_ASSERT(std::is_same<args, expected_args>{});

        auto test = std::bind(&ordered_letters, a, b, c, _1, _2, _3, _4);
        assert(apply(test, expected_args{}) == "ABCDEFG");
    } {
        using args = decltype(ct::bind_args(
            &ordered_letters, _7, _6, _5, _4, _3, _2, _1));
        using expected_args = std::tuple<G, F, E, D, C, B, A>;
        CT_ASSERT(std::is_same<args, expected_args>{});

        auto test = std::bind(&ordered_letters, _7, _6, _5, _4, _3, _2, _1);
        assert(apply(test, expected_args{}) == "ABCDEFG");
    } {
        using args = decltype(ct::bind_args(
            &ordered_letters, a, b, c, _4, _3, _2, _1));
        using expected_args = std::tuple<G, F, E, D>;
        CT_ASSERT(std::is_same<args, expected_args>{});

        auto test = std::bind(&ordered_letters, a, b, c, _4, _3, _2, _1);
        assert(apply(test, expected_args{}) == "ABCDEFG");
    } {
        using args = decltype(ct::bind_args(
            &ordered_letters, _4, _3, _2, _1, e, f, g));
        using expected_args = std::tuple<D, C, B, A>;
        CT_ASSERT(std::is_same<args, expected_args>{});

        auto test = std::bind(&ordered_letters, _4, _3, _2, _1, e, f, g);
        assert(apply(test, expected_args{}) == "ABCDEFG");
    } {
        //These aren't valid binds. Here we are testing the
        //correctness of the arg_types alias in binding_wrapper.
        using args = decltype(ct::bind_args(
            &ordered_letters, _1, _1, _3, _3, _2, _1, _2));
        using expected_args = std::tuple<A, E, C>;
        CT_ASSERT(std::is_same<args, expected_args>{});
    } {
        using args = decltype(ct::bind_args(
            &ordered_letters, _4, _1, _2, _3, _1, _2, _4));
        using expected_args = std::tuple<B, C, D, A>;
        CT_ASSERT(std::is_same<args, expected_args>{});
    } {
        using args = decltype(ct::bind_args(
            &letters, _1, _1, _3, _3, _2, a, b));
        using expected_args = std::tuple<const Letter&, const Letter&, const Letter&>;
        CT_ASSERT(std::is_same<args, expected_args>{});
    }

    return 0;
}