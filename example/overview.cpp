/*<-
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>
#ifdef CALLABLE_TRAITS_DISABLE_ABOMINABLE_FUNCTIONS
int main(){}
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

//` Manipulate member functions pointers with ease:
static_assert(is_same<
    remove_member_const<pmf>,
    int(number::*)(int)
>{}, "");

static_assert(is_same<
    add_member_volatile<pmf>,
    int(number::*)(int) const volatile
>{}, "");

static_assert(is_same<
    parent_class_of<pmf>,
    number
>{}, "");

static_assert(is_same<
    remove_member_pointer<pmf>,
    int (int) const
>{}, "");

//` INVOKE-aware metafunctions:

static_assert(is_same<
    args<pmf>,
    tuple<const number&, int>
>{}, "");

static_assert(is_same<
    arg_at<0, pmf>,
    const number&
>{}, "");

static_assert(is_same<
    arg_at<1, pmf>,
    int
>{}, "");

static_assert(is_same<
    result_of<pmf>,
    int
>{}, "");

static_assert(is_same<
    function_type<pmf>,
    int(const number&, int)
>{}, "");

static_assert(is_same<
    qualified_parent_class_of<pmf>,
    const number&
>{}, "");

//` Here are a few other trait examples:
static_assert(is_const_member<pmf>(), "");
static_assert(!is_volatile_member<pmf>(), "");
static_assert(!has_void_return<pmf>(), "");
static_assert(!has_varargs<pmf>(), "");

//` You can use [libname] to manipulate parameter lists (not defined in terms of INVOKE, since that wouldn't make sense here):

using pmf_2 = push_back<pmf, char, short, long>;

static_assert(is_same<
    pmf_2,
    int(number::*)(int, char, short, long) const
>{}, "");

static_assert(is_same<
    pop_front<pmf_2>,
    int(number::*)(char, short, long) const
>{}, "");

static_assert(is_same<
    insert_args<2, pmf_2, short*, long*>,
    int(number::*)(int, char, short*, long*, short, long) const
>{}, "");

static_assert(is_same<
    replace_args<2, pmf_2, short*, long*>,
    int(number::*)(int, char, short*, long*) const
>{}, "");

static_assert(is_same<
    remove_args<2, pmf_2>,
    int(number::*)(int, char, long) const
>{}, "");

static_assert(is_same<
    clear_args<pmf_2>,
    int(number::*)() const
>{}, "");

static_assert(is_same<
    add_varargs<pmf_2>,
    int(number::*)(int, char, short, long, ...) const
>{}, "");

//]

int main() {}

#endif
