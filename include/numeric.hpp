#pragma once

#include <type_traits>
#include <cassert>
#include <utility>
#include <iostream>
#include <functional>

namespace nfs
{
namespace constrained_types
{
    template < typename T, template<typename, typename, T...> class constraint_t, typename error_handle, T ...constraint_param>
    class Numeric_Type
    {
      public:
        using value_t   = T;
        using numeric_t = Numeric_Type< T, constraint_t, error_handle, constraint_param...>;
        using Constraint_t = constraint_t<T, error_handle, constraint_param...>;//TODO : changer l'ordre des templates dans Constraint

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

        // inplace arithmetic operator
        Numeric_Type& operator+=( numeric_t rhs )
        {
            *this = inplace_op(
                value_, rhs.value_, []( auto l, auto r ) { return l + r; } );
            return *this;
        }
        Numeric_Type& operator*=( numeric_t rhs )
        {
            *this = inplace_op(
                value_, rhs.value_, []( auto l, auto r ) { return l * r; } );
            return *this;
        }
        Numeric_Type& operator/=( numeric_t rhs )
        {
            *this = inplace_op(
                value_, rhs.value_, []( auto l, auto r ) { return l / r; } );
            return *this;
        }
        Numeric_Type& operator-=( numeric_t rhs )
        {
            *this = inplace_op(
                value_, rhs.value_, []( auto l, auto r ) { return l - r; } );
            return *this;
        }
        Numeric_Type& operator%=( numeric_t rhs )
        {
            *this = inplace_op(
                value_, rhs.value_, []( auto l, auto r ) { return l % r; } );
            return *this;
        }

        // Inplace bitwise operator
        Numeric_Type& operator<<=(
            const numeric_t& count )
        {
            *this = inplace_op(
                value_, count.value_, []( auto l, auto r ) { return l << r; } );
            return *this;
        }

        Numeric_Type& operator>>=(
            const numeric_t& count )
        {
            *this = inplace_op(
                value_, count.value_, []( auto l, auto r ) { return l << r; } );
            return *this();
        }

        Numeric_Type& operator&=( const numeric_t& peer )
        {
            *this = inplace_op(
                value_, peer.value_, []( auto l, auto r ) { return l << r; } );
            return *this();
        }

        Numeric_Type& operator^=( const numeric_t& peer )
        {
            *this = inplace_op(
                value_, peer.value_, []( auto l, auto r ) { return l << r; } );
            return *this();
        }

        Numeric_Type& operator|=( const numeric_t& peer )
        {
            *this = inplace_op(
                value_, peer.value_, []( auto l, auto r ) { return l << r; } );
            return *this();
        }

        // Increment/Decrement operator
        Numeric_Type& operator++()
        {
            ++value_;
            check_invariant();
            return *this;
        }
        Numeric_Type& operator++( int )
        {
            auto tmp = *this;
            ++value_;
            check_invariant();
            return tmp;
        }
        Numeric_Type& operator--()
        {
            --value_;
            check_invariant();
            return *this;
        }
        Numeric_Type& operator--( int )
        {
            auto tmp = *this;
            --value_;
            check_invariant();
            return tmp;
        }

        // Unary arithmetic operator
        constexpr Numeric_Type operator-() const
        {
            static_assert( std::is_signed< T >::value,
                           "Can't get the opposite of an unsigned number" );
            return Numeric_Type{-value_};
        }

        constexpr Numeric_Type operator+() const
        {
            return Numeric_Type{+value_};
        }

        constexpr Numeric_Type operator~() const
        {
            return Numeric_Type{~value_};
        }

        Numeric_Type& operator=( const numeric_t& lhs ) =
            default;
        Numeric_Type& operator=( const T& lhs )
        {
            *this = numeric_t{lhs};
            return *this;
        }

        // Binary arithmetic operator
        friend Numeric_Type operator+( numeric_t lhs,
                                       numeric_t rhs )
        {
            return lhs.inplace_op( lhs.value_,
                                   rhs.value_,
                                   []( auto l, auto r ) { return l + r; } );
        }
        friend Numeric_Type operator*( numeric_t lhs,
                                       numeric_t rhs )
        {
            return lhs.inplace_op(
                lhs.value_, rhs, []( auto l, auto r ) { return l * r; } );
        }
        friend Numeric_Type operator-( numeric_t lhs,
                                       numeric_t rhs )
        {
            return lhs.inplace_op(
                lhs.value_, rhs, []( auto l, auto r ) { return l - r; } );
        }
        friend Numeric_Type operator/( numeric_t lhs,
                                       numeric_t rhs )
        {
            return lhs.inplace_op(
                lhs.value_, rhs, []( auto l, auto r ) { return l / r; } );
        }
        friend Numeric_Type operator%( numeric_t lhs,
                                       numeric_t rhs )
        {
            return lhs.inplace_op(
                lhs.value_, rhs, []( auto l, auto r ) { return l % r; } );
        }

        // Binary bitwise operator
        friend Numeric_Type operator<<( numeric_t lhs,
                                        numeric_t rhs )
        {
            return lhs.inplace_op(
                lhs.value_, rhs, []( auto l, auto r ) { return l << r; } );
        }
        friend Numeric_Type operator>>( numeric_t lhs,
                                        numeric_t rhs )
        {
            return lhs.inplace_op(
                lhs.value_, rhs, []( auto l, auto r ) { return l >> r; } );
        }
        friend Numeric_Type operator&( numeric_t lhs,
                                       numeric_t rhs )
        {
            return lhs.inplace_op(
                lhs.value_, rhs, []( auto l, auto r ) { return l & r; } );
        }
        friend Numeric_Type operator^( numeric_t lhs,
                                       numeric_t rhs ) {
            return lhs.inplace_op(
                lhs.value_, rhs, []( auto l, auto r ) { return l ^ r; } );
        } friend Numeric_Type
            operator|( numeric_t lhs,
                       numeric_t rhs )
        {
            return lhs.inplace_op(
                lhs.value_, rhs, []( auto l, auto r ) { return l | r; } );
        }
        friend constexpr bool operator==( numeric_t lhs,
                                          numeric_t rhs )
        {
            return lhs.value_ == rhs.value_;
        }
        friend constexpr bool operator!=( numeric_t lhs,
                                          numeric_t rhs )
        {
            return lhs.value_ != rhs.value_;
        }
        friend constexpr bool operator<( numeric_t lhs,
                                         numeric_t rhs )
        {
            return lhs.value_ < rhs.value_;
        }
        friend constexpr bool operator>( numeric_t lhs,
                                         numeric_t rhs )
        {
            return lhs.value_ > rhs.value_;
        }
        friend constexpr bool operator<=( numeric_t lhs,
                                          numeric_t rhs )
        {
            return lhs.value_ <= rhs.value_;
        }
        friend constexpr bool operator>=( numeric_t lhs,
                                          numeric_t rhs )
        {
            return lhs.value_ >= rhs.value_;
        }
        friend std::ostream& operator<<( std::ostream& os,
                                         numeric_t rhs )
        {
            os << rhs.value_;
            return os;
        }
        friend std::istream& operator>>( std::istream& is,
                                         numeric_t& rhs )
        {
            T value;
            is >> value;
            numeric_t tmp{value};
            rhs = tmp;
            return is;
        }

      private:
        void check_invariant() { constraint_.check_invariant( value_ ); }

        template < typename Op >
        value_t inplace_op( value_t lhs, value_t rhs, Op op )
        {
            return constraint_
                .template inplace_op< numeric_t >(
                    lhs, rhs, op );
        }

        T value_;
        Constraint_t constraint_;
    };
}
}
