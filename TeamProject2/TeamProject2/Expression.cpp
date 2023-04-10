#include "Expression.h"

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

//Constructor, does nothing
Expression::Expression() { }

int Expression::precedence(string str) {
	if (str == "^") { return 1; }
	if (str == "*" || str == "/" || str == "%") { return 2; }
	if (str == "+" || str == "-") { return 3; }
	if (str == ">" || str == ">=" || str == "<" || str == "<=") { return 4; }
	if (str == "==" || str == "!=") { return 5; }
	if (str == "&&") { return 6; }
	if (str == "||") { return 7; }
	return 0;
}

/** Returns the postfix expression of the infix string passed to it.
	@param exp: the infix expression
	@return: the postfix expression
*/
string Expression::toPostfix(string exp) {
	exp.erase(remove(exp.begin(), exp.end(), ' '), exp.end());
	stack<string> s;
	unordered_map<string, int> precedenceMap;
	string postfixExp = "";
	string token;

	//Populate the precedence map
	for (int i = 0; i < exp.length(); i++) {
		token = exp.substr(i, 2);
		if (precedence(token) != 0) {
			precedenceMap[token] = precedence(token);
			i++;
		}
		else {
			token = exp.substr(i, 1);
			if (precedence(token) != 0) {
				precedenceMap[token] = precedence(token);
			}
		}
	}

	//Process each token in the map
	for (int i = 0; i < exp.length(); i++) {
		token = exp.substr(i, 2);
		if (precedence(token) != 0) {
			//Handles all boolean operators
			while (!s.empty() && s.top() != "(" && precedenceMap[s.top()] <= precedence(token)) {
				postfixExp += s.top() + " ";
				s.pop();
			}
			s.push(token);
			i++;
		}
		else {
			token = exp.substr(i, 1);
			if (precedence(token) != 0) {
				//Handles all other operators
				while (!s.empty() && s.top() != "(" && precedenceMap[s.top()] <= precedence(token)) {
					postfixExp += s.top() + " ";
					s.pop();
				}
				s.push(token);
			}
			else if (token == "(") {
				s.push(token);
			}
			else if (token == ")") {
				//Handles operators inside of parentheses
				while (!s.empty() && s.top() != "(") {
					postfixExp += s.top() + " ";
					s.pop();
				}
				if (!s.empty() && s.top() == "(") {
					s.pop();
				}
			}
			else {
				//Processes operands
				postfixExp += token;
				if (i < exp.length() - 1) {
					if (!isdigit(exp.at(i + 1))) { postfixExp += ' '; }
				}
				else{ postfixExp += ' '; }
			}
		}
	}

	//Pop all remaining operators
	while (!s.empty()) {
		postfixExp += s.top() + " ";
		s.pop();
	}

	postfixExp.pop_back();

	//Return the postfix expression
	return postfixExp;

}

void Expression::pushBack(string str) {

}

int Expression::evaluate(string str) {
	return -1;
}

void Expression::print() {
	for (size_t i = 0; i < infixExpressions.size(); ++i) {
		cout << "INFIX: " << endl << infixExpressions.at(i) << endl;
		//string postfixStr = this->toPostfix(i);
		//cout << "POSTFIX: " << endl << postfixStr << endl;
		//cout << "EVALUATED: " << endl << evaluate(postfixStr) << endl;
	}
}
