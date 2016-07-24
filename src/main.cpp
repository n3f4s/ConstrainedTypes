#include <iostream>
#include <regex>
#include <string>

#include "base.hpp"
#include "constrain.hpp"

// TODO : better error handling ( good use of __FUNCTION__ macro ...)
// TODO : perfect forwarding

/** @mainpage Summary
 * The purpose of this library is to provide a way to create arbitrary
 * type by adding constraint over existing type
 *
 * @todo better doc
 *
 * @code{.cpp}
using namespace nfs::constrained_types;
using namespace nfs::binary_operator;

// User defined constraint : ensure that a string contains "Hello"
struct Regex_Constraint : Constraint<std::string, invariant_checker> {
    static constexpr bool has_default = false;
    void check_invariant(std::string& value) const
    {
        std::regex reg(".*Hello.*");
        auto fun = Constraint<std::string, invariant_checker>::func;
        if (!std::regex_match(value, reg))
            error(std::regex_match(value, reg), fun);
    }
};

// Creation of angle type by adding a constraint over an int
// using new_type = Type<base_type, constraint, operations...>
using angle = Type<int,
    Strict_Range<int, invariant_checker, -1, 361>,
    arithmetic_operator,
    bitwise_operator>;

using test_type = Type<std::string, Regex_Constraint>;

int main()
{
    test_type t{ "Hello World" };
    test_type r{ "Youpi" };
    angle a{ 0 };
    for (unsigned i{ 1 };; ++i) {
        std::cout << "(angle a = " << static_cast<int>(a) << ") + (" << i
                  << ") = " << static_cast<int>(a + i) << std::endl;
    }
    return 0;
}
 * @endcode
 */

using namespace nfs::constrained_types;
using namespace nfs::binary_operator;

struct Regex_Constraint : Constraint<std::string, invariant_checker> {
    static constexpr bool has_default = false;
    void check_invariant(std::string& value) const
    {
        std::regex reg(".*Hello.*");
        auto fun = Constraint<std::string, invariant_checker>::func;
        if (!std::regex_match(value, reg))
            error(std::regex_match(value, reg), fun);
    }
};

using angle = Type<int,
    Strict_Range<int, invariant_checker, -1, 361>,
    arithmetic_operator,
    bitwise_operator>;

using test_type = Type<std::string, Regex_Constraint>;

// TODO : doc && test
int main()
{
    test_type t{ "Hello World" };
    // test_type r{}; // OK - concept generate an error
    angle a{ 0 };
    for (unsigned i{ 1 };; ++i) {
        std::cout << "(angle a = " << static_cast<int>(a) << ") + (" << i
                  << ") = " << static_cast<int>(a + i) << std::endl;
    }
    return 0;
}
