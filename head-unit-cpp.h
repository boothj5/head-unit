#ifndef HEAD_UNIT_H
#define HEAD_UNIT_H

#include <string>

using namespace std ;

void add_suite(string name) ;
void add_test(void (*test)(void), string name) ;
void run_tests(void) ;
void assert_true(int expression) ;
void assert_false(int expression) ;
void assert_int_equals(int expected, int actual) ;
void assert_string_equals(string expected, string actual) ;

#endif
