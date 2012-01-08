#ifndef HEAD_UNIT_H
#define HEAD_UNIT_H

#ifdef __cplusplus
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
using namespace std;
#endif

#define MAX_MSG_LEN 200

#define TEST_MODULE(name) add_suite(name)
#define TEST(name)        add_test(name, #name) ;

#ifdef __cplusplus
extern "C" {
#endif

extern int assert_fail;
extern char fail_message[MAX_MSG_LEN];

void add_suite(char *name);
void add_test(void (*test)(void), char *name);
void run_tests(void);

// asserts
void assert_true(int expression);
void assert_false(int expression);
void assert_int_equals(int expected, int actual);
void assert_string_equals(char *expected, char *actual);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
void add_suit(string name);
void add_test(void (*test)(void), string name);

template <class T>
void assert_equals(T expected, T actual)
{
    int fail = 0;
    stringstream msg;

    fail = expected != actual;
    if (fail) {
        assert_fail = 1;
        msg << "expected = " << expected << ", actual = " << actual;
        strcpy(fail_message, msg.str().c_str());
    }
}
#endif

#endif
