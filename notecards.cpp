#include "notecards.h"


int main() {
    int choice = 1;
    while(choice) {
        cout << "\nNotecard Program options:\n"
             << "1. add a new set\n"
             << "2. view existing sets\n"
             << "0 - EXIT\n"
             << "choice: ";
    
        cin >> choice; 
        if(choice == 1)
            add_set();
        if(choice == 2)
            view_notefolder();
    }
    return 0;
}

int add_set() {

}

int view_notefolder() {
    node * head;
    DIR * Dir;
    struct dirent * DirEntry;
    Dir = opendir("notefolder");
     
    cout << "\nOptions: \n";
    while(DirEntry = readdir(Dir)) {
        if(DirEntry->d_name[0] != '.') {
	    cout << DirEntry->d_name << endl;
            add_to_lll_end(head, DirEntry->d_name);
        }
    }
    
    cout << "\nwhich set would you like to open:\n";
}

void add_to_lll_end(node * & head, char * entry) {
    node * temp = head;
    node * new_node = new node;
    new_node -> term = new char [strlen(entry) +1];
    strcpy(new_node -> term, entry);
    while(temp -> next) 
        temp = temp -> next;
    temp -> next = new_node; 
}

void clear_lll(node * & head) {

} 
//example
/*
    ifstream myfile;
    string line;
    myfile.open ("notefolder/notes.txt");
    if(myfile.is_open()) {
        while( getline (myfile, line) ) 
            cout << line << '\n';
        myfile.close();
    }
    */
