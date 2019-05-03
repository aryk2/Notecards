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
        note_set notes;
        if(choice == 1)
            notes.add_set();
        if(choice == 2)
            notes.view_notefolder();
    }
    return 0;
}

int note_set::add_set() {
    return 1;
}

int note_set::view_notefolder() {
    node * head;
    DIR * Dir;
    struct dirent * DirEntry;
    Dir = opendir("notefolder");
     
    cout << "\nOptions: \n";
    while(DirEntry = readdir(Dir)) {
        if(DirEntry->d_name[0] != '.') {
	    cout << DirEntry->d_name << endl;
            append_lll(head, DirEntry->d_name);
        }
    }
    
    cout << "\nwhich set would you like to open:\n";
}

void note_set::append_lll(node * & head, char * entry) {
    node * temp = head;
    node * new_node = new node;
    new_node -> term = new char [strlen(entry) +1];
    strcpy(new_node -> term, entry);
    while(temp -> next) 
        temp = temp -> next;
    temp -> next = new_node; 
}

int note_set::clear_lll(node * & head) {
    if(!head)
	return 0;
    clear_lll(head -> next);
    delete head;
    return 0;
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


note_set::note_set() {
    main_list = NULL;
    more_study = NULL;
    studied = NULL;
}

note_set::~note_set() {
    if(main_list) {
        clear_lll(main_list);
        main_list = NULL;
    }
    if(more_study) {
        clear_lll(more_study);
        more_study = NULL;
    }
    if(studied) {
	clear_lll(studied);
	studied = NULL;
    }
}

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