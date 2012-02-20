/* 
 * head-unit-cpp.cpp
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

