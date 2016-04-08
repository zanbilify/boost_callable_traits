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
        using test = ct::permissive::args<foo>;
        using expect = ct::invalid_type;
        static_assert(std::is_same<test, expect>{}, "");
    } {
        using test = ct::permissive::function_type<foo>;
        using expect = ct::invalid_type;
        static_assert(std::is_same<test, expect>{}, "");
    } {
        using test = ct::permissive::result_of<foo>;
        using expect = ct::invalid_type;
        static_assert(std::is_same<test, expect>{}, "");
    }

    return 0;
}
