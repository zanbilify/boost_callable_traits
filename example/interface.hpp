// (C) Copyright Tobias Schwinger
// (C) Copyright 2016 (Modified Work) Barrett Adair
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//[ interface_header

#include <callable_traits/arg_at.hpp>
#include <callable_traits/result_of.hpp>
#include <callable_traits/push_front.hpp>
#include <callable_traits/expand_args.hpp>
#include <callable_traits/replace_arg.hpp>
#include <callable_traits/function_type.hpp>
#include <callable_traits/set_qualifiers.hpp>
#include <callable_traits/qualifier_flags.hpp>
#include <callable_traits/copy_qualifiers.hpp>
#include <callable_traits/is_like_function.hpp>
#include <callable_traits/remove_member_cv.hpp>
#include <callable_traits/get_qualifier_flags.hpp>
#include <callable_traits/apply_member_pointer.hpp>
#include <callable_traits/remove_member_reference.hpp>
#include <callable_traits/qualified_parent_class_of.hpp>
#include <callable_traits/get_member_qualifier_flags.hpp>

#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#include <utility>
#include <type_traits>

namespace intrfc {

    namespace ct = callable_traits;

    //this is our placeholder parent class for member pointers
    struct secret {};

    // used to forward a parameter without copying it
    template<typename T>
    using forward_t = std::conditional_t< sizeof(void*) < sizeof(T)
        , std::add_lvalue_reference_t< std::add_const_t<T> >, T>;

    // The member struct erases the object reference type that is supplied by
    // function_type, which aliases an INVOKE-aware function type when
    // a pmf is passed to it. We overwrite the first argument (which is
    // a reference to an object of the member ptr's parent class, as required
    // by INVOKE) with void*.

    template<typename Ptr, Ptr Value, bool IsPmf = std::is_member_function_pointer<Ptr>::value>
    struct member;

    // this is our type erasure "glue". member<...>::wrapper::wrap is a static member function which
    // casts a void* back to its original object type, and invokes the appropriate member. This first
    // definition handles member functions.
    template<typename Pmf, Pmf PmfValue>
    struct member<Pmf, PmfValue, true> {

        // qualified_parent_class_of yields a reference type which is qualified
        // according to the member function type.
        using context =
            std::remove_reference_t<ct::qualified_parent_class_of<Pmf>>;

        template<typename... Args>
        struct member_wrapper {

            static inline decltype(auto)
            wrap(void* c, ::intrfc::forward_t<Args>... args) {
                return (reinterpret_cast<context*>(c)->*PmfValue)(args...);
            };
        };

        // expand_args is used to expand the argument types into member_wrapper
        using wrapper = ::intrfc::ct::expand_args<Pmf, member_wrapper>;
    };

    // This specialization handles member data.
    template<typename T, typename C, T C::* PmdValue>
    struct member<T C::*, PmdValue, false> {

        using no_ref = std::remove_reference_t<T>;

        static constexpr const bool is_const = std::is_const<no_ref>::value;

        using context = std::conditional_t<is_const, const C, C>;

        struct wrapper {

            static inline T&
            wrap(void* c) {
                return reinterpret_cast<context*>(c)->*PmdValue;
            };
        };
    };
}

// BOOST_PP_NIL is not defined - the code below is simply a large comment
#ifdef BOOST_PP_NIL

DEFINE_INTERFACE(interface_x,
  (( print_member_data, void() const ))
  (( member_data, int ))
);

// The above macro invocation would expand to the following code (sans comments and formatting, of course):

// most of our implementation logic is dumped into this
// class to reduce the chance of naming conflicts. We could
// use a namespace instead, except that namespaces can't be
// opened inside class definition. Anywhere you see "interface_x",
// "print_member_data", and "member_data", remember that these
// names originate from the macro parameters.
struct interface_x_detail {

    // This will be our root base class, containing our vtable and void*
    // necessary for type erasure.
    struct interface_root {

        struct vtable {

            template <typename T = ::intrfc::secret>
            struct member_info0 {

                // this comes from the from the macro parameters
                using member_type = void() const;

                // this definition is only used for member data
                template <typename U, typename Member = member_type,
                    bool = std::has_member_qualifiers<member_type>::value>
                struct member_info {

                    using result_type = std::add_lvalue_reference_t<Member>;
                    using ptr_type = Member U::*;

                    // we will use these later to correctly re-construct our interface function
                    using qualifiers =
                        decltype(::intrfc::ct::get_qualifier_flags<Member>());

                    // Our type erasure scheme will use a function to dereference
                    // pointers to member data
                    using type_erased_ptr = result_type(*)(void *);
                };

