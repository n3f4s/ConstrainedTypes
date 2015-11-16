#pragma once

#include <type_traits>
#include <cassert>
#include <utility>
#include <iostream>
#include <functional>

#include "operator.hpp"
#include "arithmetic_binary_op.hpp"
#include "bitwise_binary_op.hpp"

namespace nfs
{
namespace constrained_types
{
    // TODO : change parameter order (swap error_handle with constraint_t
    // TODO : see forward
    template < typename T,
               template < typename, typename, T... > class constraint_t,
               typename error_handle,
               T... constraint_param >
    class Base_Type
    {
      public:
        using value_t = T;
        using base_t =
            Base_Type< T, constraint_t, error_handle, constraint_param... >;
        using Constraint_t =
            constraint_t< T, error_handle, constraint_param... >;

        Base_Type( T value ) : value_{value} { check_invariant(); }

        template < typename std::enable_if< Constraint_t::has_default,
                                            int >::type t = 0 >
        Base_Type()
            : Base_Type{Constraint_t::default_value}
        {
        }

        Base_Type( const Base_Type& ) = default;
        Base_Type( Base_Type&& ) = default;

        explicit constexpr operator T() const { return value_; }

        explicit constexpr operator bool() const
        {
            return static_cast< bool >( value_ );
        }

        // TODO : put in an operator struct ?
        Base_Type& operator=( const base_t& lhs ) = default;
        Base_Type& operator=( base_t&& lhs ) = default;
        Base_Type& operator=( const T& lhs )
        {
            *this = std::move( base_t{lhs} );
            return *this;
        }
        Base_Type& operator=( T&& lhs )
        {
            *this = std::move( base_t{std::move( lhs )} );
            return *this;
        }

      private:
        void check_invariant() { constraint_.check_invariant( value_ ); }

        template < typename Op >
        value_t inplace_op( value_t lhs, value_t rhs, Op op )
        {
            return constraint_.template inplace_op< base_t >( lhs, rhs, op );
        }

        value_t value_;
        Constraint_t constraint_;
    };
    template < typename T,
               typename base,
               template < typename, typename > class... operators >
    struct Type : base, operators< base, T >... {
        Type( T val ) : base{val} {}
    };
}
}
