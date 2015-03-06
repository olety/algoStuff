#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

struct Element{
};

struct List{
};

void init(List& l){
}

void insertHead(List& l, int x){
}

bool deleteHead(List& l, int &oldHead){
    return false;
}

void insertTail(List& l, int x){
}

bool deleteTail(List& l, int &oldTail){
    return false;
}

int findPosOfValue(List& l, int value){
    return -1;
}

bool deleteValue(List& l, int value){
    return false;
}

bool atPosition(List& l, int pos, int &value){
    return false;
}

void showListFromHead(List& l){
}

void clearList(List& l){
    
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
