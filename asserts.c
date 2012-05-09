/* 
 * asserts.c
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

#include <string.h>
#include <stdio.h>
#include "head-unit.h"

void assert_true(const int expression)
{
    int fail = 0 ;

    fail = !expression ; 
    if (fail) {
        assert_fail = 1 ;
        strcpy(fail_message, "expected = true, actual = false") ;
    }
}

void assert_false(const int expression)
{
    int fail = 0 ;

    fail = expression ;
    if (fail) {
        assert_fail = 1 ;
        strcpy(fail_message, "expected = false, actual = true") ;
    }
}

void assert_int_equals(const int expected, const int actual)
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

void assert_string_equals(const char * const expected, const char * const actual)
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

void assert_is_null(const void * const ptr)
{
    int fail = 0;
    
    fail = (ptr != NULL);
    if (fail) {
        assert_fail = 1;
        strcpy(fail_message, "Expected NULL, but pointer has value");
    }   
}
