#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

class Queue{
public:
};

void init(Queue& q, int size){
}

bool enqueue(Queue& q, int value){
    return false;
}

bool dequeue(Queue& q, int &value){
    return false;
}
bool isEmpty(Queue& q){
    return false;
}
bool isFull(Queue& q){
    return false;
}
void show(Queue& q){
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
    Queue *queue;
    int currentQ=0;
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
        if(isCommand(command,"EM"))
        {
            showBool(isEmpty(queue[currentQ]));
            continue;
        }
        if(isCommand(command,"FU"))
        {
            showBool(isFull(queue[currentQ]));
            continue;
        }
        if(isCommand(command,"SH"))
        {
            show(queue[currentQ]);
            continue;
        }
        if(isCommand(command,"DE"))
        {
            int ret;
            bool retBool=dequeue(queue[currentQ],ret);
            if(!retBool)
                cout << "false" << endl;
            else
                cout << ret << endl;
            continue;
        }
        
        // read next argument, one int value
        stream >> value;
        
        if(isCommand(command,"GO"))
        {
            queue=new Queue[value];
            continue;
        }
        if(isCommand(command,"CH"))
        {
            currentQ=value;
            continue;
        }
        
        if(isCommand(command,"IN"))
        {
            init(queue[currentQ],value);
            continue;
        }
        
        if(isCommand(command,"EN"))
        {
            bool retBool=enqueue(queue[currentQ],value);
            showBool(retBool);
            continue;
        }
        cout << "wrong argument in test: " << command << endl;
    }
}
