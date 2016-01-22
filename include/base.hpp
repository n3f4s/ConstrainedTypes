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
     *
     * \tparam T type to be constrained
     * \tparam Constraint_t constraint to apply to T
     */
    template < typename T, class Constraint_t >
    class Base_Type
    {
      public:
        /// alias for T
        using value_t = T;
        /// alias for Base<T, Constraint_t>
        using base_t = Base_Type< T, Constraint_t >;

        /// Ctor with value (not explicit)
        Base_Type( T value ) : value_{value} { check_invariant(); }

        Base_Type() : Base_Type{Constraint_t::default_value} {}

        Base_Type( const Base_Type& ) = default;
        Base_Type( Base_Type&& ) = default;

        /// explicit conversion to T
        explicit constexpr operator T() const { return value_; }

        /// explicit conversion to bol
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
     * @brief Constrained type (designed to be used)
     *
     * This type is the type to use for adding constraint to a type.
     * It is composable (with template) to add constraint and (optional)
     * operators
     *
     * \tparam T type to be constraint
     * \tparam Constraint_t constraint to add to the type
     * \tparam operators operator available for the (constrained) type
     */
    template < typename T,
               typename Constraint_t,
               template < typename, typename > class... operators >
    struct Type : Base_Type< T, Constraint_t >,
                  operators< Base_Type< T, Constraint_t >, T >... {

        using base = Base_Type< T, Constraint_t >;

        Type( T val ) : base{val} {}

        // TODO : find why it don't work with enable_if
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
