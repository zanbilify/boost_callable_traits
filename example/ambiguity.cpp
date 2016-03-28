/*

Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#include <type_traits>
#include <callable_traits/callable_traits.hpp>

struct foo {
    void operator()(int);
    void operator()(char);
};

namespace ct = callable_traits;

int main() {

    {
        using test = ct::no_sfinae::args<foo>;
        using expect = std::tuple<ct::unknown>;
        static_assert(std::is_same<test, expect>{}, "");
    } {
        using test = ct::no_sfinae::signature<foo>;
        using expect = ct::unknown(ct::unknown);
        static_assert(std::is_same<test, expect>{}, "");
    } {
        using test = ct::no_sfinae::result_of<foo>;
        using expect = ct::unknown;
        static_assert(std::is_same<test, expect>{}, "");
    }

    return 0;
}
