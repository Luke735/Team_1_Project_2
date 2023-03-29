#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>
#include <iterator>
#include <vector>

using namespace std;

int main() {
    ifstream fin("testCaseFile.txt");

    if (!fin.is_open()) {
        cout << "Could not open file" << endl;
    }
    else {
        ofstream fout;
        string line;
        while (getline(fin, line)) { //Gets each line from the input file

        }
    }
}