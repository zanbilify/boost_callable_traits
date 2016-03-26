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

// functions `ordered_letters`, `BEEF_returns_D`, `BEEF_returns_G`,
// and `BEEF_returns_B` are used to set up a complex bind expression
// with ct::bind_expr

auto ordered_letters(A a, B b, C c, D d, E e, F f, G g) {
    std::stringstream ss{};
    ss << a << b << c << d << e << f << g;
    return ss.str();
}

auto BEEF_returns_D(B, E, E, F) {
    return D{};
}

auto BEEF_returns_G(B, E, E, F) {
    return G{};
}

auto BEEF_returns_B(B, E, E, F) {
    return B{};
}

template <typename F, typename Tuple, std::size_t... I>
constexpr decltype(auto)
apply_helper(F&& f, Tuple&& t, std::index_sequence<I...>) {
    return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
}

//used to apply the expected_args tuple to std::bind
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

const auto a = A{};
const auto b = B{};
const auto c = C{};
const auto d = D{};
const auto e = E{};
const auto f = F{};
const auto g = G{};

// lets us create a complex bind expression with both
// `std::bind` and `ct::bind_expr`
#define BIND_WITH(bind_name)                     \
        bind_name(&ordered_letters,              \
            _1,                                  \
            _2,                                  \
            _3,                                  \
                bind_name(&BEEF_returns_D,       \
                _2,                              \
                e,                               \
                _4,                              \
                _7                               \
            ),                                   \
            _5,                                  \
            _6,                                  \
                bind_name(&BEEF_returns_G,       \
                    bind_name(&BEEF_returns_B,   \
                    b,                           \
                    _10,                         \
                    e,                           \
                    f                            \
                ),                               \
                _9,                              \
                e,                               \
                _8                               \
            )                                    \
        )                                        \
/**/

template<typename BindExpr>
void check_expression_flattening();

int main() {

    assert(ordered_letters(a, b, c, d, e, f, g) == "ABCDEFG");

    using bind_expr = decltype(BIND_WITH(ct::bind_expr));

    check_expression_flattening<bind_expr>();

    using args = ct::args<bind_expr>;

    // these are the argument types as dictated by 
    // the bind expression's placeholders
    using expected_args = std::tuple<A, B, C, E, E, F, F, F, E, E>;

    CT_ASSERT(std::is_same<args, expected_args>{});

    auto runtime_test = BIND_WITH(std::bind);
    assert(apply(runtime_test, expected_args{}) == "ABCDEFG");

    return 0;
}

template<typename BindExpr>
void check_expression_flattening() {
    using inner3 = decltype(ct::bind_expr(&BEEF_returns_B, b, _10, e, f));
    using inner2 = decltype(ct::bind_expr(&BEEF_returns_G, inner3{}, _9, e, _8));
    using inner1 = decltype(ct::bind_expr(&BEEF_returns_D, _2, e, _4, _7));

    using bind_expr_check = decltype(ct::bind_expr(
        &ordered_letters, _1, _2, _3,
        inner1{},
        _5, _6,
        inner2{}
    ));

    // this assert makes sure the BIND_WITH macro (defined above)
    // hasn't been modified out of sync with this function definition
    CT_ASSERT(std::is_same<BindExpr, bind_expr_check>{});

    using flattened_exprs = typename BindExpr::flattened_bind_expressions;
    using expected_exprs = std::tuple<BindExpr, inner1, inner2, inner3>;

    CT_ASSERT(std::is_same<flattened_exprs, expected_exprs>{});
}