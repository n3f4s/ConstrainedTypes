#pragma once

namespace nfs
{
namespace binary_operator
{
    template < typename return_type, typename parameter_type >
    struct multiply {
        friend constexpr return_type operator*( return_type const& lhs,
                                                return_type const& rhs )
        {
            return return_type{static_cast< parameter_type >( lhs ) *
                               static_cast< parameter_type >( rhs )};
        }
        friend constexpr return_type operator*( return_type const& lhs,
                                                parameter_type const& rhs )
        {
            return return_type{static_cast< parameter_type >( lhs ) * rhs};
        }
    };

    template < typename return_type, typename parameter_type >
    struct add {
        friend constexpr return_type operator+( return_type const& lhs,
                                                return_type const& rhs )
        {
            return return_type{static_cast< parameter_type >( lhs ) +
                               static_cast< parameter_type >( rhs )};
        }
        friend constexpr return_type operator+( return_type const& lhs,
                                                parameter_type const& rhs )
        {
            return return_type{static_cast< parameter_type >( lhs ) + rhs};
        }
    };

    template < typename return_type, typename parameter_type >
    struct substract {
        friend constexpr return_type operator-( return_type const& lhs,
                                                return_type const& rhs )
        {
            return return_type{static_cast< parameter_type >( lhs ) -
                               static_cast< parameter_type >( rhs )};
        }
        friend constexpr return_type operator-( return_type const& lhs,
                                                parameter_type const& rhs )
        {
            return return_type{static_cast< parameter_type >( lhs ) - rhs};
        }
    };

    template < typename return_type, typename parameter_type >
    struct divide {
        friend constexpr return_type operator/( return_type const& lhs,
                                                return_type const& rhs )
        {
            return return_type{static_cast< parameter_type >( lhs ) /
                               static_cast< parameter_type >( rhs )};
        }
        friend constexpr return_type operator/( return_type const& lhs,
                                                parameter_type const& rhs )
        {
            return return_type{static_cast< parameter_type >( lhs ) / rhs};
        }
    };

    template < typename return_type, typename parameter_type >
    struct modulo {
        friend constexpr return_type operator%( return_type const& lhs,
                                                parameter_type const& rhs )
        {
            return return_type{static_cast< parameter_type >( lhs ) % rhs};
        }
    };

    template < typename return_type, typename parameter_type >
    struct arithmetic_operator : multiply< return_type, parameter_type >,
                              add< return_type, parameter_type >,
                              divide< return_type, parameter_type >,
                              modulo< return_type, parameter_type > {
    };
}
}