                // this specialization is only used for member functions
                template <typename U>
                struct member_info<U, member_type, true> {

                    using ptr_type = member_type U::*;
                    using result_type = ::intrfc::ct::result_of<ptr_type>;

                    // The first argument of this function type is a qualified U
                    // reference, because function_type is defined in terms of INVOKE
                    using function_type = ::intrfc::ct::function_type<ptr_type>;

                    // we will use these later to correctly re-construct our forwarding
                    // interface function
                    using qualifiers =
                        decltype(::intrfc::ct::get_member_qualifier_flags<ptr_type>());

                    // overwriting the first argument with void*, "erasing" the
                    // qualified U reference. We then make it a function pointer.
                    using type_erased_ptr =
                        ::intrfc::ct::replace_arg<0, function_type, void*> *;
                };

                // these aliases simply make later code easier to follow
                using info = member_info<T>;
                using ptr_type = typename info::ptr_type;
                using result_type = typename info::result_type;
                using type_erased_ptr = typename info::type_erased_ptr;
                using qualifiers = typename info::qualifiers;
            };

            // this alias saves us some typing later
            using pmf0 = typename member_info0<>::ptr_type;

            // This is our vtable function pointer entry, which will be initialized
            // at compile-time.
            typename member_info0<>::type_erased_ptr func0;

            // repeating for additional members supplied by the macro
            template <typename T = ::intrfc::secret>
            struct member_info1 {

                // this comes from the from the macro parameters
                using member_type = int;

                template <typename U, typename Member = member_type,
                    bool = ::intrfc::ct::is_like_function<member_type>()>
                struct member_info {

                    using result_type = std::add_lvalue_reference_t<Member>;
                    using ptr_type = Member U::*;
                    using qualifiers =
                        decltype(::intrfc::ct::get_qualifier_flags<Member>());
                    using type_erased_ptr = result_type(*)(void *);
                };

                template <typename U>
                struct member_info<U, member_type, true> {

                    using ptr_type = member_type U::*;
                    using result_type = ::intrfc::ct::result_of<ptr_type>;
                    using function_type = ::intrfc::ct::function_type<ptr_type>;

                    using qualifiers =
                        decltype(::intrfc::ct::get_member_qualifier_flags<ptr_type>());

                    using type_erased_ptr =
                        ::intrfc::ct::replace_arg<0, function_type, void *> *;
                };

                using info = member_info<T>;
                using ptr_type = typename info::ptr_type;
                using result_type = typename info::result_type;
                using type_erased_ptr = typename info::type_erased_ptr;
                using qualifiers = typename info::qualifiers;
            };

            using pmf1 = typename member_info1<>::ptr_type;
            typename member_info1<>::type_erased_ptr func1;
        };

        //our two data members
        const vtable *ptr_vtable;
        void *obj_ptr;

        // conversion constructor that creates an interface from an arbitrary class
        template <class T>
        inline interface_root(T &that)
            : ptr_vtable(&vtable_holder<T>::val_vtable),
            obj_ptr(std::addressof(that))
        {}

        // This template is instantiated for every class from which this interface
        // is constructed (see constructor above). This instantiation causes the
        // compiler to emit an initialized vtable for this type (via aggregate
        // assignment later in the code).
        template <class T>
        struct vtable_holder { static const vtable val_vtable; };
    };

    // this definition will not be used, but is necessary for eager template instantiation
    template <int I, typename Ignored = ::intrfc::secret>
    struct base {
        using type = Ignored;
    };

    // We use get_next_base to chain together our base classes, starting with interface_root.
    // The rest of the classes each contain an interface member.
    template <int I>
    using get_next_base =
        std::conditional_t<I == 0, interface_root, typename base<I - 1>::type>;

    // base_impl0 defines the first member supplied by the macro, specializing on
    // the qualifiers that exist on the supplied member. The appropriate "apply"
    // specialization will serve as a base class for our interface.
    template <typename... Args>
    struct base_impl0 {

        template < ::intrfc::ct::flags QualifierFlags,
            typename Base = get_next_base<0>>
        struct apply;

        // for unqualified member functions/data
        template <typename Base>
        struct apply< ::intrfc::ct::default_, Base> : Base {

            using Base::Base;
            using Base::ptr_vtable;
            using Base::obj_ptr;

            inline decltype(auto)
            print_member_data( ::intrfc::forward_t<Args>... args) {
                return ptr_vtable->func0(obj_ptr, args...);
            }
        };

        // for const-qualified member functions/data
        template <typename Base>
        struct apply<::intrfc::ct::const_, Base> : Base {

