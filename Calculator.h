#pragma once

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

constexpr size_t MAX_STRING = 1024;
constexpr size_t NUMVARS = 32;
constexpr size_t LENGTH_TOKEN = 256;

enum class types { UNKNOWN, DELIMITER, NUMBER };

class Calculator
{
	char* expr_ptr = nullptr;
	char token[LENGTH_TOKEN] = { 0 };	// current token
	char token_type = { 0 };
	char* store_ptr = nullptr;
	double variables[NUMVARS] = { 0 };	// variables values
	void insert_parenthesises(const char* s);
	void evaluate_expr2(double& result);
	void evaluate_expr3(double& result);
	void evaluate_expr4(double& result);
	void evaluate_expr5(double& result);
	void evaluate_expr6(double& result);
	void get_token();

public:
	Calculator() = default;
	Calculator(Calculator const&) = delete;
	Calculator& operator = (Calculator const&) = delete;
	Calculator(Calculator&&) = delete;
	Calculator& operator = (Calculator&&) = delete;
	~Calculator();

	double calc(const char* str);
};
