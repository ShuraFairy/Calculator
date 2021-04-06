#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

int __isspace(int c);
size_t __strlen(const char* s);
char* __strchr(const char* s, int c);
int __toupper(int c);
int __isdigit(int c);
double __atof(const char* s);
bool whole_number(double x);
size_t check_exponent(const char* s);
void remove_quotes(char* s, int c);
