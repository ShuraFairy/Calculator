#include "Auxiliary.h"

int __isspace(int c)
{
	return ((c == ' ') || (c == '\n') || (c == '\t'));
}

size_t __strlen(const char* s)
{
	const char* sc;

	for (sc = s; *sc != '\0'; ++sc)
		; // nothing do it
	return sc - s;
}

char* __strchr(const char* s, int c)
{
	const char* cur;
	for (cur = s; *cur; cur++) {
		if (*cur == c) {
			return ((char*)cur);
		}
	}

	return NULL;
}

int __toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return c - ('a' - 'A');
	else
		return c;
}

int __isdigit(int c)
{
	return ((c >= '0') && (c <= '9'));
}

double __atof(const char* s)
{
	double a = 0.0;
	int e = 0;
	int c;
	while ((c = *s++) != '\0' && __isdigit(c))
	{
		a = a * 10.0 + (c - '0');
	}
	if (c == '.')
	{
		while ((c = *s++) != '\0' && __isdigit(c))
		{
			a = a * 10.0 + (c - '0');
			e = e - 1;
		}
	}
	if (c == 'e' || c == 'E')
	{
		int sign = 1;
		int i = 0;
		c = *s++;
		if (c == '+')
			c = *s++;
		else if (c == '-')
		{
			c = *s++;
			sign = -1;
		}
		while (isdigit(c))
		{
			i = i * 10 + (c - '0');
			c = *s++;
		}
		e += i * sign;
	}
	while (e > 0)
	{
		a *= 10.0;
		e--;
	}
	while (e < 0)
	{
		a *= 0.1;
		e++;
	}
	return a;
}

size_t check_exponent(const char* s)
{
	size_t i = 0;
	size_t size = __strlen(s);
	size_t count = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '^' && i == 0) || (s[i] == '^' && i == size - 1) ||
			((s[i] == '^' && s[i + 1] == '^') && i < size))
			throw std::runtime_error("Syntax Error");

		if (s[i] == '^')
			++count;
		++i;
	};
	return count;
}

bool whole_number(double x)
{
	//return (fabs((int)x - x) < 1e-16);
	return (double((int)x) == x);
}

void remove_quotes(char* s, int c)
{
	size_t i = 0;
	size_t j = 0;
	size_t size = __strlen(s);

	for (i = j = 0; s[i] != '\0'; ++i)
	{
		if (s[i] != c)
			s[j++] = s[i];
		else if (i != 0 && i != size - 1)
			throw std::runtime_error("Syntax Error");
	}
	s[j] = '\0';
}

