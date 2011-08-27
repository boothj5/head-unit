#ifndef HEAD_UNIT_H
#define HEAD_UNIT_H

void add_suite(char *name) ;
void add_test(void (*test)(void), char *name) ;
void assert_true(int expression) ;
void run_tests(void) ;

#endif
