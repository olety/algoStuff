//
//  EfficientBST.h
//  lab8
//
//  Created by Oleksii Kyrylchuk on 5/8/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#ifndef __lab8__EfficientBST__
#define __lab8__EfficientBST__

#include <iostream>
#include <string>

struct Element1{
    Element1 *parent, *left, *right;
    std::string word;
    int value;
};

class EfficientBST {
private:
    Element1 *root;
    Element1 *initElem( std::string word );
    void clear( Element1* node );
    void removeKey();
    bool removeNode ( Element1 *node );
    Element1* findSuccessor ( Element1 *node );
    int findMaxVal( Element1 *node );
    void outWordDelValue ( Element1 *node, int val );
    void outAll( Element1 *node );
public:
    
    EfficientBST();
    ~EfficientBST();
    void insert( std::string word );
    void outMax ();
    void outElems ();
    
};

#endif /* defined(__lab8__EfficientBST__) */
