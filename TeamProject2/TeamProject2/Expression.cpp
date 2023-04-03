#include "Expression.h"

using namespace std;

//Constructor, does nothing
Expression::Expression() { }

int Expression::precedence(string str) {
	if (str == "^") { return 1; }
	if (str == "*" || str == "/" || str == "%") { return 2; }
	if (str == "+" || str == "-") { return 3; }
	if (str == ">" || str == ">=" || str == "<" || str == "<=") { return 4; }
	if (str == "=" || str == "!") { return 5; }
	if (str == "&") { return 6; }
	if (str == "|") { return 7; }
}

/** Returns the postfix expression of the infix string passed to it.
	@param infixExp: the infix expression
	@return: the postfix expression
*/
string Expression::toPostfix(int index) {
	return infixExpressions.at(index);
}

void Expression::pushBack(string str) {
	infixExpressions.push_back(str);
}

int Expression::evaluate(string str) {
	return -1;
}

void Expression::print() {
	for (size_t i = 0; i < infixExpressions.size(); ++i) {
		cout << "INFIX: " << endl << infixExpressions.at(i) << endl;
		string postfixStr = this->toPostfix(i);
		cout << "POSTFIX: " << endl << postfixStr << endl;
		cout << "EVALUATED: " << endl << evaluate(postfixStr) << endl;
	}
}
