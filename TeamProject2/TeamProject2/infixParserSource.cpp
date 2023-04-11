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
        
        //Gets each line from the input file
        while (getline(fin, line)) {
            //construct a new Expression object with the infix string
            Expression expression = Expression(line);
            //Expression's print() prints the infix expression, calls toPostfix() and prints its return, then calls evaluate() and prints its return
            expression.print();
        }
    }
    return 0;
}
