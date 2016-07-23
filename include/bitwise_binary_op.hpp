#pragma once

namespace nfs {
namespace binary_operator {
    template <typename return_type, typename parameter_type>
    struct right_shift {
        friend constexpr return_type operator>>(return_type const& lhs,
            return_type const& rhs)
        {
            return return_type{ static_cast<parameter_type>(lhs) >> static_cast<parameter_type>(rhs) };
        }
        friend constexpr return_type operator>>(return_type const& lhs,
            parameter_type const& rhs)
        {
            return return_type{ static_cast<parameter_type>(lhs) >> rhs };
        }
    };

    template <typename return_type, typename parameter_type>
    struct left_shift {
        friend constexpr return_type operator<<(return_type const& lhs,
            return_type const& rhs)
        {
            return return_type{ static_cast<parameter_type>(lhs)
                << static_cast<parameter_type>(rhs) };
        }
        friend constexpr return_type operator<<(return_type const& lhs,
            parameter_type const& rhs)
        {
            return return_type{ static_cast<parameter_type>(lhs) << rhs };
        }
    };

    template <typename return_type, typename parameter_type>
    struct bitwise_and {
        friend constexpr return_type operator&(return_type const& lhs,
            return_type const& rhs)
        {
            return return_type{ static_cast<parameter_type>(lhs) & static_cast<parameter_type>(rhs) };
        }
        friend constexpr return_type operator&(return_type const& lhs,
            parameter_type const& rhs)
        {
            return return_type{ static_cast<parameter_type>(lhs) & rhs };
        }
    };

    template <typename return_type, typename parameter_type>
    struct bitwise_or {
        friend constexpr return_type operator|(return_type const& lhs,
            return_type const& rhs)
        {
            return return_type{ static_cast<parameter_type>(lhs) | static_cast<parameter_type>(rhs) };
        }
        friend constexpr return_type operator|(return_type const& lhs,
            parameter_type const& rhs)
        {
            return return_type{ static_cast<parameter_type>(lhs) | rhs };
        }
    };

    template <typename return_type, typename parameter_type>
    struct bitwise_xor {
        friend constexpr return_type operator^(return_type const& lhs,
            return_type const& rhs)
        {
            return return_type{ static_cast<parameter_type>(lhs) ^ static_cast<parameter_type>(rhs) };
        }
        friend constexpr return_type
        operator^(return_type const& lhs, parameter_type const& rhs)
        {
            return return_type{ static_cast<parameter_type>(lhs) ^ rhs };
        }
    };

    template <typename return_type, typename parameter_type>
    struct bitwise_operator : right_shift<return_type, parameter_type>,
                              left_shift<return_type, parameter_type>,
                              bitwise_and<return_type, parameter_type>,
                              bitwise_or<return_type, parameter_type>,
                              bitwise_xor<return_type, parameter_type> {
    };
}
}
