#include "Expression.h"

using namespace std;

//Constructor, sets infixExpression
Expression::Expression(string exp) { infixExpression = exp; }

/** Determines the precedence of the operator passed to it
	@param str: the operator as a string
	@return: the precedence of the operator as an int
*/
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
				else { postfixExp += ' '; }
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

/** Evaluates a postfix expression.
	@param postfixStr: a postfix expression in a string
	@return: the integer evaluation result
*/
int Expression::evaluate(const string& postfixStr) {
	//create empty stack
	stack<int> stack;
		
	// use input string stream to easily get each token
	istringstream iss(postfixStr);
	string token;
	// while there are more tokens in the stream
	while (iss >> token) {
		//if the token is an operand, push it unto the stack (stoi(token) converts string to int, but only after token string is confirmed to be one)
		if (isNumber(token)) { stack.push(stoi(token)); }
		else {
			
			// Pop the right operand from the stack.
			int right = stack.top(); stack.pop();
			// Pop the left operand from the stack.
			int left = stack.top(); stack.pop();
			// Push the evaluation result onto the stack.
			if (token == "+") { stack.push(left + right); }
			if (token == "-") { stack.push(left - right); }
			if (token == "*") { stack.push(left * right); }
			if (token == "^") { stack.push(pow(left, right)); }
			if (token == "%") { stack.push(left % right); }
			if (token == ">") {
				if (left > right) { stack.push(1); }
				else { stack.push(0); }
			}
			if (token == "<") {
				if (left < right) { stack.push(1); }
				else { stack.push(0); }
			}
			if (token == ">=") {
				if (left >= right) { stack.push(1); }
				else { stack.push(0); }
			}
			if (token == "<=") {
				if (left <= right) { stack.push(1); }
				else { stack.push(0); }
			}
			if (token == "==") {
				if (left == right) { stack.push(1); }
				else { stack.push(0); }
			}
			if (token == "!=") {
				if (left != right) { stack.push(1); }
				else { stack.push(0); }
			}
			if (token == "&&") {
				if (left != 0 && right != 0) { stack.push(1); }
				else { stack.push(0); }
			}
			if (token == "||") {
				if (left == 0 && right == 0) { stack.push(0); }
				else { stack.push(1); }
			}
			if (token == "/") {
				if (right == 0) { 
					cout << "Cannot divide by zero!" << endl;
					exit(1);
				}
				else { stack.push(left / right); }
			}
		}
	}
	//the remaining int on the stack is the evaluation result
	return stack.top();
}

/** Tests whether a string is a number by calling char's isdigit() for every char in the string
	@param str: the string to test
	@return: true for is number (operand), false for is not number (operator)
*/
bool Expression::isNumber(const string& str) {
	for (char ch : str) {
		if (!isdigit(ch)) { return false; }
	}
	return true;
}

// Prints the infix expression, calls toPostfix and prints its return, then calls evaluate and prints its return
void Expression::print() {
		cout << "INFIX: " << endl << infixExpression << endl;
		string postfixStr = this->toPostfix(infixExpression);
		cout << "POSTFIX: " << endl << postfixStr << endl;
		cout << "EVALUATED: " << endl << evaluate(postfixStr) << endl;
}
