/*

Copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#include <cassert>
#undef NDEBUG
#include "make_function.hpp"

using example::make_function;
using namespace std::placeholders;

int add(int i, int j) {
    return i + j;
}

struct adder {

    int eval(int i, int j) const {
        return i + j;
    }
};

void check_add(std::function<int(int, int)>& f) {

    auto add_result = f(99, 1);
    assert(add_result == 100);
}

int main() {

    //function pointer
    auto f = make_function(&add);
    check_add(f);

    //function reference
    f = make_function(add);
    check_add(f);

    //lambda
    f = make_function([](int i, int j) {
        return i + j;
    });
    check_add(f);

    //member function pointer (bound to object)
    f = make_function(&adder::eval, adder{}, _1, _2);
    check_add(f);
}
