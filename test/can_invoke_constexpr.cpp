#include <type_traits>
#include <callable_traits/callable_traits.hpp>

struct foo1 {
    int operator()() const {
        return 0;
    }
};

struct foo2 {
    constexpr int operator()(int) const {
        return 0;
    }
    constexpr int operator()() const {
        return 0;
    }
};

struct foo3 {
    static constexpr auto value = foo2{}();
};

namespace ct = callable_traits;

static_assert(!ct::can_invoke_constexpr(foo1{}), "");
static_assert(!ct::can_invoke_constexpr(foo1{}, 0), "");
static_assert(ct::can_invoke_constexpr(foo2{}), "");
static_assert(ct::can_invoke_constexpr(foo2{}, 0), "");

int main() {
    return 0;
}
