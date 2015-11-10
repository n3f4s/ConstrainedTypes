#include <iostream>

#include "numeric.hpp"
#include "constrain.hpp"

using angle =
    Numeric_Type< int, Strict_Range< int, -1, 361, invariant_checker > >;
using not_null = Numeric_Type< int, Not_Null< int, invariant_checker > >;
using mod5     = Numeric_Type< int, Modulo< int, No_Op, 5 > >;

// TODO : faire une meilleur gestion des erreurs : passer les bonnes macro
// __FILE__ ....

int main()
{
    angle a{10};
    // angle c{};
    // std::cout << c << std::endl;
    std::cout << "range_type : ";
    std::cin >> a;
    std::cout << a << std::endl;

    std::cout << std::endl;

    not_null b{10};
    std::cout << "not_null : ";
    std::cin >> b;
    std::cout << b << std::endl;

    mod5 c{};
    for( auto const& elt : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9} ) {
        c = elt;
        std::cout << c << std::endl;
    }
    return 0;
}