            using Base::Base;
            using Base::ptr_vtable;
            using Base::obj_ptr;

            inline decltype(auto)
            print_member_data(::intrfc::forward_t<Args>... args) const {
                return ptr_vtable->func0(obj_ptr, args...);
            }
        };

        // for volatile-qualified member functions/data
        template <typename Base>
        struct apply<::intrfc::ct::volatile_, Base> : Base {

            using Base::Base;
            using Base::ptr_vtable;
            using Base::obj_ptr;

            inline decltype(auto)
            print_member_data(::intrfc::forward_t<Args>... args) volatile {
                return ptr_vtable->func0(obj_ptr, args...);
            }
        };

        // for const-volatile-qualified member functions/data
        template <typename Base>
        struct apply<(::intrfc::ct::const_ | ::intrfc::ct::volatile_), Base> : Base {

            using Base::Base;
            using Base::ptr_vtable;
            using Base::obj_ptr;

            inline decltype(auto)
            print_member_data(::intrfc::forward_t<Args>... args) const volatile {
                return ptr_vtable->func0(obj_ptr, args...);
            }
        };
    };

    // this specialization helps link the bases together
    template <typename Ignored>
    struct base<0, Ignored> {
        using impl = ::intrfc::ct::expand_args<
            typename interface_root::vtable::pmf0, base_impl0>;

        using qualifiers =
            typename interface_root::vtable::member_info0<>::qualifiers;

        using type = impl::template apply<qualifiers::value>;
    };

    // repeat for additional interface members
    template <typename... Args>
    struct base_impl1 {

        template <::intrfc::ct::flags QualifierFlags,
            typename Base = get_next_base<1>>
        struct apply;

        template <typename Base>
        struct apply<::intrfc::ct::default_, Base> : Base {

            using Base::Base;
            using Base::ptr_vtable;
            using Base::obj_ptr;

            inline decltype(auto)
            member_data(::intrfc::forward_t<Args>... args) {
                return ptr_vtable->func1(obj_ptr, args...);
            }
        };

        template <typename Base>
        struct apply<::intrfc::ct::const_, Base> : Base {

            using Base::Base;
            using Base::ptr_vtable;
            using Base::obj_ptr;

            inline decltype(auto)
            member_data(::intrfc::forward_t<Args>... args) const {
                return ptr_vtable->func1(obj_ptr, args...);
            }
        };

        template <typename Base>
        struct apply<::intrfc::ct::volatile_, Base> : Base {

            using Base::Base;
            using Base::ptr_vtable;
            using Base::obj_ptr;

            inline decltype(auto)
            member_data(::intrfc::forward_t<Args>... args) volatile {
                return ptr_vtable->func1(obj_ptr, args...);
            }
        };

        template <typename Base>
        struct apply<(::intrfc::ct::const_ | ::intrfc::ct::volatile_), Base> : Base {

            using Base::Base;
            using Base::ptr_vtable;
            using Base::obj_ptr;

            inline decltype(auto)
            member_data(::intrfc::forward_t<Args>... args) const volatile {
                return ptr_vtable->func1(obj_ptr, args...);
            }
        };
    };

    template <typename Ignored>
    struct base<1, Ignored> {

        using impl = ::intrfc::ct::expand_args<
            typename interface_root::vtable::pmf1, base_impl1>;

        using qualifiers =
            typename interface_root::vtable::member_info1<>::qualifiers;

        using type = impl::template apply<qualifiers::value>;
    };
};

// this initializes the vtable at compile time for every class used to construct an
// interface_x object. Member functions and member data are both handled.
template <typename T>
interface_x_detail::interface_root::vtable const
    interface_x_detail::interface_root::vtable_holder<T>::val_vtable = {

        &::intrfc::member<
            typename vtable::member_info0<T>::ptr_type,
            &T::print_member_data
        >::wrapper::wrap,

        &::intrfc::member<
            typename vtable::member_info1<T>::ptr_type,
            &T::member_data
        >::wrapper::wrap
};

// We inherit the base for the last member, which inherits all
// the bases before it. This strategy keeps our runtime memory layout
// as small as possible, but unfortunately increases compile times.
struct interface_x : interface_x_detail::base<2 - 1>::type {

    using detail = interface_x_detail;
    using base = typename detail::base<2 - 1>::type;

    template<typename T, std::enable_if_t<
        !std::is_base_of<interface_root, std::decay_t<T>>::value, int> = 0>
        inline interface_x(T &that) : base(that) {}

    inline interface_x(const interface_x &) = default;

