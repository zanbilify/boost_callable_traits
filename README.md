<!--
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
-->

# CallableTraits <a target="_blank" href="https://travis-ci.org/badair/callable_traits">![Travis status][badge.Travis]</a> <a target="_blank" href="https://ci.appveyor.com/project/badair/callable-traits">![Appveyor status][badge.Appveyor]</a> <a target="_blank" href="http://melpon.org/wandbox/permlink/nGNLJRYBsc58zqnp">![Try it online][badge.wandbox]</a> <a target="_blank" href="https://gitter.im/badair/callable_traits">![Gitter Chat][badge.Gitter]</a>

CallableTraits is a C++11/C++14/C++17 header-only library for the inspection, synthesis, and decomposition of callable types. CallableTraits fills the gaps where existing library solutions fall short, aiming to be the "complete type manipulation facility for function types" mentioned in the last section of the C++17 proposal [p0172](http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2015/p0172r0.html). CallableTraits currently supports GCC 4.8 and later, Clang 3.5 and later, AppleClang from XCode 6.3 and later, and Visual Studio 2015. More notes on compatibility [here](http://badair.github.io/callable_traits/doc/html/callable_traits/compatibility.html).

Disclaimer - CallableTraits is currently version 0.4, and is not yet ready for production use. Undiscovered bugs may exist. Documentation is incomplete and may not accurately reflect the state of the code in all places. "Breaking changes" will be made before the 1.0 version is released. Development will take place on the Develop branch, and non-documentation commits merged to the Master branch will be accompanied by a version increment.

## [Documentation](http://badair.github.io/callable_traits/index.html)

Quick reference:

* Member Qualifier Features
  * [add_member_const](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_add_member_const)
  * [remove_member_const](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_remove_member_const)
  * [add_member_volatile](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_add_member_volatile)
  * [remove_member_volatile](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_remove_member_volatile)
  * [add_member_cv](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_add_member_cv)
  * [remove_member_cv](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_remove_member_cv)
  * [add_member_lvalue_reference](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_add_member_lvalue_reference)
  * [add_member_rvalue_reference](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_add_member_rvalue_reference)
  * [remove_member_reference](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_remove_member_reference)
  * [has_member_qualifiers](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_has_member_qualifiers)
  * [is_const_member](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_is_const_member)
  * [is_volatile_member](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_is_volatile_member)
  * [is_cv_member](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_is_cv_member)
  * [is_lvalue_reference_member](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_is_lvalue_reference_member)
  * [is_rvalue_reference_member](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_is_rvalue_reference_member)
  * [is_reference_member](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_qualifier_features.ref_is_reference_member)
* Parameter List Features
  * [function_type](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_function_type)
  * [args](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_args)
  * [arg_at](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_arg_at)
  * [clear_args](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_clear_args)
  * [remove_args](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_remove_args)
  * [replace_args](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_replace_args)
  * [insert_args](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_insert_args)
  * [pop_back_args](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_pop_back_args)
  * [pop_front_args](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_pop_front_args)
  * [push_back_args](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_push_back_args)
  * [push_front_args](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_push_front_args)
  * [expand_args](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_expand_args)
  * [expand_args_left](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_expand_args_left)
  * [expand_args_right](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_expand_args_right)
  * [add_varargs](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_add_varargs)
  * [remove_varargs](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_remove_varargs)
  * [has_varargs](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.parameter_list_features.ref_has_varargs)
*Return Type Features
  * [return_type](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.return_type_features.ref_return_type)
  * [apply_return](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.return_type_features.ref_apply_return)
  * [has_void_return](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.return_type_features.ref_has_void_return)
* Member Pointer Features
  * [apply_member_pointer](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_pointer_features.ref_apply_member_pointer)
  * [parent_class_of](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_pointer_features.ref_apply_member_pointer)
  * [qualified_parent_class_of](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.member_pointer_features.ref_qualified_parent_class_of)
* Transactional Memory Features
  * [add_transaction_safe](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.transactional_memory_features.ref_add_transaction_safe)
  * [remove_transaction_safe](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.transactional_memory_features.ref_remove_transaction_safe)
  * [is_transaction_safe](http://badair.github.io/callable_traits/doc/html/callable_traits/reference.html#callable_traits.reference.transactional_memory_features.ref_is_transaction_safe)

## [License](LICENSE.md)

<!-- Links -->
[badge.Appveyor]: https://ci.appveyor.com/api/projects/status/uf0l91v7l4wc4kw6/branch/master?svg=true
[badge.Gitter]: https://img.shields.io/badge/gitter-join%20chat-blue.svg
[badge.Travis]: https://travis-ci.org/badair/callable_traits.svg?branch=master
[badge.Wandbox]: https://img.shields.io/badge/try%20it-online-blue.svg

