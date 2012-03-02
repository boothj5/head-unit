/* 
 * head-unit.h
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

#ifndef HEAD_UNIT_H
#define HEAD_UNIT_H

#ifdef __cplusplus
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#endif

#define MAX_MSG_LEN 200

// Core C API  ----------------------------------------------------------------

// Client API for setting up tests
#define TEST_MODULE(name) add_module(name)
#define SETUP(name)       add_setup(name)
#define BEFORETEST(name)  add_beforetest(name)
#define AFTERTEST(name)   add_aftertest(name)
#define TEARDOWN(name)    add_teardown(name)
#define TEST(name)        add_test(name, #name) ;

#ifdef __cplusplus
extern "C" {
#endif

extern int assert_fail;
extern char fail_message[MAX_MSG_LEN];

// test setup functions, clients should use the macros above
void add_module(char *name);
void add_setup(void (*setup)(void));
void add_beforetest(void (*beforetest)(void));
void add_aftertest(void (*aftertest)(void));
void add_teardown(void (*teardown)(void));
void add_test(void (*test)(void), char *name);
void run_suite(void);

// C asserts available to clients
void assert_true(int expression);
void assert_false(int expression);
void assert_int_equals(int expected, int actual);
void assert_string_equals(char *expected, char *actual);
void assert_is_null(void *ptr);

#ifdef __cplusplus
}
#endif

// C++ API  -------------------------------------------------------------------

// C++ bindings taking std::string instead of const char *
#ifdef __cplusplus
void add_module(std::string name);
void add_test(void (*test)(void), std::string name);

// C++ asserts
template <class T>
void assert_equals(T expected, T actual)
{
    int fail = 0;
    std::stringstream msg;

    fail = expected != actual;
    if (fail) {
        assert_fail = 1;
        msg << "expected = " << expected << ", actual = " << actual;
        strcpy(fail_message, msg.str().c_str());
    }
}
#endif

#endif
