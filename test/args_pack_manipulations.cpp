#include <tuple>
#include <utility>
#include <type_traits>
#include <boost/callable_traits/detail/config.hpp>

#include <boost/callable_traits/detail/sfinae_errors.hpp>
#include "test.hpp"


BOOST_CLBL_TRTS_DETAIL_NAMESPACE_BEGIN

template<typename... Ts>
struct pack {

#define BOOST_CLBL_TRTS_BEGIN_PACK_MANIP void(
#define BOOST_CLBL_TRTS_ARGS_PACK Ts
#define BOOST_CLBL_TRTS_END_PACK_MANIP , ... )
#include <boost/callable_traits/detail/unguarded/args_pack_manipulations.hpp>

};  

BOOST_CLBL_TRTS_DETAIL_NAMESPACE_END


using namespace boost::callable_traits::detail;
template<int I>
struct N {};

int main() {

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::remove_args<0>;
        using expect = void(N<1>, N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::remove_args<1>;
        using expect = void(N<0>, N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::remove_args<2>;
        using expect = void(N<0>, N<1>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::remove_args<3>;
        using expect = void(N<0>, N<1>, N<2>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::remove_args<4>;
        using expect = void(N<0>, N<1>, N<2>, N<3>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::remove_args<0, 5>;
        using expect = void(...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::remove_args<0, 3>;
        using expect = void(N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::remove_args<3, 2>;
        using expect = void(N<0>, N<1>, N<2>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::remove_args<4, 1>;
        using expect = void(N<0>, N<1>, N<2>, N<3>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::pop_front<2>;
        using expect = void(N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}

