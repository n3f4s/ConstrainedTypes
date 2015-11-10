#pragma once

#include <iostream>
#include <string>

// TODO : passer en ref pour over/underflow
template < typename T, typename error_function >
struct Constraint {

    static constexpr bool has_default = false;

    void check_invariant( T& ) const {}

    template < typename numeric_t, typename Op >
    typename numeric_t::value_t inplace_op( typename numeric_t::value_t lhs,
                                            typename numeric_t::value_t rhs,
                                            Op op ) const
    {
        return static_cast< typename numeric_t::value_t >(
            numeric_t{op( lhs, rhs )} );
    }

  protected:
    error_function func;
};

template < typename T, T lower_bound, T upper_bound, typename error_function >
struct Strict_Range : Constraint< T, error_function > {

    static constexpr T default_value  = lower_bound + T{1};
    static constexpr bool has_default = true;

    void check_invariant( T& value ) const
    {
        auto fun = Constraint< T, error_function >::func;
        if( !( lower_bound < value ) ) error( lower_bound < value, fun );
        if( !( value < upper_bound ) ) error( value < upper_bound, fun );
    }
};

template < typename T, typename error_function >
struct Not_Null : Constraint< T, error_function > {

    static constexpr bool has_default = false;

    void check_invariant( T& value ) const
    {
        auto fun = Constraint< T, error_function >::func;
        if( !value ) error( value != 0, fun );
    }
};

template < typename T, typename error_function, unsigned int mod >
struct Modulo : Constraint< T, error_function > {
    static constexpr bool has_default = true;
    static constexpr T default_value  = 0;

    void check_invariant( T& value ) const { value = value % mod; }
};

// TODO : faire en sorte que les __FUNCTION__ ... pointent sur les bonnes
// fonctions
struct invariant_checker {
    void operator()( std::string func, std::string cond )
    {
        std::cerr << func << " : " << cond << " failed" << std::endl;
        std::abort();
    }
};
