#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <string>
#include <dirent.h>
using namespace std;

class node {
    public:
        node();
        ~node();
        char * term;
        char * definition;
        node * next;
};

node::node() {
    term = NULL;
    definition = NULL;
    next = NULL;
}

node::~node() {
    if(term) {
        delete [] term;
        term = NULL;
    }
    if(definition) {
        delete [] definition;
        definition = NULL;
    }
    next = NULL;
}
//prototypes
int add_set();
int view_notefolder();
void add_to_lll_end(node * & head, char * entry);
