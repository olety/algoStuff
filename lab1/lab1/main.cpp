
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// size from 2 to 20
/*
 X
 XX
 XXX
 */
void drawTriangle(int size){
    for ( int i = 1; i <= size; i++ ){
        for ( int j = 1; j <= i; j++ ){
            cout << "X";
        }
        cout << endl;
    }
}
// size from 2 to 20
void drawSquare(int size){
    for ( int i = 0 ; i < size; i++ ){
        for ( int j = 0 ; j < size; j++ ){
            if ( i == 0 || i == size - 1 || j == 0 || j == size - 1 ){
                cout << "X";
            } else if ( i != 0 && i != size - 1 ){
                cout << " ";
            }
        }
        cout << endl;
    }
}
// size from 1 to 20
void drawPyramid(int size){
    if ( size == 1 ){
        cout << "X\n";
        return;
    }
    char line [400];
    int i;
    for ( i = 0 ; i < (1 + 2 * size); i++){
        line[i] = ' ';
    }
    line[i] = '\0';
    for ( i = 0; i < size; i++ ){
        line[size - i - 1 ] = 'X';
        line[size + i - 1 ] = 'X';
        cout << line << endl;
    }
}

// supporting func to make drawXmasTree
void drawPyramidPosition(int size, int where, char* line){
    int i;
    if ( size == 1 ){
        for ( i = 0 ; i < where - 1; i++ )
            cout << ' ';
        cout << "X\n";
        return;
    }
    for ( i = 0 ; i < (1 + 2 * size + where); i++){
        line[i] = ' ';
    }
    line[i] = '\0';
    for ( i = 0; i < size; i++ ){
        line[ where - i - 1 ] = 'X';
        line[ where + i - 1 ] = 'X';
        cout << line << endl;
    }
}

// size from 1 to 20
void drawChristmasTree(int size){
    char line [400];
    for ( int i = 1; i <= size; i++ ){
        drawPyramidPosition(i, (1 + 2 * size)/2, line);
    }
}

// size from 2 to 20
void drawFigureX(int size){
}

// size from 2 to 20
void drawFigureY(int size){
}

// size from 3 to 20
void drawFigureZ(int size){
}

// size from 2 to 20
void drawFigureW(int size){
}

bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}

int main(){
    string line;
    string command;
    int value;
    cout << "START" << endl;
    while(true){
        //		cin.getline(line, MAXLINE);
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
        
        // read next argument, one int value
        stream >> value;
        
        if(isCommand(command,"TR"))
        {
            drawTriangle(value);
            continue;
        }
        if(isCommand(command,"SQ"))
        {
            drawSquare(value);
            continue;
        }
        if(isCommand(command,"PY"))
        {
            drawPyramid(value);
            continue;
        }
        if(isCommand(command,"CT"))
        {
            drawChristmasTree(value);
            continue;
        }
        if(isCommand(command,"FX"))
        {
            drawFigureX(value);
            continue;
        }
        if(isCommand(command,"FY"))
        {
            drawFigureY(value);
            continue;
        }
        if(isCommand(command,"FZ"))
        {
            drawFigureZ(value);
            continue;
        }
        if(isCommand(command,"FW"))
        {
            drawFigureW(value);
            continue;
        }
        
        cout << "wrong argument in test: " << command << endl;
    }
    
}