    // These using declarations assist with IDE code-completion
    using detail::base<0>::type::print_member_data;
    using detail::base<1>::type::member_data;
};

#endif

// the interface definition on the client's side
#define DEFINE_INTERFACE(name,def)                                      \
struct BOOST_PP_CAT(name, _detail) {                                    \
                                                                        \
    struct interface_root {                                             \
                                                                        \
        struct vtable {                                                 \
                                                                        \
            CALLABLE_TRAITS_INTERFACE__MEMBERS(def, VTABLE)             \
        };                                                              \
                                                                        \
        const vtable * ptr_vtable;                                      \
        void* obj_ptr;                                                  \
                                                                        \
        template <class T>                                              \
        inline interface_root(T& that)                                  \
            : ptr_vtable(&vtable_holder<T>::val_vtable),                \
            obj_ptr(std::addressof(that)) {}                            \
                                                                        \
        template <class T>                                              \
        struct vtable_holder {                                          \
            static const vtable val_vtable;                             \
        };                                                              \
    };                                                                  \
                                                                        \
    template <int I, typename Ignored = ::intrfc::secret>               \
    struct base{                                                        \
        using type = Ignored;                                           \
    };                                                                  \
                                                                        \
    template<int I>                                                     \
    using get_next_base = std::conditional_t<                           \
        I == 0, interface_root, typename base<I - 1>::type>;            \
                                                                        \
    CALLABLE_TRAITS_INTERFACE__MEMBERS(def, BASES)                      \
};                                                                      \
                                                                        \
template <typename T>                                                   \
BOOST_PP_CAT(name, _detail)::interface_root::vtable const               \
    BOOST_PP_CAT(name, _detail)::interface_root::vtable_holder<T>       \
        ::val_vtable =                                                  \
            { CALLABLE_TRAITS_INTERFACE__MEMBERS(def, INIT_VTABLE) };   \
                                                                        \
struct name : BOOST_PP_CAT(name, _detail)                               \
    ::base<BOOST_PP_SEQ_SIZE(def) - 1>::type {                          \
                                                                        \
    using detail = BOOST_PP_CAT(name, _detail);                         \
    using base =                                                        \
        typename detail::base<BOOST_PP_SEQ_SIZE(def) - 1>::type;        \
                                                                        \
    template<typename T, std::enable_if_t<                              \
        !std::is_base_of<interface_root,                                \
            std::decay_t<T>>::value, int> = 0>                          \
    inline name(T& that) : base(that) {}                                \
                                                                        \
    inline name(const name &) = default;                                \
                                                                        \
    CALLABLE_TRAITS_INTERFACE__MEMBERS(def, USING_DECLARATIONS)         \
}                                                                       \
/**/


// preprocessing code details

// iterate all of the interface's members and invoke a macro, prefixed
// with CALLABLE_TRAITS_INTERFACE__
#define CALLABLE_TRAITS_INTERFACE__MEMBERS(seq,macro)                  \
    BOOST_PP_REPEAT(BOOST_PP_SEQ_SIZE(seq),                            \
        CALLABLE_TRAITS_INTERFACE__ ## macro, seq)                     \
/**/

// generate the vtable initilizer code
#define CALLABLE_TRAITS_INTERFACE__INIT_VTABLE(z,i,seq)                \
    CALLABLE_TRAITS_INTERFACE__INIT_VTABLE_I(i,                        \
        BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_SEQ_ELEM(i,seq)))             \
/**/

#define CALLABLE_TRAITS_INTERFACE__INIT_VTABLE_I(i,mem)                \
    BOOST_PP_COMMA_IF(i)                                               \
        &::intrfc::member<                                             \
            typename vtable::BOOST_PP_CAT(member_info, i)<T>::ptr_type,\
            &T::mem                                                    \
        >::wrapper::wrap                                               \
/**/

//generate the vtable
#define CALLABLE_TRAITS_INTERFACE__VTABLE(z,i,seq)                     \
    CALLABLE_TRAITS_INTERFACE__VTABLE_I(z,i,                           \
        BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_SEQ_ELEM(i,seq)))             \
/**/

