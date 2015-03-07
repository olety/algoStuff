#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

struct Element{
    Element *next;
    int val;
};

typedef struct List{
    Element *head;
} List;

void init(List& l){
    List *temp = new List;
    temp->head = new Element;
    temp->head->next = NULL;
    temp->head->val = NULL;
    l = *temp;
}

void insertHead(List& l, int x){
    Element *temp_head;
    temp_head->next = l.head;
    temp_head->val = x;
    l.head = temp_head;
}

bool deleteHead(List& l, int &oldHead){
    if ( l.head == NULL ){
        return false;
    }
    Element *tempHead = l.head;
    oldHead = l.head->val;
    l.head = l.head->next;
    delete tempHead;
    return true;
}

void insertTail(List& l, int x){
    Element *temp_head = l.head;
    Element *tail;
    tail->next = NULL;
    tail->val = x;
    while ( temp_head->next != NULL )
        temp_head = temp_head->next;
    temp_head->next = tail;
}

bool deleteTail(List& l, int &oldTail){
    if ( l.head == NULL ){
        return false;
    }
    Element *prev_elem = NULL,*temp_elem = l.head;
    while ( temp_elem->next != NULL ){
        prev_elem = temp_elem;
        temp_elem = temp_elem->next;
    }
    prev_elem->next = NULL;
    oldTail = temp_elem->val;
    delete temp_elem;
    return false;
}

int findPosOfValue(List& l, int value){
    Element *temp_elem = l.head;
    int i = 0;
    
    if ( l.head->next == NULL && l.head->val == value)
        return i;
    
    while ( temp_elem->next != NULL ){
        temp_elem = temp_elem->next;
        i++;
        if ( temp_elem->val == value){
            return i;
        }
    }
    return -1;
}

bool deleteValue(List& l, int value){
    Element *prev_elem = NULL;
    Element *temp_elem = l.head;
    
    
    if ( l.head->next == NULL && l.head->val == value){
        int i;
        return deleteHead(l, i);
    }
    
    while ( temp_elem->next != NULL ){
        prev_elem = temp_elem;
        temp_elem = temp_elem->next;
        if ( temp_elem->val == value){
            prev_elem->next = temp_elem->next;
            delete temp_elem;
            return true;
        }
    }
    
    return false;
}

bool atPosition(List& l, int pos, int &value){
    if ( pos < 0 )
        return false;
    
    Element *temp_elem = l.head;
    for ( int i = 0; i < pos; i++){
        if ( temp_elem->next == NULL){
            return false;
        }
        
        temp_elem = temp_elem->next;
    }
    value = temp_elem->val;
    return true;
}

void showListFromHead(List& l){
    if ( l.head == NULL ){
        cout << endl;
        return;
    }
    
    if ( l.head->next == NULL ){
        cout << l.head->val << "," << endl;
        return;
    }
    
    Element *temp_elem = l.head;
    while ( temp_elem->next != NULL ) {
        cout << temp_elem->val << ",";
        temp_elem = temp_elem->next;
    }
    cout << endl;
}

void clearList(List& l){
    int i;
    while ( l.head != NULL ){
        deleteHead(l, i);
    }
}

void showBool(bool val){
    if(val)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}


bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}

int main(){
    string line;
    string command;
    List *list;
    int currentL=0;
    int value;
    cout << "START" << endl;
    while(true){
        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }
        
        // copy line on output with exclamation mark
        cout << "!" << line << endl;;
        
        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);
        
        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
        }
        
        // zero-argument command
        if(isCommand(command,"DH"))
        {
            int retValue;
            bool retBool=deleteHead(list[currentL],retValue);
            if(retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }
        if(isCommand(command,"DT"))
        {
            int retValue;
            bool retBool=deleteTail(list[currentL],retValue);
            if(retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }
        
        if(isCommand(command,"SL"))
        {
            showListFromHead(list[currentL]);
            continue;
        }
        
        if(isCommand(command,"CL"))
        {
            clearList(list[currentL]);
            continue;
        }
        
        if(isCommand(command,"IN"))
        {
            init(list[currentL]);
            continue;
        }
        
        // read next argument, one int value
        stream >> value;
        
        if(isCommand(command,"FP"))
        {
            int ret;
            ret=findPosOfValue(list[currentL],value);
            cout << ret << endl;
            continue;
        }
        
        if(isCommand(command,"DV"))
        {
            showBool(deleteValue(list[currentL],value));
            continue;
        }
        
        
        if(isCommand(command,"AT"))
        {
            int retValue;
            bool retBool=atPosition(list[currentL],value,retValue);
            if(retBool)
                cout << retValue << endl;
            else
                showBool(retBool);
            continue;
        }
        
        if(isCommand(command,"CH"))
        {
            currentL=value;
            continue;
        }
        
        if(isCommand(command,"IH"))
        {
            insertHead(list[currentL],value);
            continue;
        }
        
        if(isCommand(command,"IT"))
        {
            insertTail(list[currentL],value);
            continue;
        }
        
        if(isCommand(command,"GO"))
        {
            list=new List[value];
            continue;
        }
        
        cout << "wrong argument in test: " << command << endl;
    }
}
