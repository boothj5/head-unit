#include <iostream>
#include <sstream>
#include <string>
#include "head-unit-cpp.h"

#define MAX_TESTS 100
#define MAX_SUITES 100

using namespace std ;

struct test_t {
    void (*test)(void) ;
    string name ;
} ;

struct failed_test_t {
    int index ;
    string message ;
} ;

struct suite_t {
    string name ;
    struct test_t tests[MAX_TESTS] ;
    int num_tests ;
    struct failed_test_t failed_tests[MAX_TESTS] ;
    int num_failed ;
} ;

static struct suite_t suites[MAX_SUITES] ; 
static int num_suites = 0 ;
static int assert_fail = 0 ;
static string fail_message ;
static int total_passed = 0 ;
static int total_failed = 0 ;

static void run_suite(struct suite_t *suite) ;
static void failure_summary(struct suite_t *suite) ;

void add_suite(string name)
{
    struct suite_t new_suite ;
    new_suite.num_tests = 0 ;
    new_suite.num_failed = 0 ;
    new_suite.name = name ;
    suites[num_suites++] = new_suite ;
}

void add_test(void (*test)(void), string name)
{
    struct test_t new_test ;
    struct suite_t *current_suite = &suites[num_suites-1] ;

    new_test.test = test ;
    new_test.name = name ;
    current_suite->tests[current_suite->num_tests++] = new_test ;
}

void run_tests()
{
    int i ;
    
    cout << endl << "---------" << endl ;
    cout << "HEAD-UNIT" << endl ;
    cout << "---------" << endl << endl ;

    for (i = 0 ; i < num_suites ; i++) {
        run_suite(&suites[i]) ;
        if (i != num_suites-1)
            cout << endl ;
    }
    
    cout << endl << total_passed << " tests passed" << endl ;

    if (total_failed) {
        cout << total_failed << " tests failed" << endl << endl ;
        
        cout << "FAILURE SUMMARY" << endl ;
        cout << "---------------" << endl ;

        for (i = 0 ; i < num_suites ; i++) 
            if (suites[i].num_failed)
                failure_summary(&suites[i]) ;
    }
    else {
        cout << "SUCCESS" << endl << endl ;
    }
}

static void failure_summary(struct suite_t *suite)
{
    int i ;
    cout << "-> " << suite->name << " (" ;
    cout << suite->num_failed << "/" ;
    cout << suite->num_tests << ")" << endl ; 
    
    for (i = 0 ; i < suite->num_failed ; i++) {
        int test_num = suite->failed_tests[i].index ;
        string msg = suite->failed_tests[i].message ;
        cout << "   --> " << suite->tests[test_num].name ;
        cout << "... FAILED (" << msg << ")" << endl ;
        if (i == suite->num_failed -1 )
            cout << endl ;
    }
}

static void run_suite(struct suite_t *suite)
{
    int i ;
    cout << "-> Running tests for suite '" << suite->name << "'..." << endl ;

    for (i = 0 ; i < suite->num_tests ; i++) {
        assert_fail = 0 ;
        cout << "   --> " << suite->tests[i].name << "... " ;
        (*suite->tests[i].test)() ;
        if (assert_fail) {
            total_failed++ ;
            cout << "FAILED" << endl ;
            struct failed_test_t failed ;
            failed.index = i ;
            failed.message = fail_message ;
            suite->failed_tests[suite->num_failed++] = failed ;
        }
        else {
            total_passed++ ;
            cout << "SUCCESS" << endl ;
        }
    }
}

void assert_true(int expression)
{
    int fail = 0 ;

    fail = !expression ; 
    if (fail) {
        assert_fail = 1 ;
        fail_message = "expected = true, actual = false" ;
    }
}

void assert_false(int expression)
{
    int fail = 0 ;

    fail = expression ;
    if (fail) {
        assert_fail = 1 ;
        fail_message = "expected = false, actual = true" ;
    }
}

void assert_int_equals(int expected, int actual)
{
    int fail = 0 ;
    stringstream msg ;

    fail = expected != actual ;
    if (fail) {
        assert_fail = 1 ;
        msg << "expected = " << expected << ", actual = " << actual ;
        fail_message = msg.str() ;
    }
}

void assert_string_equals(string expected, string actual)
{
    int fail = 0 ;
    stringstream msg ;

    fail = expected != actual ;
    if (fail) {
        assert_fail = 1 ;
        msg << "expected = " << expected << ", actual = " << actual ;
        fail_message = msg.str() ;
    }
}

