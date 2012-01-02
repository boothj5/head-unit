#include <sstream>
#include <string>
#include "head-unit-cpp.h"

using namespace std ;

void assert_true(int expression)
{
    int fail = 0 ;

    fail = !expression ; 
    if (fail) {
        assert_fail = 1 ;
        fail_message = "expected = true, actual = false" ;
    }
}

void assert_false(int expression)
{
    int fail = 0 ;

    fail = expression ;
    if (fail) {
        assert_fail = 1 ;
        fail_message = "expected = false, actual = true" ;
    }
}
