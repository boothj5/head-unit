#include <string.h>
#include <stdio.h>
#include "head-unit.h"

void assert_true(int expression)
{
    int fail = 0 ;

    fail = !expression ; 
    if (fail) {
        assert_fail = 1 ;
        strcpy(fail_message, "expected = true, actual = false") ;
    }
}

void assert_false(int expression)
{
    int fail = 0 ;

    fail = expression ;
    if (fail) {
        assert_fail = 1 ;
        strcpy(fail_message, "expected = false, actual = true") ;
    }
}

void assert_int_equals(int expected, int actual)
{
    int fail = 0 ;
    char msg[MAX_MSG_LEN] ;
    char buf[10] ;

    fail = expected != actual ;
    if (fail) {
        assert_fail = 1 ;
        strcpy(msg, "expected = ") ;
        sprintf(buf, "%d", expected) ;
        strcat(msg, buf) ;
        strcat(msg, ", actual = ") ;
        sprintf(buf, "%d", actual) ;
        strcat(msg, buf) ;
        strcpy(fail_message, msg) ;
    }
}

void assert_string_equals(char *expected, char *actual)
{
    int fail = 0 ;
    char msg[MAX_MSG_LEN] ;

    fail = strcmp(expected, actual) != 0 ;
    if (fail) {
        assert_fail = 1 ;
        strcpy(msg, "expected = ") ;
        strcat(msg, expected) ;
        strcat(msg, ", actual = ") ;
        strcat(msg, actual) ;
        strcpy(fail_message, msg) ;
    }
}
