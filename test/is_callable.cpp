#include <tuple>
#include <utility>
#include <type_traits>
#include <callable_traits/min_arity.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

namespace callable_traits {

    template<typename T>
    static constexpr inline auto
    is_callable() {
        return std::integral_constant<bool, min_arity<T>().value >= 0>{};
    }

    template<typename T>
    static constexpr inline auto
    is_callable(T&&) {
        return is_callable<T&&>();
    }
}

namespace ct = callable_traits;

void foo() {}

struct bar {
    template<typename T>
    auto operator()(T&& t) {
        return t;
    }
};

static_assert(ct::is_callable(foo), "");
static_assert(ct::is_callable(&foo), "");
static_assert(ct::is_callable<void(int)>(), "");
static_assert(ct::is_callable<void(...)>(), "");
static_assert(ct::is_callable<void(bar::*)()>(), "");

#ifndef CALLABLE_TRAITS_DISABLE_ARITY_RANGES
static_assert(ct::is_callable(bar{}), "");
#endif //#ifndef CALLABLE_TRAITS_DISABLE_ARITY_RANGES

int main() {}