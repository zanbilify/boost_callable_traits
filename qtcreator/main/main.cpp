/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>
#ifdef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS
int main(){ return 0; }
#else



//[ overview
#include <callable_traits/callable_traits.hpp>

#include <type_traits>
#include <tuple>

using std::is_same;
using std::tuple;

using namespace callable_traits;

struct number {
    int value;
    auto add(int n) const { return value + n; }
};

using pmf = decltype(&number::add);

//` Mmanipulate member functions pointers with ease:
static_assert(is_same<remove_member_const<pmf>,
    int(number::*)(int)>::value, "");

static_assert(is_same<add_member_volatile<pmf>,
    int(number::*)(int) const volatile>::value, "");

static_assert(is_same<parent_class_of<pmf>, number>::value, "");
static_assert(is_same<remove_member_pointer<pmf>, int (int) const>::value, "");

//` INVOKE-aware metafunctions:
static_assert(is_same<args<pmf>, tuple<const number&, int>>::value, "");
static_assert(is_same<arg_at<0, pmf>, const number&>::value, "");
static_assert(is_same<arg_at<1, pmf>, int>::value, "");
static_assert(is_same<result_of<pmf>, int>::value, "");
static_assert(is_same<function_type<pmf>, int(const number&, int)>::value, "");

static_assert(is_same<qualified_parent_class_of<pmf>, const number&>::value, "");


//` `arity` is defined as the number of parameters to a callable type. This is defined in terms of INVOKE, so that member function pointers always have an arity of at least one:
static_assert(arity(&number::add) == 2, "");

//` The `[libname]` interface uses constexpr function templates for type traits, which accept values and return `integral_constant`s. However, if you don't have any values lying around, you can always use types instead:
static_assert(arity<pmf>() == 2, ""); // same as above, but with a type instead of a value

//` Here are a few other trait examples:
static_assert(is_const_member<pmf>(), "");
static_assert(!is_volatile_member<pmf>(), "");
static_assert(!has_void_return<pmf>(), "");
static_assert(can_invoke<pmf, const number&, int>(), "");
static_assert(!can_invoke<pmf, const number&, const char*>(), "");
static_assert(!is_constexpr<pmf>(), "");
static_assert(!has_varargs<pmf>(), "");

//` You can use [libname] to manipulate parameter lists (not defined in terms of
// INVOKE, since that wouldn't make sense here):

using pmf_2 = push_back<pmf, char, short, long>;

static_assert(is_same<pmf_2,
    int(number::*)(int, char, short, long) const>::value, "");

static_assert(is_same<pop_front<pmf_2>,
    int(number::*)(char, short, long) const>::value, "");

static_assert(is_same<insert_args<2, pmf_2, short*, long*>,
    int(number::*)(int, char, short*, long*, short, long) const>::value, "");

static_assert(is_same<replace_args<2, pmf_2, short*, long*>,
    int(number::*)(int, char, short*, long*) const>::value, "");

static_assert(is_same<remove_args<2, pmf_2>,
    int(number::*)(int, char, long) const>::value, "");

static_assert(is_same<clear_args<pmf_2>,
    int(number::*)() const>::value, "");

static_assert(is_same<add_varargs<pmf_2>,
    int(number::*)(int, char, short, long, ...) const>::value, "");
//]

int main() {}

#endif
