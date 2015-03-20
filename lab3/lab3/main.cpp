#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

struct Element{
    int val;
    Element *next, *prev;
};

class List2W{
    public: Element *head, *tail;
};

void init(List2W& l){
    List2W *temp = new List2W;
    temp->head = NULL;
    temp->tail = NULL;
    l = *temp;
}
bool isEmpty (List2W& l){
    return (l.head == NULL && l.tail == NULL);
}

void insertHead(List2W& l, int x){
    Element *newHead = new Element;
    newHead->val = x;
    if ( isEmpty(l) ){
        l.tail = newHead;
    } else {
        l.head->prev = newHead;
    }
    //cycled
    newHead->prev = l.tail;
    newHead->next = l.head;
    l.head = newHead;
}

bool deleteHead(List2W& l, int &oldHead){
    if ( isEmpty(l) ){
        return false;
    }
    
    Element *temp = l.head;
    oldHead = temp->val;
    
    if ( l.head == l.tail )
    {
        l.head = NULL;
        l.tail = NULL;
    } else {
        temp->next->prev = l.tail;
        l.head = temp->next;
    }
    
    delete temp;
    
    return true;
}

void insertTail(List2W& l, int x){
    if ( isEmpty(l) ){
        insertHead( l, x );
        return;
    }
    
    Element *temp = new Element;
    temp->val = x;
    temp->next = NULL;
    temp->prev = l.tail;
    l.tail->next = temp;
    l.tail = temp;
}

bool deleteTail(List2W& l, int &oldTail){
    if ( l.head == l.tail ){
        return deleteHead(l, oldTail);
    }
    
    Element *temp = l.tail;
    oldTail = temp->val;
    temp->prev->next = NULL;
    l.tail = temp->prev;
    
    delete temp;
    
    return true;
}

int findValue(List2W& l, int value){
    if ( isEmpty(l) ){
        return -1;
    }
    
    Element *temp = l.head;
    int i = 0;
    
    while ( temp!= NULL) {
        if ( temp->val == value ){
            return i;
        }
        temp = temp->next;
        i++;
    }
    
    return -1;
}
            

void removeAllValue(List2W & l,int value){
    if ( isEmpty(l) ){
        return;
    }
    
    Element *temp = l.head, *del;
    int i;
    
    if ( l.head->val == value ){
        temp = temp->next;
        deleteHead(l, i);
    }
    
    while ( temp!= NULL) {
        if ( temp->val == value ){
            
            if ( l.tail == temp ) {
                temp = temp->next;
                deleteTail(l, i);
                return;
            }
            
            del = temp;
            temp = temp->next;
            del->next->prev = del->prev;
            del->prev->next = del->next;
            
            delete del;
            
        } else {
            temp = temp->next;
        }
    }
}

void showListFromHead(List2W& l){
    Element *temp = l.head;
    while ( temp!= NULL ) {
        cout << temp->val << ",";
        temp = temp->next;
    }
    cout << endl;
}

void showListFromTail(List2W& l){
    Element *temp = l.tail;
    while ( temp!= NULL ) {
        cout << temp->val << ",";
        temp = temp->prev;
    }
    cout << endl;
}

void clearList(List2W& l){
    int i;
    while ( l.head != NULL ){
        deleteHead(l, i);
    }
}

void addList(List2W& l1, List2W& l2){
    if ( l1.head == l2.head ){
        return;
    }
    int i;
    while ( !isEmpty(l2) ){
        insertTail(l1, l2.head->val);
        deleteHead(l2, i);
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
    List2W *list = NULL;
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
        
        if(isCommand(command,"SH"))
        {
            showListFromHead(list[currentL]);
            continue;
        }
        
        if(isCommand(command,"ST"))
        {
            showListFromTail(list[currentL]);
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
        
        if(isCommand(command,"FV"))
        {
            int ret;
            ret=findValue(list[currentL],value);
            cout << ret << endl;
            continue;
        }
        
        if(isCommand(command,"RV"))
        {
            removeAllValue(list[currentL],value);
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
        
        if(isCommand(command,"AD"))
        {
            addList(list[currentL], list[value]);
            continue;
        }
        
        if(isCommand(command,"GO"))
        {
            list=new List2W[value];
            continue;
        }
        
        cout << "wrong argument in test: " << command << endl;
    }
}