#define CALLABLE_TRAITS_INTERFACE__VTABLE_I(z,i,signature)             \
template<typename T = ::intrfc::secret>                                \
struct BOOST_PP_CAT(member_info, i) {                                  \
                                                                       \
    using member_type = signature;                                     \
                                                                       \
    template<typename U, typename Member = member_type,                \
        bool = ::intrfc::ct::is_like_function<member_type>()>          \
    struct member_info {                                               \
                                                                       \
        using result_type = std::add_lvalue_reference_t<Member>;       \
        using ptr_type = Member U::*;                                  \
                                                                       \
        using qualifiers =                                             \
            decltype( ::intrfc::ct::get_qualifier_flags<Member>());    \
                                                                       \
        using type_erased_ptr = result_type(*)(void*);                 \
    };                                                                 \
                                                                       \
    template<typename U>                                               \
    struct member_info <U, member_type, true> {                        \
                                                                       \
        using ptr_type = member_type U::*;                             \
        using result_type = ::intrfc::ct::result_of<ptr_type>;         \
        using function_type = ::intrfc::ct::function_type<ptr_type>;   \
                                                                       \
        using qualifiers = decltype(                                   \
            ::intrfc::ct::get_member_qualifier_flags<ptr_type>());     \
                                                                       \
        using type_erased_ptr =                                        \
            ::intrfc::ct::replace_arg<0, function_type, void*> *;     \
    };                                                                 \
                                                                       \
    using info = member_info<T>;                                       \
    using ptr_type = typename info::ptr_type;                          \
    using result_type = typename info::result_type;                    \
    using type_erased_ptr = typename info::type_erased_ptr;            \
    using qualifiers = typename info::qualifiers;                      \
};                                                                     \
                                                                       \
using BOOST_PP_CAT(pmf, i) =                                           \
    typename BOOST_PP_CAT(member_info, i)<>::ptr_type;                 \
                                                                       \
typename BOOST_PP_CAT(member_info, i)<>                                \
    ::type_erased_ptr BOOST_PP_CAT(func, i);                           \
/**/

// generate the bases, each of which will contain a public-facing
// interface function
#define CALLABLE_TRAITS_INTERFACE__BASES(z,i,seq)                      \
    CALLABLE_TRAITS_INTERFACE__BASES_I(i,                              \
        BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_SEQ_ELEM(i,seq)))             \
/**/

#define CALLABLE_TRAITS_INTERFACE__BASES_I(i, mem)                     \
template<typename... Args>                                             \
struct BOOST_PP_CAT(base_impl, i) {                                    \
                                                                       \
    template<::intrfc::ct::flags QualifierFlags,                       \
        typename Base = get_next_base<i>>                              \
    struct apply;                                                      \
                                                                       \
    CALLABLE_TRAITS_INTERFACE__BASES_APPLY(i, mem,                     \
      ::intrfc::ct::default_, BOOST_PP_EMPTY())                        \
                                                                       \
    CALLABLE_TRAITS_INTERFACE__BASES_APPLY(i, mem,                     \
      ::intrfc::ct::const_, const)                                     \
                                                                       \
    CALLABLE_TRAITS_INTERFACE__BASES_APPLY(i, mem,                     \
      ::intrfc::ct::volatile_, volatile)                               \
                                                                       \
    CALLABLE_TRAITS_INTERFACE__BASES_APPLY(i, mem,                     \
      (::intrfc::ct::const_ | ::intrfc::ct::volatile_), const volatile)\
};                                                                     \
                                                                       \
template <typename Ignored>                                            \
struct base<i, Ignored> {                                              \
                                                                       \
    using impl = ::intrfc::ct::expand_args<                            \
        typename interface_root::vtable::BOOST_PP_CAT(pmf, i),         \
        BOOST_PP_CAT(base_impl, i)>;                                   \
                                                                       \
    using qualifiers =                                                 \
        typename interface_root::vtable::BOOST_PP_CAT(member_info, i)<>\
            ::qualifiers;                                              \
                                                                       \
    using type = impl::template apply<qualifiers::value>;              \
};                                                                     \
/**/

// generate specializations based on qualifiers on member functions/data.
// lvalue and rvalue member functions are ignored.
#define CALLABLE_TRAITS_INTERFACE__BASES_APPLY(i, mem, flags, qualifiers) \
    template<typename Base>                                            \
    struct apply<flags, Base> : Base {                                 \
                                                                       \
        using Base::Base;                                              \
        using Base::ptr_vtable;                                        \
        using Base::obj_ptr;                                           \
                                                                       \
        inline decltype(auto)                                          \
        mem(::intrfc::forward_t<Args>... args) qualifiers {            \
            return ptr_vtable->BOOST_PP_CAT(func, i)(obj_ptr, args...);\
        }                                                              \
    };                                                                 \
/**/

#define CALLABLE_TRAITS_INTERFACE__USING_DECLARATIONS(z,i,seq)         \
    using detail::base<i>::type::                                      \
        BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_SEQ_ELEM(i,seq));             \
/**/

//]
