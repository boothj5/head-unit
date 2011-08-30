#ifndef HEAD_UNIT_H
#define HEAD_UNIT_H

void add_suite(char *name) ;
void add_test(void (*test)(void), char *name) ;
void run_tests(void) ;
void assert_true(int expression) ;
void assert_false(int expression) ;
void assert_int_equals(int expected, int actual) ;

#endif
