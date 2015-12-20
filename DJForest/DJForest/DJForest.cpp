//
//  DJForest.cpp
//  lab9
//
//  Created by Oleksii Kyrylchuk on 5/14/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include "DJForest.h"

DJForest::Node::Node(){
    this->parent = this;
    this->data = 0;
    this->rank = 0;
}

DJForest::DJForest( int nodesCnt ){
    this->nodeCnt = nodesCnt;
//    this->nodes.resize(nodesCnt);
    for ( int i = 0; i < nodesCnt; i++ ){
        this->nodes[i] = new DJForest::Node();
        this->nodes[i]->data = i;
    }
}

DJForest::~DJForest( ){
    for ( int i = 0; i < this->nodeCnt; i++ ){
        delete this->nodes[i];
    }
}

DJForest::Node* DJForest::find(Node* n){
    if (n != n->parent) {
        n->parent = find(n->parent);
    }
    return n->parent;
}

void DJForest::merge(Node* x, Node* y)
{
    x = find(x);
    y = find(y);
    
    if (x->rank > y->rank) {
        y->parent = x;
    } else {
        x->parent = y;
        if (x->rank == y->rank) {
            (y->rank)++;
        }
    }
}