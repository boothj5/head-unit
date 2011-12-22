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

void assert_int_equals(int expected, int actual)
{
    int fail = 0 ;
    stringstream msg ;

    fail = expected != actual ;
    if (fail) {
        assert_fail = 1 ;
        msg << "expected = " << expected << ", actual = " << actual ;
        fail_message = msg.str() ;
    }
}

void assert_string_equals(string expected, string actual)
{
    int fail = 0 ;
    stringstream msg ;

    fail = expected != actual ;
    if (fail) {
        assert_fail = 1 ;
        msg << "expected = " << expected << ", actual = " << actual ;
        fail_message = msg.str() ;
    }
}

