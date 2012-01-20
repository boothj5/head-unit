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
#define TEST_MODULE(name) add_suite(name)
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
void add_suite(char *name);
void add_setup(void (*setup)(void));
void add_beforetest(void (*beforetest)(void));
void add_aftertest(void (*aftertest)(void));
void add_teardown(void (*teardown)(void));
void add_test(void (*test)(void), char *name);
void run_tests(void);

// C asserts available to clients
void assert_true(int expression);
void assert_false(int expression);
void assert_int_equals(int expected, int actual);
void assert_string_equals(char *expected, char *actual);

#ifdef __cplusplus
}
#endif

// C++ API  -------------------------------------------------------------------

// C++ bindings taking std::string instead of const char *
#ifdef __cplusplus
void add_suit(std::string name);
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
