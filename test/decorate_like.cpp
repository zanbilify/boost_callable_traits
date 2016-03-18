/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#include <callable_traits/decorate_like.hpp>
#include <type_traits>
#include <memory>
#include <utility>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

#ifdef _MSC_VER
//abominable function type warning
#pragma warning(disable:4180)
#endif

namespace ct = callable_traits;

using Input = int;
using Output = float;


void test();

template<
    typename DecayedInput,
    typename Output,
    typename Input,
    typename Expect,
    template<class> class Metafunction
>
void test_expand() {
    using input = typename Metafunction<Input>::type;
    using test = typename Metafunction<Expect>::type;

    using decorator = ct::decorator<input>;
    using result1 = ct::decorate_like<input, Output>;
    using result2 = typename decorator::template apply<Output>;

    CT_ASSERT(std::is_same<result1, result2>{});
    CT_ASSERT(std::is_same<test, result1>{});
    CT_ASSERT(std::is_same<ct::deep_decay<Input>, DecayedInput>{});
}

template<typename T>
struct identity {
    using type = T;
};

template<typename T>
struct wrap_ref {
    using type = std::reference_wrapper<T>;
};

template<typename T>
struct wrap_unique {
    using type = std::unique_ptr<T>;
};

template<typename T>
struct wrap_shared {
    using type = std::shared_ptr<T>;
};

template<typename T>
struct wrap_weak {
    using type = std::weak_ptr<T>;
};

struct foo {};

template<typename T>
struct add_member_pointer {
    using type = T foo::*;
};

template<typename DecayedInput, typename Output, typename Input, typename Expect>
void test_prepare() {
    test_expand<DecayedInput, Output, Input, Expect, identity>();
    test_expand<DecayedInput, Output, Input, Expect, std::add_const>();
    test_expand<DecayedInput, Output, Input, Expect, std::add_volatile>();
    test_expand<DecayedInput, Output, Input, Expect, std::add_cv>();
    test_expand<DecayedInput, Output, Input, Expect, std::add_lvalue_reference>();
    test_expand<DecayedInput, Output, Input, Expect, std::add_rvalue_reference>();
    test_expand<DecayedInput, Output, Input, Expect, wrap_ref>();
    test_expand<DecayedInput, Output, Input, Expect, wrap_unique>();
    test_expand<DecayedInput, Output, Input, Expect, wrap_shared>();
    test_expand<DecayedInput, Output, Input, Expect, wrap_weak>();
}

template<typename DecayedInput, typename DecayedOutput, typename Input, typename Output>
void test() {
    test_prepare<DecayedInput, DecayedOutput, Input, Output>();
    test_prepare<DecayedInput, DecayedOutput, Input&, Output&>();
    test_prepare<DecayedInput, DecayedOutput, Input&&, Output&&>();

    test_prepare<DecayedInput, DecayedOutput, std::unique_ptr<Input>, std::unique_ptr<Output>>();
    test_prepare<DecayedInput, DecayedOutput, std::shared_ptr<Input>, std::shared_ptr<Output>>();
    test_prepare<DecayedInput, DecayedOutput, std::weak_ptr<Input>, std::weak_ptr<Output>>();

    test_prepare<DecayedInput, DecayedOutput, std::unique_ptr<Input>&, std::unique_ptr<Output>&>();
    test_prepare<DecayedInput, DecayedOutput, std::shared_ptr<Input>&, std::shared_ptr<Output>&>();
    test_prepare<DecayedInput, DecayedOutput, std::weak_ptr<Input>&&, std::weak_ptr<Output>&&>();

    test_prepare<DecayedInput, DecayedOutput, std::unique_ptr<Input>*, std::unique_ptr<Output>*>();
    test_prepare<DecayedInput, DecayedOutput, std::shared_ptr<Input>*, std::shared_ptr<Output>*>();
    test_prepare<DecayedInput, DecayedOutput, std::weak_ptr<Input>*, std::weak_ptr<Output>*>();

    test_prepare<DecayedInput, DecayedOutput, const Input, const Output>();
    test_prepare<DecayedInput, DecayedOutput, const Input&, const Output&>();
    test_prepare<DecayedInput, DecayedOutput, const Input&&, const Output&&>();

    test_prepare<DecayedInput, DecayedOutput, volatile Input, volatile Output>();
    test_prepare<DecayedInput, DecayedOutput, volatile Input&, volatile Output&>();
    test_prepare<DecayedInput, DecayedOutput, const volatile Input&&, const volatile Output&&>();

    test_prepare<DecayedInput, DecayedOutput, const std::unique_ptr<Input>, const std::unique_ptr<Output>>();
    test_prepare<DecayedInput, DecayedOutput, std::shared_ptr<const Input>, std::shared_ptr<const Output>>();
    test_prepare<DecayedInput, DecayedOutput, std::weak_ptr<volatile Input>, std::weak_ptr<volatile Output>>();
    test_prepare<DecayedInput, DecayedOutput, std::unique_ptr<const volatile Input>&, std::unique_ptr<const volatile  Output>&>();
}

int main() {
     
    test<int, float, int, float>();
    test<int, float, int*, float*>();
    test<void(int, int), void(int), void(int, int), void(int)>();
    test<void(int, int), int, void(foo::* const)(int, int), int foo::* const>();
    test<void(int, int), int, void(foo::*** const)(int, int), int foo::*** const>();
    test<void(int, int), int, void(foo::*** const)(int, int), int foo::*** const>();
    test<int, float, const int foo::* volatile, const float foo::* volatile>();

    return 0;
}