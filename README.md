HEAD-UNIT
=========

Simple unit testing framework for C/C++ .

Basic steps are:.

* Write the tests
* Register the tests in a test module
* Register the test modules in a testsuite
* Run the testsuite

Building and installing head-unit
---------------------------------

To clean:

    make clean

To build:

    make

To install (currently to ~/lib and ~/include):

    make install

Usage
-----

### Write a test module

some_tests.c:

```c
#include <head-unit.h>

static void setup(void)
{
    ... do some setup for all tests ...
}

static void teardown(void)
{
    ... close resources etc ...
}

static void beforetest(void)
{
    ... code to run before each test ...
}

static void aftertest(void)
{
    ... code to run after each test ...
}

static void test_something(void)
{
    ... some code ...

    assert_true( ... some expression ... );
}

static void test_something_else(void)
{
    ... some code ...

    assert_true( ... some expression ... );
}

void register_some_tests()
{
    TEST_MODULE("some_tests");
    SETUP(setup);
    BEFORETEST(beforetest);
    AFTERTEST(aftertest);
    TEST(test_something);
    TEST(test_something_else);
    TEARDOWN(teardown);
}
```
The use of static is optional but stops tests with similar names in different source files conflicting.

The register function must not be static.

The SETUP, BEFORETEST, AFTERTEST and TEARDOWN functions and equivalent macros are optional.

### Create a header and source file to register and run all modules

testsuite.h:

```c
#ifndef TESTSUITE_H
#define TESTSUITE_H

void register_some_tests(void) ;
void register_some_other_tests(void) ;

#endif
```

testsuite.c:

```c
#include <head-unit.h>
#include <"testsuite.h">

int main(void)
{
    register_some_tests() ;
    register_some_other_tests() ;
    run_tests() ;
    return 0 ;
}
```

### Build and run the tests

C compiler flags:

    -lstdc++ -I ~/include -L ~/lib -l headunit

C++ compiler flags:

    -Wno-write-strings -I ~/include -L ~/lib -l headunit

Example C make targets:

    compile-tests: testsuite.o some_tests.o something.o
        $(CC) -lstdc++ testsuite.o some_tests.o something.o -I ~/include -L ~/lib -o testsuite -l headunit

    test: compile-tests
        ./testsuite

Example C++ make targets:

    compile-tests: testsuite.o some_tests.o something.o
        $(CC) -Wno-write-strings testsuite.o some_tests.o something.o -I ~/include -L ~/lib -o testsuite -l headunit

    test: compile-tests
        ./testsuite

Example output
--------------

    ---------
    HEAD-UNIT
    ---------

    -> Running tests for suite 'test_card'...
       --> testThreeLowerThanTwo... SUCCESS
       --> testFiveLowerThanTwo... SUCCESS
       --> testJackLowerThanSeven... SUCCESS
       --> testTwoSpecial... FAILED
       --> testSevenSpecial... FAILED
       --> testTenSpecial... SUCCESS
       --> testRanksEqual... SUCCESS
       --> testRanksNotEqual... SUCCESS
       --> testAllRanksEqual... SUCCESS
       --> testAllRanksEqual... SUCCESS

    -> Running tests for suite 'test_player'...
       --> testAddToHandAddsCard... FAILED
       --> testAddAllToHandAddsCards... SUCCESS
       --> testAddToFaceUpAddsCard... SUCCESS
       --> testAddToFaceDownAddsCard... SUCCESS
       --> sortHandSortsHand... SUCCESS
       --> swapSwapsCards... SUCCESS
       --> removeFromHandRemovesCard... SUCCESS
       --> hasCardsWhenCardsInHand... SUCCESS
       --> hasCardsWhenCardsInFaceUp... SUCCESS
       --> hasCardsWhenCardsInFaceDown... SUCCESS
       --> notHasCardsWhenNone... SUCCESS

    18 tests passed
    3 tests failed

    FAILURE SUMMARY
    ---------------
    -> test_card (2/10)
       --> testTwoSpecial... FAILED (expected = true, actual = false)
       --> testSevenSpecial... FAILED (expected = true, actual = false)

    -> test_player (1/11)
       --> testAddToHandAddsCard... FAILED (expected = THREE of DIAMONDS, actual = TWO of SPADES)

Asserts
-------

### C/C++

```c
assert_true(int expression)
assert_false(int expression)
assert_int_equals(int expected, int actual)
assert_string_equals(char *expected, char *actual)
```

### C++

```cpp
assert_equals(T expected, T actual)
```

T must override:

```cpp
bool T::operator==(const T& other) const
bool T::operator!=(const T& other) const
```

And overload the output stream << function:

```cpp
ostream& operator<<(ostream& strm, const T& obj)
```
