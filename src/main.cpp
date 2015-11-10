#include <iostream>

#include "numeric.hpp"
#include "constrain.hpp"

using angle =
    Numeric_Type< int, Strict_Range< int, -1, 361, invariant_checker > >;
using not_null = Numeric_Type< int, Not_Null< int, invariant_checker > >;
// TODO : tester la contrainte Modulo

// TODO : faire les constructeurs par défaut en fonction de si on peut le faire
//          i.e. : si les contraintes le permettent
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
    return 0;
}
