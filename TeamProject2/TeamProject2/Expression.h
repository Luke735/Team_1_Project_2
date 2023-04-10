#pragma once
#ifndef Expression_H
#define Expression_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stack>
#include <unordered_map>
using namespace std;

class Expression {
public:
	Expression(string exp);
	void print();
	string toPostfix(string exp);
	int evaluate(const string& postfixStr);
	bool isNumber(const string& str);
	static int precedence(string);
private:
	string infixExpression;
};

#endif
