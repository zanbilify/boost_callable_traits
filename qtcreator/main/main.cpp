/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/callable_traits.hpp>

using namespace callable_traits;

int main() {

    using g = add_transaction_safe_t<void()>;
    static_assert(std::is_same<g, void()>::value, "");
}
