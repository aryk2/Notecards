#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class node {
    public:
        node();
        ~node();
        char * term;
        char * definition;
        node * next;
};
