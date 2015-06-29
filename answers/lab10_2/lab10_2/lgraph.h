//
//  lgraph.h
//  linked list graph
//
//  Created by Oleksii Kyrylchuk on 5/28/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#ifndef __lgraph__
#define __lgraph__

#include <iostream>
#include <float.h>
#include <vector>

class lGraph {
private:
    struct ElementL{
        ElementL *prev;
        ElementL *next;
        double weight;
        int nodeNum;
    };
    struct List { ElementL *head; };
    ElementL *initElem ( int nodeNum, double weight, ElementL *prev, ElementL *next );
    int nodeCnt;
    std::vector< List* > nodeArray;
    
public:
    lGraph( int nodes );
    ~lGraph();
    void insertEdge( int node1, int node2, double weight );
    bool findEdge( int node1, int node2, double &weight );
    bool findEdge( int node1, int node2 );
    void showAsMatrix();
    void showAsArray();
};

#endif /* defined(__lgraph__) */
