/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <tuple>
#include <callable_traits/callable_traits.hpp>

// Most of this example uses a function object. Unless otherwise noted, all
// features shown in this example can be used for any "callable" types:
// lambdas, generic lambdas, function pointers, function references,
// function types, abominable function types, member function pointers, and
// member data pointers. Ambiguous callables (e.g. function objects with
// templated/overloaded operator()) are not addressed in this example, but
// are recognized and handled by CallableTraits.

// Note: For more information about abominable function types, see Alisdair Meredith's
// proposal at http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0172r0.html

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

    // callable_traits::function_type yields a plain function type
    using function_type = ct::function_type<foo>;
    using expected_function_type = void(int, int&&, const int&, void*);
    static_assert(std::is_same<function_type, expected_function_type>::value, "");

    // when trait information can be conveyed in an integral_constant,
    // callable_traits uses constexpr functions instead of template aliases.
    // Note: min_arity and max_arity only differ logically from arity when
    // the argument is a function object.
    static_assert(ct::arity(foo{}) == 4, "");
    static_assert(ct::max_arity(foo{}) == 4, "");
    static_assert(ct::min_arity(foo{}) == 3, "");

    // CallableTraits provides constexpr functions so that the user doesn't
    // need to worry about reference collapsing or decltype when dealing with
    // universal references to callables. Still, you don't need an instance,
    // because CallableTraits provides non-deduced function templates for
    // all constexpr functions besides can_invoke and bind, which
    // model std::invoke and std::bind, respectively (more on these below).
    // Here's an example of the non-deduced functions, which take an explicit
    // type argument. We'll ignore these for the rest of the example.
    static_assert(ct::arity<foo>() == 4, "");
    static_assert(ct::max_arity<foo>() == 4, "");
    static_assert(ct::min_arity<foo>() == 3, "");

    // C-style varargs (ellipses in a signature) can be detected.
    static_assert(!ct::has_varargs(foo{}), "");

    // callable_traits::can_invoke allows us to preview whether
    // std::invoke will compile with the given arguments. Keep
    // in mind that failing cases must be SFINAE-friendly (i.e.
    // any failing static_asserts can still be tripped). Note: The
    // same sfinae restrictions apply to min_arity and max_arity
    // for function objects.
    int i = 0;
    static_assert(ct::can_invoke(foo{}, 0, 0, i), "");
    // no error:     std::invoke(foo{}, 0, 0, i);

    static_assert(!ct::can_invoke(foo{}, nullptr), "");
    // error:         std::invoke(foo{}, nullptr);

    // callable_traits::bind is a compile-time bind expression parser,
    // very loosely based on the Boost.Bind implementation. Nested bind
    // expressions are fully supported. The return type of bind only
    // contains type information, but can still be used in an evaluated
    // context. The return type can be treated like a callable type when passed
    // to result_of, function_type, args, or arg_at template aliases.
    auto b = ct::bind(foo{}, _1, _1, _1);

    // Here, int&& is chosen as the expected argument for the bind expression
    // because it's the best fit for all three placeholder slots. Behind
    // the scenes, this is determined by a cartesian product of parameter
    // conversion combinations that are represented by the reused placeholders.
    static_assert(std::is_same<
        ct::args<decltype(b)>,
        std::tuple<int&&>
    >::value, "");

    // For function objects, the following checks are determined by the 
    // qualifiers on operator(), rather than the category of the passed value.
    // For member function pointers and abominable function types, the
    // qualifier on the function type are used.
    static_assert(ct::is_const_qualified(foo{}), "");
    static_assert(!ct::is_volatile_qualified(foo{}), "");
    static_assert(!ct::is_reference_qualified(foo{}), "");
    static_assert(!ct::is_lvalue_qualified(foo{}), "");
    static_assert(!ct::is_lvalue_qualified(foo{}), "");



    // If you find yourself in the unfortunate situation of needing
    // to manipulate member function pointer types, CallableTraits
    // has all the tools you need to maintain your sanity.



    using pmf = decltype(&foo::operator());

    {
        // So that you don't have to scroll back up to see, here's the type of pmf:
        using expected_pmf = void (foo::*)(int, int&&, const int&, void*) const;
        static_assert(std::is_same<pmf, expected_pmf>::value, "");
    }

    {
        // Let's remove the const qualifier:
        using mutable_pmf = ct::remove_const_qualifier<pmf>;
        using expected_pmf = void (foo::*)(int, int&&, const int&, void*) /*no const!*/;
        static_assert(std::is_same<mutable_pmf, expected_pmf>::value, "");
    }

    {
        // Now let's add an rvalue qualifier (&&):
        using rvalue_pmf = ct::add_rvalue_qualifier<pmf>;
        using expected_pmf = void (foo::*)(int, int&&, const int&, void*) const &&;
        static_assert(std::is_same<rvalue_pmf, expected_pmf>::value, ""); //        ^^^^
    }

    // You get the picture. CallableTraits lets you add and remove all PMF
    // qualifiers (const, volatile, &, &&, and any combination thereof).
    // These type operations can be performed on abominable function types as well.


    // Somehow, somewhere, there was a sad programmer who wanted to
    // manipulate c-style varargs in a function signature. There's
    // really no way to do this universally without doing all the work
    // that CallableTraits already does, so CallableTraits includes in
    // an add/remove feature for this, too.
    {

        using varargs_pmf = ct::add_varargs<pmf>;
        using expected_pmf = void (foo::*)(int, int&&, const int&, void*, ...) const;
        static_assert(std::is_same<varargs_pmf, expected_pmf>::value, ""); //  ^^^

        // note: MSVC likely requires __cdecl for a varargs PMF on your
        // machine, at least if you intend to do anything useful with it.
    }
}
