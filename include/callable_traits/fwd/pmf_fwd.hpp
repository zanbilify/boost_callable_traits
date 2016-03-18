/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_FWD_PMF_FWD_HPP
#define CALLABLE_TRAITS_FWD_PMF_FWD_HPP

#if defined (CALLABLE_TRAITS_PMF_HPP)
static_assert(false, "<callable_traits/fwd/pmf_fwd.hpp> must be included before <callable_traits/pmf.hpp>.");
#endif

namespace callable_traits {

    namespace ctdetail {

        template<typename T>
        struct pmf;

    }
}

#endif