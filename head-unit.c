/* 
 * head-unit.c
 *
 * Copyright (C) 2011, 2012 James Booth <boothj5@gmail.com>
 * 
 * This file is part of head-unit.
 *
 * head-unit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * head-unit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with head-unit.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <string.h>
#include "head-unit.h"

#define MAX_TEST_NAME_LEN 100
#define MAX_TESTS 100
#define MAX_SUITES 100

// Test structures ------------------------------------------------------------

// a single test function, with name
struct test_t {
    void (*test)(void);
    char name[MAX_TEST_NAME_LEN];
};

// pointer to failed test, with message
struct failed_test_t {
    int index;
    char message[MAX_MSG_LEN];
};

// represents a single source file containing tests
struct module_t {
    char name[MAX_TEST_NAME_LEN];
    void (*setup)(void);
    void (*teardown)(void);
    void (*beforetest)(void);
    void (*aftertest)(void);
    struct test_t tests[MAX_TESTS];
    struct failed_test_t failed_tests[MAX_TESTS];
    int num_tests;
    int num_failed;
};

// Global test data -----------------------------------------------------------

static struct module_t modules[MAX_SUITES]; 
static int num_modules = 0;
static int total_passed = 0;
static int total_failed = 0;

int assert_fail = 0;
char fail_message[MAX_MSG_LEN];

// Module setup ---------------------------------------------------------------

void add_module(char *name)
{
    struct module_t new_module;
    new_module.setup = NULL;
    new_module.teardown = NULL;
    new_module.beforetest = NULL;
    new_module.aftertest = NULL;
    new_module.num_tests = 0;
    new_module.num_failed = 0;
    strcpy(new_module.name, name);
    modules[num_modules++] = new_module;
}

void add_setup(void (*setup)(void))
{
    struct module_t *current_module = &modules[num_modules-1];
    current_module->setup = setup;
}

void add_teardown(void (*teardown)(void))
{
    struct module_t *current_module = &modules[num_modules-1];
    current_module->teardown = teardown;
}

void add_beforetest(void (*beforetest)(void))
{
    struct module_t *current_module = &modules[num_modules-1];
    current_module->beforetest = beforetest;
}

void add_aftertest(void (*aftertest)(void))
{
    struct module_t *current_module = &modules[num_modules-1];
    current_module->aftertest = aftertest;
}

void add_test(void (*test)(void), char *name)
{
    struct test_t new_test;
    struct module_t *current_module = &modules[num_modules-1];

    new_test.test = test;
    strcpy(new_test.name, name);
    current_module->tests[current_module->num_tests++] = new_test;
}

// Used by testuite runner ----------------------------------------------------

static void run_module(struct module_t *module)
{
    int i;
    printf("-> Running tests for suite '%s'...\n", module->name);

    if (!(module->setup == NULL))
        (*module->setup)();

    for (i = 0; i < module->num_tests; i++){
        assert_fail = 0;
        printf("   --> %s... ", module->tests[i].name);
        
        if (!(module->beforetest == NULL))
            (*module->beforetest)();

        (*module->tests[i].test)();

        if (!(module->aftertest == NULL))
            (*module->aftertest)();

        if (assert_fail) {
            total_failed++;
            printf("FAILED\n");
            struct failed_test_t failed;
            failed.index = i;
            strcpy(failed.message, fail_message);
            module->failed_tests[module->num_failed++] = failed;
        }
        else {
            total_passed++;
            printf("SUCCESS\n");
        }
    }
    
    if (!(module->teardown == NULL))
        (*module->teardown)();
}

static void failure_summary(struct module_t *module)
{
    int i;
    printf("-> %s (%d/%d)\n", module->name, module->num_failed, 
        module->num_tests);
    
    for (i = 0 ; i < module->num_failed ; i++) {
        int test_num = module->failed_tests[i].index;
        char *msg = module->failed_tests[i].message;
        printf("   --> %s... FAILED (%s)\n", 
            module->tests[test_num].name, msg);
        if (i == module->num_failed -1)
            printf("\n");
    }
}

// Testsuite runner -----------------------------------------------------------

void run_suite()
{
    int i;
    
    printf("\n---------\n");
    printf("HEAD-UNIT\n");
    printf("---------\n\n");

    for (i = 0; i < num_modules; i++) {
        run_module(&modules[i]);
        if (i != num_modules-1)
            printf("\n");
    }
    
    printf("\n%d tests passed\n", total_passed);

    if (total_failed) {
        printf("%d tests failed\n", total_failed);
        printf("\n");
        
        printf("FAILURE SUMMARY\n");
        printf("---------------\n");

        for (i = 0; i < num_modules; i++) 
            if (modules[i].num_failed)
                failure_summary(&modules[i]);
    }
    else {
        printf("SUCCESS\n\n");
    }
}
