#pragma once

#include <iostream>
#include <string>
#include <type_traits>

/**
 * @file constrain.hpp
 * @brief Provide a way to define constraint
 * @author Vincent
 * @version 0.1
 * @date 2016-07-23
 */

#define error(cond, func) func(std::string{ __func__ }, std::string{ #cond })

#ifdef HASCONCEPT
#define REQUIRES(concept) requires concept
#else
#define REQUIRES(concept) // use enable_if
#endif                    /* ifndef  */

namespace nfs {
namespace constrained_types {

    struct ConstraintTag{}; // TODO : find better solution

    /**
     * @struct Constraint
     * @brief Base class to be overrided. Represent a constraint on a type
     *
     * @tparam T              type on which constraint is applied
     * @tparam error_function error handling function used when constraint are
     * violated
     * @warning This class define the function inplace_op, constraints class need
     * to derive from Constraint to
     * inherit inplace_op (but do not need to re-define it)
     */
    template <typename T, typename error_function>
    struct Constraint : ConstraintTag {

        /**
         * @static
         * @brief True if the constraint allow a default for the constrained type
         * @fixme find a better solution
         */
        static constexpr bool has_default = false;

        /**
         * @fn check_invariant(T&) const
         * @brief check invariant
         *
         * Call the error function in case of constraint violation
         *
         * @param value value on which you need to chech the constraint
         * @warning This function need to be overrided. This function do nothing
         */
        void check_invariant(T&) const {}

        /**
         * @brief Perform the operation while ensuring constraint
         *
         * @tparam numeric_t  type of the result of the operation
         * @tparam Op         operation to be performed
         * @param lhs  left hand side of the operation
         * @param rhs  right hand side of the operation
         * @param op   operation to be performed
         *
         * @return result of op(lhs, rhs) if it does not violate the constraint
         */
        template <typename numeric_t, typename Op>
        typename numeric_t::value_t inplace_op(typename numeric_t::value_t lhs,
            typename numeric_t::value_t rhs,
            Op op) const
        {
            return static_cast<typename numeric_t::value_t>(
                numeric_t{ op(lhs, rhs) });
        }

    protected:
        error_function func;
    };

    /// @todo move those classes elsewhere
    template <typename T,
        typename error_function,
        T lower_bound,
        T upper_bound>
    struct Strict_Range : Constraint<T, error_function> {

        static constexpr T default_value = lower_bound + T{ 1 };
        static constexpr bool has_default = true;

        void check_invariant(T& value) const
        {
            auto fun = Constraint<T, error_function>::func;
            if (lower_bound >= value)
                error(lower_bound < value, fun);
            if (value >= upper_bound)
                error(value < upper_bound, fun);
        }
    };

    template <typename T, typename error_function>
    struct Not_Null : Constraint<T, error_function> {

        static constexpr bool has_default = false;

        void check_invariant(T& value) const
        {
            auto fun = Constraint<T, error_function>::func;
            if (!value)
                error(value != 0, fun);
        }
    };

    template <typename T, typename error_function, int mod>
    struct Modulo : Constraint<T, error_function> {
        static constexpr bool has_default = true;
        static constexpr T default_value = 0;

        void check_invariant(T& value) const { value = value % mod; }
    };

    // TODO : faire en sorte que les __FUNCTION__ ... pointent sur les bonnes
    // fonctions
    struct invariant_checker {
        void operator()(std::string func, std::string cond)
        {
            std::cerr << func << " : " << cond << " failed" << std::endl;
            std::abort();
        }
    };

    struct No_Op {
        void operator()(std::string, std::string) {}
    };
#ifdef HASCONCEPT
    template <typename T>
    constexpr bool Is_Constraint_Type()
    {
        return std::is_base_of<ConstraintTag, T>::value;
    }
#endif
}
}
