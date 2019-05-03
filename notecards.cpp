#include "notecards.h"

int test_readin();

int main() {
    test_readin();
    return 0;
}

int test_readin() {
    ifstream myfile;
    string line;
    myfile.open ("notefolder/notes.txt");
    if(myfile.is_open()) {
        while( getline (myfile, line) ) 
            cout << line << '\n';
        myfile.close();
    }
    return 0;
}
