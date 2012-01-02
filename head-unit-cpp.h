#ifndef HEAD_UNIT_CPP_H
#define HEAD_UNIT_CPP_H

#include <string>
#include <sstream>

using namespace std ;

extern int assert_fail ;
extern string fail_message ;

void add_suite(string name) ;
void add_test(void (*test)(void), string name) ;
void run_tests(void) ;

// asserts
void assert_true(int expression) ;
void assert_false(int expression) ;

template <class T>
void assert_equals(T expected, T actual)
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


#endif
