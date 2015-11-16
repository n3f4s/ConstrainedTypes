#include <iostream>

#include "constrain.hpp"
#include "base.hpp"

// TODO : better error handling ( good use of __FUNCTION__ macro ...)

using namespace nfs::constrained_types;
using namespace nfs::binary_operator;

using angle = Type< int,
                    Base_Type< int, Strict_Range, invariant_checker, -1, 361 >,
                    arithmetic_operator,
                    bitwise_operator >;

int main()
{
    angle a{0};
    for( unsigned i{1};; ++i ) {
        std::cout << "(angle a = " << static_cast< int >( a ) << ") + (" << i
                  << ") = " << static_cast< int >( a + i ) << std::endl;
    }
    return 0;
}
