#include <iostream>

#include "numeric.hpp"
#include "constrain.hpp"

// TODO : better error handling ( good use of __FUNCTION__ macro ...)

using namespace nfs::constrained_types;

// We create an angle type : it's a int that bounded between 0 and 360
// however, Strict_Range exclude the bound so we use -1 and 361 as range bound
using angle =
    Numeric_Type< int, Strict_Range, invariant_checker, -1, 361 >;
// We create a type that can't be equal to 0 (cf Not_Null)
using not_null = Numeric_Type< int, Not_Null, invariant_checker >;
// We create a type that is bounded between 0 and 4.
// But getting out of bound is not an error, it just takes N % 5.
using mod5 = Numeric_Type< int, Modulo, No_Op, 5 >;

int main()
{
    angle a{10};
    std::cout << "range_type : ";
    std::cin >> a;

    not_null b{10};
    std::cout << "not_null : ";
    std::cin >> b;

    mod5 c{};
    for( auto const& elt : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} ) {
        c = elt;
        std::cout << c << std::endl;
    }
    return 0;
}
