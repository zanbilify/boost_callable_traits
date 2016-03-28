/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FWD_PMD_FWD_HPP
#define CALLABLE_TRAITS_FWD_PMD_FWD_HPP

#if defined (CALLABLE_TRAITS_PMD_HPP)
static_assert(false, "<callable_traits/fwd/pmd_fwd.hpp> must be included before <callable_traits/pmd.hpp>.");
#endif

namespace callable_traits {

    namespace detail {

        template<typename T>
        struct pmd;

    }
}

#endif