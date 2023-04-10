#pragma once
#ifndef Expression_H
#define Expression_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class Expression {
public:
	Expression();
	void pushBack(string str);
	void print();
	string toPostfix(string str);
	int evaluate(string str);
	static int precedence(string);
private:
	vector<string> infixExpressions;

};

#endif
