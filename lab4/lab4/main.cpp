#include<iostream>
#include<string.h>
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
    temp->sentinel = NULL;
    l = *temp;
}

void showElem ( Element &elem ){
    cout << elem.key << "(" << elem.val << ")" << endl;
}

void showElemComma ( Element &elem ){
    cout << elem.key << "(" << elem.val << ")" << "," ;
}

bool isEmpty (List2W& l){
    return (l.sentinel = NULL);
}

void insertAfter ( Element& l1, Element& insert){
    insert.next = l1.next;
    insert.prev = &l1;
    l1.next->prev = &insert;
    l1.next = &insert;
}

void insertBefore ( Element& l2, Element& insert){
    insertAfter(*l2.prev, insert);
}

void deleteElem ( Element& elem ){
    elem.prev->next = elem.next;
    elem.next->prev = elem.prev;
    delete &elem;
}

void insertElem ( List2W& l, Element& elem){
    if ( isEmpty(l) ){
        l.sentinel->key = NULL;
        l.sentinel->val = NULL;
        l.sentinel->next = &elem;
        l.sentinel->prev = &elem;
        elem.next = l.sentinel;
        elem.prev = l.sentinel;
        return;
    }
    
    if ( l.sentinel->next->key <= elem.key){
        insertAfter(*l.sentinel, elem);
    }
    
    Element *temp = l.sentinel;
    while ( temp->next != l.sentinel && temp->key <= elem.key ){
        
        temp = temp->next;
        
        if ( temp->next->key > elem.key && temp->key < elem.key ){
            insertAfter(*temp, elem);
            return;
        }
        
        if ( temp->next->key != elem.key && temp->key == elem.key )
        {
            insertAfter(*temp, elem);
            return;
        }
    }
    
    insertBefore(*l.sentinel, elem);
    
}


bool findKey(List2W& l, int key, Element& elem){
    if ( isEmpty(l))
        return false;
    
    Element *temp = l.sentinel;
    
    while ( temp->next != l.sentinel && temp->key <= temp->next->key ){
        temp = temp->next;
        if( temp->key == key )
        {
            elem = *temp;
            return true;
        }
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
    
    Element *temp = l.sentinel;
    Element *del;
    while ( temp->next != l.sentinel && temp->next->key <= key ){
    
        temp = temp->next;
        
        if( temp->key == key )
        {
            del = temp;
            deleteElem(*del);
        }
    }
}

void showListFromHead(List2W& l){
    Element *temp = l.sentinel;
    while ( temp->next != l.sentinel ){
        temp = temp->next;
        showElemComma(*temp);
        cout << ",";
    }
}

void showListFromTail(List2W& l){
    Element *temp = l.sentinel;
    while ( temp->prev != l.sentinel ){
        showElemComma(*temp);
        temp = temp->prev;
    }
}

void clearList(List2W& l){
    while ( !(l.sentinel->next == l.sentinel)){
        deleteElem(*l.sentinel->next);
    }
    l.sentinel = NULL;
}

void addList(List2W& l1, List2W& l2){
    if ( l1.sentinel == l2.sentinel )
        return;
    if ( isEmpty(l2))
        return;
    
    while (l2.sentinel->next != l2.sentinel){
        insertElem(l1, *l2.sentinel->next);
    }
    
    l2.sentinel = NULL;
    
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
        cout << "!" << line << endl;;
        
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
