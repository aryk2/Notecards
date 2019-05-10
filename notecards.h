#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
#include <string>
#include <dirent.h>
using namespace std;

class node;
class note_set {
    public:
        note_set();
        ~note_set();
        int add_set();
        char * view_notefolder();
        int load_set(char * path);
        int clear_lll(node * & head);
        void append_lll(node * & head, char * term, char * define);       
    private:
    node * main_list;
    node * more_study;
    node * studied;
};

class node {
    public:
        node();
        ~node();
        char * term;
        char * definition;
        node * next;
};
