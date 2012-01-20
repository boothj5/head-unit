#include <string>
#include "head-unit.h"

using namespace std ;

void add_module(string name)
{
    const char *cname = name.c_str();
    add_module(cname);
}

void add_test(void (*test)(void), string name)
{
    const char *cname = name.c_str();
    add_test(test, cname);
}

