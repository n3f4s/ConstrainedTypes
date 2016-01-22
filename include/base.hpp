#pragma once

#include <type_traits>
#include <cassert>
#include <utility>
#include <iostream>
#include <functional>

#include "arithmetic_binary_op.hpp"
#include "bitwise_binary_op.hpp"

namespace nfs
{
namespace constrained_types
{
    // TODO : change parameter order (swap error_handle with constraint_t
    // TODO : see forward
    /**
     * @brief base class for constrained type
     */
    template < typename T, class Constraint_t >
    class Base_Type
    {
      public:
        using value_t = T;
        using base_t  = Base_Type< T, Constraint_t >;
        // Base_Type< T, constraint_t, error_handle, constraint_param... >;
        // using Constraint_t =
        // constraint_t< T, error_handle, constraint_param... >;

        Base_Type( T value ) : value_{value} { check_invariant(); }

        // template < typename std::enable_if< Constraint_t::has_default,
        // int >::type t = 0 >
        Base_Type() : Base_Type{Constraint_t::default_value} {}

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

    /**
     * @brief wrapper for Base_Type
     */
    template < typename T,
               typename Constraint_t,
               template < typename, typename > class... operators >
    struct Type : Base_Type< T, Constraint_t >,
                  operators< Base_Type< T, Constraint_t >, T >... {

        using base = Base_Type< T, Constraint_t >;

        Type( T val ) : base{val} {}

        // TODO : pourquoi ça fail avec enable_if
        // template < typename std::enable_if< Constraint_t::has_default,
        // int >::type t = 0 >
        Type() : base{}
        {
            static_assert( Constraint_t::has_default,
                           "This type could not be default constructed" );
        }
    };
}
}
