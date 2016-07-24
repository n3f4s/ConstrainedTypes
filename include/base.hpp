#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <type_traits>
#include <utility>

#include "arithmetic_binary_op.hpp"
#include "bitwise_binary_op.hpp"
#include "constrain.hpp"

/**
 * @file base.hpp
 * @brief Provide type to be aliased for creating new constrained type.
 * @author Vincent
 * @version 0.1
 * @date 2016-07-23
 */

#ifdef HASCONCEPT
#define REQUIRES(concept) requires concept
#else
#define REQUIRES(concept) // use enable_if
#endif                    /* ifndef  */

// TODO : use concept -> define concept for contraint
// TODO : doc

namespace nfs {
namespace constrained_types {
    // TODO : see forward
    /**
     * @brief Base class for constrained type.
     *
     * This class tie together the constraint and the value type.
     * It contains all the boilerplate required to ensure that the constraint
     * is always respected.
     *
     * Define a way to construct a constrained type
     *
     * @tparam T type to be constrained
     * @tparam Constraint_t constraint to apply to T
     */
    template <typename T, class Constraint_t>
        REQUIRES(Is_Constraint_Type<Constraint_t>())
    class Base_Type {
    public:
        /// alias for T
        using value_t = T;
        /// alias for Base<T, Constraint_t>
        using base_t = Base_Type<T, Constraint_t>;
        template <typename S>
        using is_bool_convertible = std::is_convertible<S, bool>;

        /**
         * @brief Constructor for Base_type
         *
         * @param value value of the object
         */
        Base_Type(T&& value)
            : value_{ value }
        {
            check_invariant();
        }

        /**
         * @brief Constructor overloaded for const reference
         *
         * @fixme should not be necessary with universal reference
         *
         * @param value value of the object
         */
        Base_Type(const T& value)
            : value_{ value }
        {
            check_invariant();
        }

        /**
         * @brief Default constructor
         */
        template <typename S = void>
        REQUIRES(Constraint_t::has_default&& std::is_default_constructible<T>::value)
        Base_Type()
            : Base_Type{ Constraint_t::default_value }
        {
        }

        // if is_default_copyable
        template <typename S = void>
        REQUIRES(std::is_copy_constructible<T>::value)
        Base_Type(const Base_Type& t)
            : value_{ t.value_ }
        {
            check_invariant();
        }
        template <typename S = void>
        REQUIRES(std::is_move_constructible<T>::value)
        Base_Type(Base_Type&& t)
            : value_{ std::move(t.value_) }
        {
            check_invariant();
        }

        /// explicit conversion to T
        explicit constexpr operator T() const { return value_; }

        /// explicit conversion to bol
        template <typename S = void>
        REQUIRES(is_bool_convertible<T>::value)
        explicit constexpr operator bool() const
        {
            return static_cast<bool>(value_);
        }

        template <typename S = void>
        REQUIRES(std::is_copy_assignable<T>::value)
        Base_Type& operator=(const base_t& lhs){
            *this = std::move(lhs);
            return *this;
        }
        template <typename S = void>
        REQUIRES(std::is_move_assignable<T>::value)
        Base_Type& operator=(base_t&& lhs) {
            *this = std::move(lhs);
            return *this;
        }

        /// assignement from T
        Base_Type& operator=(const T& lhs)
        {
            *this = std::move(base_t{ lhs });
            return *this;
        }
        /// assignement from T
        Base_Type& operator=(T&& lhs)
        {
            *this = std::move(base_t{ std::move(lhs) });
            return *this;
        }

    private:
        void check_invariant() { constraint_.check_invariant(value_); }

        template <typename Op>
        value_t inplace_op(value_t lhs, value_t rhs, Op op)
        {
            return constraint_.template inplace_op<base_t>(lhs, rhs, op);
        }

        value_t value_;
        Constraint_t constraint_;
    };

    /**
     * @brief Constrained type (designed to be used)
     *
     * Type to used to create constrained type.
     * Inherit from Base_Type to provide a better interface for
     * creating a constrained type that can perform operations.
     *
     * Use template composition to make it able to perform some operation,
     * like arithmetic operation ...
     *
     * @tparam T type to be constrained
     * @tparam Constraint_t constraint to add to the type
     * @tparam operators operator available for the (constrained) type
     *
     * example of type creation
     * @code{.cpp}
using angle = Type<int,
    Strict_Range<int, invariant_checker, -1, 361>,
    arithmetic_operator,
    bitwise_operator>;
     * @endcode
     */
    template <typename T,
        typename Constraint_t,
        template <typename, typename> class... operators>
        REQUIRES(Is_Constraint_Type<Constraint_t>())
    struct Type : Base_Type<T, Constraint_t>,
                  operators<Base_Type<T, Constraint_t>, T>... {

        using base = Base_Type<T, Constraint_t>;

        /// Constructor with value
        Type(T val)
            : base{ val }
        {
        }

        /// Default constructor
        template <typename S = void>
        REQUIRES(Constraint_t::has_default&& std::is_default_constructible<T>::value)
        Type()
            : base{}
        {
        }
    };
}
}
