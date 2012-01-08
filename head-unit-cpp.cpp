#include <string>
#include "head-unit.h"

using namespace std ;

void add_suite(string name)
{
    const char *cname = name.c_str();
    add_suit(cname);
}

void add_test(void (*test)(void), string name)
{
    const char *cname = name.c_str();
    add_test(test, cname);
}

