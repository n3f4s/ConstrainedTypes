#pragma once

#include <type_traits>
#include <cassert>
#include <utility>
#include <iostream>
#include <functional>

#include "operator.hpp"

namespace nfs
{
namespace constrained_types
{
    template < typename T,
               template < typename, typename, T... > class constraint_t,
               typename error_handle,
               T... constraint_param >
    class Numeric_Type
        : arthmetic_operator< Numeric_Type< T,
                                            constraint_t,
                                            error_handle,
                                            constraint_param... > >,
          bitwise_operator< Numeric_Type< T,
                                          constraint_t,
                                          error_handle,
                                          constraint_param... > >,
          unary_operator< Numeric_Type< T,
                                        constraint_t,
                                        error_handle,
                                        constraint_param... > >,
          increment_operator< Numeric_Type< T,
                                            constraint_t,
                                            error_handle,
                                            constraint_param... > >,
          comparison_operator< Numeric_Type< T,
                                             constraint_t,
                                             error_handle,
                                             constraint_param... > >,
          stream_operator< Numeric_Type< T,
                                         constraint_t,
                                         error_handle,
                                         constraint_param... > >

    {
      public:
        using value_t = T;
        using numeric_t =
            Numeric_Type< T, constraint_t, error_handle, constraint_param... >;
        using Constraint_t =
            constraint_t< T, error_handle, constraint_param... >;  // TODO :
                                                                   // changer
                                                                   // l'ordre
                                                                   // des
                                                                   // templates
                                                                   // dans
                                                                   // Constraint

        Numeric_Type( T value ) : value_{value}
        {
            static_assert( std::is_arithmetic< T >::value,
                           "T must be an arithmetic type" );
            check_invariant();
        }
        template < bool B                                    = Constraint_t::has_default,
                   typename std::enable_if< B, int >::type t = 0 >
        Numeric_Type()
            : Numeric_Type{Constraint_t::default_value}
        {
        }

        explicit constexpr operator T() const { return value_; }

        explicit constexpr operator bool() const
        {
            return static_cast< bool >( value_ );
        }

        // TODO : put in an operator struct ?
        Numeric_Type& operator=( const numeric_t& lhs ) = default;
        Numeric_Type& operator=( const T& lhs )
        {
            *this = numeric_t{lhs};
            return *this;
        }

      protected:
        void check_invariant() { constraint_.check_invariant( value_ ); }

        template < typename Op >
        value_t inplace_op( value_t lhs, value_t rhs, Op op )
        {
            return constraint_.template inplace_op< numeric_t >( lhs, rhs, op );
        }

        value_t value_;
        Constraint_t constraint_;
    };
}
}
