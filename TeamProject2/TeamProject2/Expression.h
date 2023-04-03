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
	string toPostfix(int index);
	int evaluate(string str);
private:
	vector<string> infixExpressions;
	
};

#endif
