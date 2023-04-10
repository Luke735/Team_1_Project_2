#include <iostream>
#include <fstream>
#include <iomanip>
#include "Expression.h"

using namespace std;

int main() {
   ifstream fin("testCaseFile.txt");

   if (!fin.is_open()) {
       cout << "Could not open file" << endl;
       return -1;
   }
   else {
        ofstream fout;
        string line;
        Expression expressionVec = Expression();
        while (getline(fin, line)) { //Gets each line from the input file
            cout << "Original expression: " << line << endl;
            Expression e;
            cout << "Postfix expression: " << e.toPostfix(line) << endl;
            cout << "Evaluated expression: " << e.evaluate(e.toPostfix(line)) << endl;
        }
   }
   return 0;
}
