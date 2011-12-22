#ifndef HEAD_UNIT_CPP_H
#define HEAD_UNIT_CPP_H

#include <string>

using namespace std ;

extern int assert_fail ;
extern string fail_message ;

void add_suite(string name) ;
void add_test(void (*test)(void), string name) ;
void run_tests(void) ;

// asserts
void assert_true(int expression) ;
void assert_false(int expression) ;
void assert_int_equals(int expected, int actual) ;
void assert_string_equals(string expected, string actual) ;

#endif
