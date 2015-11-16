#include <iostream>

#include "numeric.hpp"
#include "constrain.hpp"

// TODO : better error handling ( good use of __FUNCTION__ macro ...)

using namespace nfs::constrained_types;

using angle = Numeric_Type< int, Strict_Range, invariant_checker, -1, 361 >;

int main()
{
    for( int i{0};; ++i ) {
        std::cout << "i=" << i << std::endl;
        angle a{i};
        std::cout << "a=" << static_cast< int >( a ) << std::endl;
    }
    // angle a{360};
    // for( unsigned i{1};; ++i ) {
    // std::cout << "(a = " << static_cast< int >( a ) << ") % (" << i
    //<< ") = " << static_cast< int >( a ) % i << std::endl;
    // std::cout << "(angle a = " << static_cast< int >( a ) << ") % (" << i
    //<< ") = " << static_cast< int >( a % i ) << std::endl;
    //}
    return 0;
}
