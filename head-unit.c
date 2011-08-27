#include <stdio.h>
#include <string.h>
#include "head-unit.h"

static char suite_name[MAX_TEST_NAME_LEN] ;
static int assert_fail = 0 ;
static int total_passed = 0 ;
static int total_failed = 0 ;
static int num_tests = 0 ;
static Test tests[MAX_TESTS] ;

void add_suite(char *name)
{
    strcpy(suite_name, name) ;
}

void add_test(void (*test)(void), char *name)
{
    Test new_test ;
    new_test.test = test ;
    strcpy(new_test.name, name) ;

    tests[num_tests++] = new_test ;
}

void run_tests()
{
    int i ;

    printf("HEAD-UNIT\n") ;
    printf("Running tests for suite '%s'...\n", suite_name) ;

    for (i = 0 ; i < num_tests ; i++) {
        assert_fail = 0 ;
        printf("-> %s... ", tests[i].name) ;
        (*tests[i].test)() ;
        if (assert_fail) {
            total_failed++ ;
            printf("FAILED\n") ;
        }
        else {
            total_passed++ ;
            printf("SUCCESS\n") ;
        }
    }
    
    printf("\nPassed tests: %d\n", total_passed) ;
    if (total_failed) {
        printf("Failed tests: %d\n", total_failed) ;
        printf("FAILURE\n\n") ;
    }
    else {
        printf("SUCCESS\n\n") ;
    }
}

void assert_true(int expression)
{
    if (!expression) 
        assert_fail = 1 ;
}


