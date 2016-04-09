/*<-
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
->*/
//[ hideous_template
template<typename Return, typename T, typename... Args>
struct foo<Return(T::*)(Args...) const volatile &&> {
    //...
};
//]
