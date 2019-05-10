#include "notecards.h"

int main() {
    int choice = 1;
    char * path;
    while(choice) {
        cout << "\nNotecard Program options:\n"
             << "1. add a new set\n"
             << "2. view existing sets\n"
             << "0 - EXIT\n"
             << "choice: ";
    
        cin >> choice; 
        note_set notes;
        if(!choice)
	    break;
        if(choice == 1)
            notes.add_set();
        if(choice == 2) {
            path = notes.view_notefolder();
            notes.load_set(path);
            notes.start_quiz(path, notes.get_main_list());
        }
    }
    return 0;
}

int note_set::add_set() {
    char * set_name = new char[200];
    char file_path[200] = {"notefolder/"};
    char file_ext[10] = {".txt"};
    cout << "\nenter a new set\n"
         << "please use no spaces and no .txt\n"
         << "set name: ";
    cin.ignore(100, '\n');
    cin.get(set_name, 200, '\n');
    cin.ignore(200, '\n');
    strcat(file_path, set_name);
    strcat(file_path, file_ext);
    ofstream file;
    file.open (file_path);
    char another = 'y';
    while(another == 'y') {
        char term[500];
        char define[1000];
        cout << "\nenter term: ";
        cin.get(term, 500, '\n');
        cin.ignore(500, '\n');
        cout << "\ndefine the term: ";
        cin.get(define, 1000, '\n');
        cin.ignore(1000, '\n');
        for(int i = 0; i < strlen(term); ++i)
	    file << term[i];
        file << "\n";
        for(int i = 0; i < strlen(define); ++i)
            file << define[i];
        file << "\n";
        
        cout << "add another? (y/n): ";
        cin >> another;
        cin.ignore(10, '\n');
        if(another == 'n')
 	    break;
    }
    file.close();
    return 1;
}

char * note_set::view_notefolder() {
    node * head = NULL;
    DIR * Dir;
    struct dirent * DirEntry;
    Dir = opendir("notefolder");
     
    cout << "\nOptions: \n";
    while(DirEntry = readdir(Dir)) {
        if(DirEntry->d_name[0] != '.') {
	    cout << DirEntry->d_name << endl;
            append_lll(head, DirEntry->d_name, NULL);
        }
    }
    int done = 0;
    while(!done) { 
        cout << "\nwhich set would you like to open:\n";
        cin.ignore(100, '\n');
        char * set = new char[200];
        cin.get(set, 200);
        cin.ignore(200, '\n');
        node * temp = head;
        while(temp) {
            if(strcmp(set, temp -> term) == 0) {
                clear_lll(head);
                return set;
            }
            else
		temp = temp -> next;
        }
        cout << "\nfile name not found"
             << "\nto enter another, enter 1"
             << "\nif there is no set you would like, enter 0\n";
        cin >> done;
    }
    return NULL;
}

int note_set::load_set(char * path) {
    char file_path[200] = {"notefolder/"};
    strcat(file_path, path);
    ifstream myfile;
    myfile.open(file_path);
    string line;
    if(myfile.is_open()) {
        int i = 0;
    	char * term;
        char * define;
        while( getline (myfile, line) ) {
            if(i % 2 == 0) {
                term = new char [line.length() +1];
                strcpy(term, line.c_str());
            }
            else{ 
                define = new char [line.length() +1];
                strcpy(define, line.c_str());
                append_lll(this->main_list, term, define);
                delete [] term;
                term = NULL;
                delete [] define;
                define = NULL;
            }
            ++i;
        }     
        myfile.close();
    }
}

int note_set::start_quiz(char * path, node * head) {
    cout << "you are now being quized on the ";
    int len = strlen(path);
    for(int i = 0; i < len; ++i) 
        cout << path[i];
    cout << " note card set\n"
         << "you will be given a term, you can choose to view the definition\n"
         << "you can choose to move each card to a set to study more or a \n"
         << "set for cards that you feel have been studied enough for this quiz\n";
    getchar();
    node * temp = head;
    node * further_study = NULL;
    while(temp) {
        for(int i = 0; i < 70; ++i)
	    cout << endl;
        cout << "press r to reveal definition\n\n"
             << "term: " << temp -> term << endl;
        char result;
        cin >> result;
        cin.ignore(100, '\n');
        if(result == 'r')
	    cout << "definition: " << temp -> definition << endl;
        cout << "\npress a to add to study this card later\n"
             << "press b if you feel good about this card and don't need more study\n"
             << "press r to reveal definintion\n";
        cin >> result;
        cin.ignore(100, '\n');
        if(result == 'a')
	    append_lll(further_study, temp -> term, temp -> definition);
        if(result == 'b')
            append_lll(this -> studied, temp -> term, temp -> definition);
        if(result == 'r')
	    cout << "definition: " << temp -> definition << endl;
        cout << "\n\npress enter for next term";
        getchar();
        temp = temp -> next;
    }
    clear_lll(this -> more_study);
    this -> more_study = further_study;
    if(this -> more_study) {
	cout << "\nready to view the cards marked for later study (y/n)? ";
        char choice;
        cin >> choice;
        if(choice == 'y')
	    start_quiz(path, more_study);
    }
    else
	cout << "no more note cards marked for more study, exiting\n";
    delete [] path;
    return 0;
}

void note_set::append_lll(node * & head, char * term, char * define) {
    node * temp = head;
    node * new_node = new node;
    new_node -> term = new char [strlen(term) +1];
    strcpy(new_node -> term, term);
    if(define) {
        new_node -> definition  = new char [strlen(define) +1];
        strcpy(new_node -> definition, define);
    }
    if(temp) {
        while(temp -> next) 
            temp = temp -> next;
        temp -> next = new_node; 
    }
    else
	head = new_node;
}

void note_set::test_disp(node * head) {
    if(!head)
	return;
    if(head -> term)
        cout << head -> term << endl;
    if(head -> definition)
	cout << head -> definition << endl;
    cout << endl;   
    test_disp(head -> next);
}

int note_set::clear_lll(node * & head) {
    if(!head)
	return 0;
    clear_lll(head -> next);
    delete head;
    return 0;
} 

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
