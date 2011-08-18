#include <stdio.h>
#include <string.h>
#include "head-unit.h"

static int last_result = 0 ;
static int passed = 0 ;
static int failed = 0 ;
static int num_tests = 0 ;
static Test tests[MAX_TESTS] ;

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
    printf("Running tests...\n") ;

    for (i = 0 ; i < num_tests ; i++) {
        printf("-> %s... ", tests[i].name) ;
        (*tests[i].test)() ;
        if (last_result)
            passed++ ;
        else
            failed++ ;
    }
    
    printf("\nPassed tests: %d\n", passed) ;
    if (failed) {
        printf("Failed tests: %d\n", failed) ;
        printf("FAILURE\n") ;
    }
    else {
        printf("SUCCESS\n") ;
    }
}

void assert_true(int expression)
{
    if (expression) {
        printf("SUCCESS\n") ;
        last_result = 1 ;
    }
    else { 
        printf("FAILURE\n") ;
        last_result = 0 ;
    }
}


