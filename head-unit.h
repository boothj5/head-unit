#ifndef HEAD_UNIT_H
#define HEAD_UNIT_H

#define MAX_NAME_LEN 50
#define MAX_TESTS 100
#define END_TEST "END_TEST"

typedef struct {
    void (*test)(void) ;
    char name[MAX_NAME_LEN] ;
} Test ;

void add_test(void (*test)(void), char *name) ;
void assert_true(int expression) ;
void run_tests(void) ;

#endif
