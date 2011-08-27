#include <stdio.h>
#include <string.h>
#include "head-unit.h"

#define MAX_TEST_NAME_LEN 50
#define MAX_TESTS 100
#define MAX_SUITES 100

struct test_t {
    void (*test)(void) ;
    char name[MAX_TEST_NAME_LEN] ;
} ;

struct suite_t {
    char name[MAX_TEST_NAME_LEN] ;
    struct test_t tests[MAX_TESTS] ;
    int num_tests ;
    int failed_tests[MAX_TESTS] ;
    int num_failed ;
} ;

static struct suite_t suites[MAX_SUITES] ; 
static int num_suites = 0 ;
static int assert_fail = 0 ;
static int total_passed = 0 ;
static int total_failed = 0 ;

static void run_suite(struct suite_t *suite) ;

void add_suite(char *name)
{
    struct suite_t new_suite ;
    new_suite.num_tests = 0 ;
    new_suite.num_failed = 0 ;
    strcpy(new_suite.name, name) ;
    suites[num_suites++] = new_suite ;
}

void add_test(void (*test)(void), char *name)
{
    struct test_t new_test ;
    struct suite_t *current_suite = &suites[num_suites-1] ;

    new_test.test = test ;
    strcpy(new_test.name, name) ;
    current_suite->tests[current_suite->num_tests++] = new_test ;
}

void run_tests()
{
    int i, j ;
    struct suite_t *suite ;

    printf("\n---------\n") ;
    printf("HEAD-UNIT\n") ;
    printf("---------\n\n") ;

    for (i = 0 ; i < num_suites ; i++)
        run_suite(&suites[i]) ;
    
    printf("\n%d tests passed\n", total_passed) ;
    if (total_failed) {
        printf("%d tests failed\n", total_failed) ;
        printf("\n") ;
        
        printf("FAILURE SUMMARY\n") ;
        printf("---------------\n") ;

        for (i = 0 ; i < num_suites ; i++) {
            if (suites[i].num_failed) {
                suite = &suites[i] ;
                printf("-> %s (%d/%d)\n", suite->name, suite->num_failed, suite->num_tests) ;
                for (j = 0 ; j < suite->num_failed ; j++) {
                    printf("   --> %s... FAILED\n", suite->tests[suite->failed_tests[j]].name) ;
                    if (j == suite->num_failed -1 )
                        printf("\n") ;
                }
            }
        }
    }
    else {
        printf("SUCCESS\n\n") ;
    }
}

static void run_suite(struct suite_t *suite)
{
    int i, j ;
    printf("-> Running tests for suite '%s'...\n", suite->name) ;

    for (j = 0 ; j < suite->num_tests ; j++) {
        assert_fail = 0 ;
        printf("   --> %s... ", suite->tests[j].name) ;
        (*suite->tests[j].test)() ;
        if (assert_fail) {
            total_failed++ ;
            printf("FAILED\n") ;
            suite->failed_tests[suite->num_failed++] = j ;
        }
        else {
            total_passed++ ;
            printf("SUCCESS\n") ;
        }
    }
    if (i != num_suites-1)
        printf("\n") ;
}




void assert_true(int expression)
{
    if (!expression) 
        assert_fail = 1 ;
}


