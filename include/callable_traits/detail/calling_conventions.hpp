/*
Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_CALLING_CONVENTIONS_HPP
#define CALLABLE_TRAITS_DETAIL_CALLING_CONVENTIONS_HPP

#include <callable_traits/detail/utility.hpp>
#include <tuple>

namespace callable_traits {

	namespace calling_conventions {
		struct cdecl{};
		struct stdcall{};
		struct fastcall{};
		struct pascal{};
	}

	namespace detail {

        template<typename T, typename Tag>
		struct add_calling_convention_t {
			using type = invalid_type;
		};

        template<typename T, typename Tag>
		struct has_calling_convention_t {
			using type = std::false_type;
		};

		// member function pointers

		#ifdef CALLABLE_TRAITS_ENABLE_CDECL
		#define CALLABLE_TRAITS_CC_TAG calling_conventions::cdecl
		#define CALLABLE_TRAITS_CC __cdecl
        #include <callable_traits/detail/pmf_cc.hpp>
		#undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
		#endif

		#ifdef CALLABLE_TRAITS_ENABLE_STDCALL
		#define CALLABLE_TRAITS_CC_TAG calling_conventions::stdcall
		#define CALLABLE_TRAITS_CC __stdcall
        #include <callable_traits/detail/pmf_cc.hpp>
		#undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
		#endif

		#ifdef CALLABLE_TRAITS_ENABLE_FASTCALL
		#define CALLABLE_TRAITS_CC_TAG calling_conventions::fastcall
		#define CALLABLE_TRAITS_CC __fastcall
        #include <callable_traits/detail/pmf_cc.hpp>
		#undef CALLABLE_TRAITS_CC
        #undef CALLABLE_TRAITS_CC_TAG
		#endif

	}
}

#endif
