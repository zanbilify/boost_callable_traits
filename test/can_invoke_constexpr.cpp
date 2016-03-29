#include <type_traits>
#include <callable_traits/callable_traits.hpp>

struct foo1 {
    int operator()() const {
        return 0;
    }
};

struct foo2 {
    constexpr int operator()(int) const {
        return 1;
    }
    constexpr int operator()() const {
        return 1;
    }
};

struct foo3 {
    constexpr int bar(int) const {
        return 1;
    }
};

constexpr int bar(const int&) {
    return 1;
}

using foo4 = std::integral_constant<decltype(&bar), &bar>;

using foo1_pmf = std::integral_constant<decltype(&foo1::operator()), &foo1::operator()>;
using foo3_pmf = std::integral_constant<decltype(&foo3::bar), &foo3::bar>;

namespace ct = callable_traits;

#ifdef  CALLABLE_TRAITS_CAN_INVOKE_CONSTEXPR_DISABLED
#define IF_ENABLED !
#else
#define IF_ENABLED
#endif

static_assert(!ct::can_invoke_constexpr(foo1{}), "");
static_assert(!ct::can_invoke_constexpr(foo1{}, 0), "");

static_assert(IF_ENABLED ct::can_invoke_constexpr(foo2{}), "");
static_assert(IF_ENABLED ct::can_invoke_constexpr(foo2{}, 0), "");

static_assert(!ct::can_invoke_constexpr(foo4{}), "");
static_assert(IF_ENABLED ct::can_invoke_constexpr(foo4{}, 0), "");

static_assert(!ct::can_invoke_constexpr(foo1_pmf{}, foo1{}), "");
static_assert(!ct::can_invoke_constexpr(foo1_pmf{}, foo1{}, 0), "");

static_assert(!ct::can_invoke_constexpr(foo3_pmf{}, foo3{}), "");
static_assert(IF_ENABLED ct::can_invoke_constexpr(foo3_pmf{}, foo3{}, 0), "");

int main() { return 0; }
