//#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "Auxiliary.h"
#include "Calculator.h"


int main(int argc, char* argv[]) 
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	setlocale(LC_ALL, "Russian");
	system("cls");
	
	char str[MAX_STRING];	
	
	try
	{
		do {
			std::cout << "Enter expression. Enter a blank line to stop: ";
		
			std::cin.getline(str, MAX_STRING);
			remove_quotes(str, '\"');

			Calculator calculator;
			double ans = calculator.calc(str);

			if (whole_number(ans))
				std::cout << ans << ".0" << std::endl;
			else
				std::cout << ans << std::endl;
		} while (*str);
	}
	catch (std::exception& e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	};

	return EXIT_SUCCESS;
}

