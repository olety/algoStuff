//
//  InefficientInsertBST.h
//  lab8
//
//  Created by Oleksii Kyrylchuk on 5/8/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#ifndef __lab8__InefficientInsertBST__
#define __lab8__InefficientInsertBST__

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

struct Element{
    Element *parent, *left, *right;
    int key;
    std::vector<std::string> words;
};



class InefficientInsertBST {
private:
    Element *root;
    Element* findWord ( Element* node, std::string word );
    Element* findSuccessor ( Element *node);
    Element* initElem( int k, std::string word );
    void addWord( Element* elem, std::string word );
    void clear( Element* node );
    void removeWord ( std::string word );
    void removeWord ( Element* node, std::string word );
    void outWords ( std::vector<std::string> words );
    bool wordOcc ( std::vector<std::string> strings, std::string word );
    bool removeNode ( Element* node );
    
public:
    
    InefficientInsertBST();
    ~InefficientInsertBST();
    void insert( std::string word );
    void outMax ();
    
};
#endif /* defined(__lab8__InefficientInsertBST__) */
