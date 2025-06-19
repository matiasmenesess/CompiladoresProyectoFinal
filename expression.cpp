//
// Created by zamirlm on 6/5/25.
//

#include "expression.h"
#include <iostream>
#include <utility>
using namespace  std;

Include::Include(string header, bool system): header_name(move(header)), is_system_header(system) {}
Include::~Include() {}

IncludeList::
