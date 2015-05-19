//
//  DJForest.h
//  lab9
//
//  Created by Oleksii Kyrylchuk on 5/14/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#ifndef __lab9__DJForest__
#define __lab9__DJForest__

#include <iostream>
#include <vector>
#include "limits.h"
class DJForest
{
private:
    int nodeCnt;
public:
    class Node {
        public :
        int data;
        int rank;
        Node *parent;
        Node();
    };
//    std::vector<DJForest::Node*> nodes;
    Node* nodes[INT_MAX];
    Node*   find(Node*);
    void   merge(Node*, Node*); // Union
    DJForest( int );
    ~DJForest();
};

#endif /* defined(__lab9__DJForest__) */
