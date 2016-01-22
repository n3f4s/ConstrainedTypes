#pragma once

#include <type_traits>
#include <iostream>

namespace nfs
{

template < typename parent >
struct unary_operator {
    constexpr parent operator-() const
    {
        static_assert( std::is_signed< typename parent::value_t >::value,
                       "Can't get the opposite of an unsigned number" );
        return parent{-parent::value_};
    }

    constexpr parent operator+() const { return parent{+parent::value_}; }

    constexpr parent operator~() const { return parent{~parent::value_}; }
};

template < typename parent >
struct increment_operator {
    parent& operator++()
    {
        ++parent::value_;
        parent::check_invariant();
        return *this;
    }
    parent& operator++( int )
    {
        auto tmp = *this;
        ++parent::value_;
        parent::check_invariant();
        return tmp;
    }
    parent& operator--()
    {
        --parent::value_;
        parent::check_invariant();
        return *this;
    }
    parent& operator--( int )
    {
        auto tmp = *this;
        --parent::value_;
        parent::check_invariant();
        return tmp;
    }
};

template < typename parent >
struct comparison_operator {
    friend constexpr bool operator==( const parent& lhs, const parent& rhs )
    {
        return lhs.value_ == rhs.value_;
    }
    friend constexpr bool operator!=( const parent& lhs, const parent& rhs )
    {
        return lhs.value_ != rhs.value_;
    }
    friend constexpr bool operator<( const parent& lhs, const parent& rhs )
    {
        return lhs.value_ < rhs.value_;
    }
    friend constexpr bool operator>( const parent& lhs, const parent& rhs )
    {
        return lhs.value_ > rhs.value_;
    }
    friend constexpr bool operator<=( const parent& lhs, const parent& rhs )
    {
        return lhs.value_ <= rhs.value_;
    }
    friend constexpr bool operator>=( const parent& lhs, const parent& rhs )
    {
        return lhs.value_ >= rhs.value_;
    }
};
template < typename parent >
struct stream_operator {
    friend std::ostream& operator<<( std::ostream& os, const parent& rhs )
    {
        os << rhs.value_;
        return os;
    }
    friend std::istream& operator>>( std::istream& is, parent& rhs )
    {
        typename parent::value_t value;
        is >> value;
        const parent& tmp{value};
        rhs = tmp;
        return is;
    }
};
}  // namespace nfs
