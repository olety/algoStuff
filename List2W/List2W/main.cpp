#include <iostream>
#include <string.h>
#include <string>
#include <sstream>

using namespace std;

struct Element{
    int val, key;
    Element *next, *prev;
};

class List2W{
public: Element *sentinel;
};


void init(List2W& l){
    List2W *temp = new List2W;
    temp->sentinel = new Element;
    temp->sentinel->next = temp->sentinel;
    temp->sentinel->prev = temp->sentinel;
    l = *temp;
}

void showElem ( Element &elem ){
    cout << elem.key << "(" << elem.val << ")" << endl;
}

void showElemComma ( Element &elem ){
    cout << elem.key << "(" << elem.val << ")" << ",";
}

bool isEmpty (List2W& l){
    return (l.sentinel->next == l.sentinel && l.sentinel->prev == l.sentinel );
}

void insertAfter ( Element& el1, Element& insert){
    insert.next = el1.next;
    insert.prev = &el1;
    el1.next->prev = &insert;
    el1.next = &insert;
}

void insertBefore ( Element& el2, Element& insert){
    insertAfter(*el2.prev, insert);
}

void deleteElem ( Element& elem ){
    elem.prev->next = elem.next;
    elem.next->prev = elem.prev;
    delete &elem;
}

void insertElem ( List2W& l, Element& elem){
    if ( isEmpty(l) ){
        l.sentinel->key = 0;
        l.sentinel->val = 0;
        l.sentinel->next = &elem;
        l.sentinel->prev = &elem;
        elem.next = l.sentinel;
        elem.prev = l.sentinel;
        return;
    }
    
    if ( l.sentinel->next->key > elem.key){
        insertAfter(*l.sentinel, elem);
        return;
    }
    
    if ( l.sentinel->prev->key < elem.key){
        insertBefore(*l.sentinel, elem);
        return;
    }
    
    Element *temp = l.sentinel->next;
    while ( temp != l.sentinel && temp->key <= elem.key ){
        
        if ( temp->next->key > elem.key && temp->key < elem.key ){
            insertAfter(*temp, elem);
            return;
        }
        
        if ( temp->next->key != elem.key && temp->key == elem.key )
        {
            insertAfter(*temp, elem);
            return;
        }
        
        temp = temp->next;
    }
    
    
}


bool findKey(List2W& l, int key, Element& elem){
    if ( isEmpty(l))
        return false;
    
    Element *temp = l.sentinel->next;
    
    while ( temp != l.sentinel && temp->key <= key ){
        
        if( temp->key == key )
        {
            elem = *temp;
            return true;
        }
        temp = temp->next;
    }
    
    return false;
}


void removeAllKeys(List2W & l,int key){
    if ( isEmpty(l))
        return;
    
    if ( l.sentinel->next->next == l.sentinel ){
        if ( l.sentinel->next->key == key )
        {
            delete l.sentinel->next;
            l.sentinel = NULL;
        }
        return;
    }
    
    Element *temp = l.sentinel->next;
    Element *del;
    while ( temp != l.sentinel && temp->key <= key ){
        
        if( temp->key == key )
        {
            del = temp;
            deleteElem(*del);
        }
        
        temp = temp->next;
    }
}

void showListFromHead(List2W& l){
    if ( !isEmpty(l) ){
        Element *temp = l.sentinel->next;
        while ( temp != l.sentinel ){
            showElemComma(*temp);
            temp = temp->next;
        }
    }
    cout << endl;
}

void showListFromTail(List2W& l){
    if ( !isEmpty(l) ){
        Element *temp = l.sentinel->prev;
        while ( temp != l.sentinel ){
            showElemComma(*temp);
            temp = temp->prev;
        }
    }
    cout << endl;
}

void clearList(List2W& l){
    while ( !isEmpty(l)){
        deleteElem(*l.sentinel->next);
    }
}

void addList(List2W& l1, List2W& l2){
    if ( l1.sentinel == l2.sentinel )
        return;
    if ( isEmpty(l2))
        return;
    
    Element *temp;
    while ( true ){
        temp = l2.sentinel->next;
        l2.sentinel->next = l2.sentinel->next->next;
        insertElem(l1, *temp);
        if ( l2.sentinel->next == l2.sentinel ){
            l2.sentinel->prev = l2.sentinel;
            return;
        }
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
    int value, value2;
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
        cout << "!" << line << endl;
        
        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);
        
        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
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
        
        // read next argument, one int value
        stream >> value;
        
        if(isCommand(command,"FK"))
        {
            Element elem;
            bool retBool=findKey(list[currentL], value ,elem);
            if(retBool)
                showElem(elem);
            else
                showBool(retBool);
            continue;
        }
        
        
        if(isCommand(command,"RK"))
        {
            removeAllKeys(list[currentL], value);
            continue;
        }
        
        if(isCommand(command,"CH"))
        {
            currentL=value;
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
        // two argument command
        
        stream >> value2;
        
        if(isCommand(command,"IE"))
        {
            Element* temp = new Element;
            temp->key = value;
            temp->val = value2;
            insertElem(list[currentL], *temp);
            continue;
        }
        cout << "wrong argument in test: " << command << endl;
    }
}
