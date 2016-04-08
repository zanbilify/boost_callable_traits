/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

//[ intro
#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/callable_traits.hpp>

struct foo {
    void operator()(int, int&&, const int&, void* = nullptr) const {}
};

namespace ct = callable_traits;
using namespace std::placeholders;

int main() {

    // indexed argument types
    using second_arg = ct::arg_at<1, foo>;
    static_assert(std::is_same<second_arg, int&&>::value, "");

    // arg types are packaged into std::tuple, which serves as the default
    // type list in CallableTraits (runtime capabilities are not used).
    using args = ct::args<foo>;
    using expected_args = std::tuple<int, int&&, const int&, void*>;
    static_assert(std::is_same<args, expected_args>::value, "");

    //callable_traits::result_of is a bit friendlier than std::result_of
    using return_type = ct::result_of<foo>;
    static_assert(std::is_same<return_type, void>::value, "");

    //has_void_return is a quicker way to perform the check above
    static_assert(ct::has_void_return(foo{}), "");

    // callable_traits::function_type decays a callable type to
    // a plain function type, which is structured in terms of INVOKE
    using function_type = ct::function_type<foo>;
    using expected_function_type = void(int, int&&, const int&, void*);
    static_assert(std::is_same<function_type, expected_function_type>::value, "");

    // when trait information can be conveyed in an std::integral_constant,
    // callable_traits opts for constexpr functions instead of template aliases.
    // This is done to encourage value semantics, and to simplify usage inside
    // of forwarding functions.
    static_assert(ct::arity(foo{}) == 4, "");
    static_assert(ct::max_arity(foo{}) == 4, "");
    static_assert(ct::min_arity(foo{}) == 3, "");

    // CallableTraits provides constexpr functions so that the user doesn't
    // need to worry about reference collapsing or decltype when dealing with
    // universal references to callables. Still, you don't NEED an instance,
    // because CallableTraits provides non-deduced function templates for
    // all constexpr functions (except for can_invoke/can_invoke_constexpr and bind,
    // which model std::invoke and std::bind, respectively -- more on these below).
    // Here's an example of the non-deduced version of arity, which take an
    // explicit type argument. We'll ignore these non-deduced overloads for the
    // rest of this example.
    static_assert(ct::arity<foo>() == 4, "");

    // C-style variadics detection (ellipses in a signature)
    static_assert(!ct::has_varargs(foo{}), "");

    int i = 0;

    // callable_traits::can_invoke allows us to preview whether std::invoke will
    // compile with the given arguments.
    static_assert(ct::can_invoke(foo{}, 0, 0, i), "");
    // no error:     std::invoke(foo{}, 0, 0, i);

    static_assert(!ct::can_invoke(foo{}, nullptr), "");
    // error:         std::invoke(foo{}, nullptr);

    // For function objects, the following checks are determined by the
    // qualifiers on operator(), rather than the category of the passed value.
    // For member function pointers and abominable function types, the
    // qualifiers on the function type are used.
    static_assert(ct::is_const_qualified(foo{}), "");
    static_assert(!ct::is_volatile_qualified(foo{}), "");
    static_assert(!ct::is_reference_qualified(foo{}), "");
    static_assert(!ct::is_lvalue_qualified(foo{}), "");
    static_assert(!ct::is_rvalue_qualified(foo{}), "");


    // If you find yourself in the unfortunate situation of needing
    // to manipulate member function pointer types, CallableTraits
    // has all the tools you need to maintain your sanity.


    using pmf = decltype(&foo::operator());

    // So that you don't have to scroll back up to see, here's the type of pmf:
    using with_const = void (foo::*)(int, int&&, const int&, void*) const;
    static_assert(std::is_same<pmf, with_const>::value, "");

    // Let's remove the const qualifier:
    using mutable_pmf = ct::remove_const_qualifier<pmf>;
    using without_const = void (foo::*)(int, int&&, const int&, void*) /*no const!*/;
    static_assert(std::is_same<mutable_pmf, without_const>::value, "");

    // Now let's add an rvalue qualifier (&&):
    using rvalue_pmf = ct::add_rvalue_qualifier<pmf>;
    using with_rvalue = void (foo::*)(int, int&&, const int&, void*) const &&;
    static_assert(std::is_same<rvalue_pmf, with_rvalue>::value, "");

    // You get the picture. CallableTraits lets you add and remove all PMF
    // qualifiers (const, volatile, &, &&, and any combination thereof).
    // These type operations can generally be performed on abominable function
    // types as well.

    // is_constexpr would return std::true_type if foo's operator() were constexpr.
    static_assert(!ct::is_constexpr(foo{}), "");

    // to check constexprness of a function or member function, you must use an
    // std::integral_constant, like this:
    using pmf_constant = std::integral_constant<pmf, &foo::operator()>;
    static_assert(!ct::is_constexpr(pmf_constant{}), "");
}
//]
