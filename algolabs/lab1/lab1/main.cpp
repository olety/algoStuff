#include <stdio.h>
#include <string.h>
#include <iostream>
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

// size from 2 to 20, draws empty square
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
void drawfigureX(int size){
}
// size from 2 to 20
void drawfigureY(int size){
}
// size from 3 to 20
void drawfigureZ(int size){
}
// size from 2 to 20
void drawfigureW(int size){
}

int main(){
    const int MAXLINE=100;
    char line[MAXLINE];
    char oneChar;
    int value;
    while(true){
        cin >> oneChar;
        if(oneChar=='#')
        {
            cin.getline(line, MAXLINE);
            continue;
        }
        if(oneChar=='E')
            break;
        // read next argument, one int value
        cin >> value;
        switch(oneChar){
            case 'T': drawTriangle(value); break;
            case 'S': drawSquare(value); break;
            case 'P': drawPyramid(value); break;
            case 'C': drawChristmasTree(value); break;
            case 'X': drawfigureX(value); break;
            case 'Y': drawfigureY(value); break;
            case 'Z': drawfigureZ(value); break;
            case 'W': drawfigureW(value); break;
        }
    }
    cout << "END OF EXECUTION" << endl;
}