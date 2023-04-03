#include <iostream>
#include <fstream>
#include <iomanip>
#include "Expression.h"

using namespace std;

int main() {
    ifstream fin("testCaseFile.txt");

    if (!fin.is_open()) {
        cout << "Could not open file" << endl;
    }
    else {
        ofstream fout;
        string line;
        Expression expressionVec = Expression();
        while (getline(fin, line)) { //Gets each line from the input file
            expressionVec.pushBack(line);
        }

        expressionVec.print();
    }
}
