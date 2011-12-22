#ifndef HEAD_UNIT_H
#define HEAD_UNIT_H

#define MAX_MSG_LEN 200

extern int assert_fail ;
extern char fail_message[MAX_MSG_LEN] ;

void add_suite(char *name) ;
void add_test(void (*test)(void), char *name) ;
void run_tests(void) ;

// asserts
void assert_true(int expression) ;
void assert_false(int expression) ;
void assert_int_equals(int expected, int actual) ;
void assert_string_equals(char *expected, char *actual) ;

#endif
