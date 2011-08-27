#ifndef HEAD_UNIT_H
#define HEAD_UNIT_H

#define MAX_TEST_NAME_LEN 50
#define MAX_TESTS 100

typedef struct {
    void (*test)(void) ;
    char name[MAX_TEST_NAME_LEN] ;
} Test ;

void add_test(void (*test)(void), char *name) ;
void assert_true(int expression) ;
void run_tests(void) ;

#endif
