#include "Auxiliary.h"
#include "Calculator.h"

Calculator::~Calculator()
{
	//std::cout << "Destructor" << std::endl;
	expr_ptr = store_ptr;
	free(expr_ptr);
}

double Calculator::calc(const char* str)
{
	double result = 0.0;

	if (check_exponent(str) < 2)
	{
		size_t size = __strlen(str);
		expr_ptr = (char*)malloc(size + 1);

		if (expr_ptr == nullptr)
			throw std::runtime_error("Allocation error");

		size_t i = 0;
		for (i = 0; i < size; ++i)
			expr_ptr[i] = str[i];
		expr_ptr[i] = '\0';
	}
	else
		insert_parenthesises(str);

	store_ptr = expr_ptr;

	get_token();
	if (!*token)
		throw std::runtime_error("No Expression Present");	// no expression present

	evaluate_expr2(result);

	if (*token) // last token must be null
		throw std::runtime_error("Syntax Error");

	return result;
}

void Calculator::evaluate_expr2(double& result)
{
	char op;
	double temp;
	evaluate_expr3(result);
	while ((op = *token) == '+' || op == '-')
	{
		get_token();
		evaluate_expr3(temp);
		switch (op)
		{
		case '-':
			result = result - temp;
			break;
		case '+':
			result = result + temp;
			break;
		}
	}
}

void Calculator::evaluate_expr3(double& result)
{
	char op;
	double temp;
	evaluate_expr4(result);
	while ((op = *token) == '*' || op == '/')
	{
		get_token();
		evaluate_expr4(temp);
		switch (op)
		{
		case '*':
			result = result * temp;
			break;
		case '/':
			result = result / temp;
			break;
		}
	}
}

void Calculator::evaluate_expr4(double& result)
{
	double temp;
	evaluate_expr5(result);
	while (*token == '^')
	{
		get_token();
		evaluate_expr5(temp);
		result = pow(result, temp);
	}
}

void Calculator::evaluate_expr5(double& result)
{
	char op;
	op = 0;
	if ((token_type == static_cast<char>(types::DELIMITER)) && *token == '+' || *token == '-')
	{
		op = *token;
		get_token();
	}
	evaluate_expr6(result);
	if (op == '-')
		result = -result;
}

void Calculator::evaluate_expr6(double& result)
{
	if ((*token == '('))
	{
		get_token();
		evaluate_expr2(result);

		if (*token != ')')
			throw std::runtime_error("Unbalanced Parentheses");

		get_token();
	}
	else
	{
		switch (token_type)
		{
			case static_cast<char>(types::NUMBER) :
				result = __atof(token);
				get_token();
				return;
			default:
				throw std::runtime_error("Syntax Error");
		}
	}
}

void Calculator::get_token()
{
	char* temp;
	token_type = 0;
	temp = token;
	*temp = '\0';
	if (!*expr_ptr)  // end of expression
		return;
	while (__isspace(*expr_ptr))  // skip over white space
		++expr_ptr;
	if (__strchr("+-*/%^=()", *expr_ptr))
	{
		token_type = static_cast<char>(types::DELIMITER);
		*temp++ = *expr_ptr++;  //  to next char
	}
	else if (__isdigit(*expr_ptr) || *expr_ptr == '.')
	{
		while (!__strchr(" +-/*%^=()\t\r", *expr_ptr) && (*expr_ptr))
			*temp++ = __toupper(*expr_ptr++);
		token_type = static_cast<char>(types::NUMBER);
	}
	*temp = '\0';
}

void Calculator::insert_parenthesises(const char* s)
{
	size_t count = check_exponent(s);
	size_t size = __strlen(s);
	expr_ptr = (char*)malloc(size + 2 * count + 1);

	if (expr_ptr == nullptr)
		throw std::runtime_error("Allocation error");

	size_t curr_count = 0;
	size_t i = 0;
	size_t j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '^' && curr_count < count)			
		{
			expr_ptr[j] = s[i];
			++i;
			++j;
		}

		if (s[i] == '^' && (curr_count >= 0 && curr_count < count))
		{
			expr_ptr[j] = s[i];
			++curr_count;
			++j;
			expr_ptr[j] = '(';
			++i;
			++j;
		}

		if (__strchr("+-/*%=()", s[i]) && (curr_count >= count && curr_count < 2 * count))
		{
			expr_ptr[j] = ')';
			++j;
			expr_ptr[j] = s[i];
			++i;
			++j;
			++curr_count;
		}

		if (__strchr(" \t\r", s[i]) && (curr_count >= count && curr_count < 2 * count))
		{
			expr_ptr[j] = s[i];
			++i;
			++j;
		}

		if (!__strchr(" +-/*%=()\t\r", s[i]) && curr_count >= count)
		{
			expr_ptr[j] = s[i];
			++i;
			++j;
		}

	}
	while (curr_count < 2 * count)
	{
		expr_ptr[j] = ')';
		++j;
		++curr_count;
	}
	expr_ptr[j] = '\0';
	//std::cout << expr_ptr << std::endl;
}

