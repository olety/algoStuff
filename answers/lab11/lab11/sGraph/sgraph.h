//
//  sgraph.h (search graph)
//
//
//  Created by Oleksii Kyrylchuk on 5/28/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#ifndef __sgraph__
#define __sgraph__

#include <stdio.h>
#include <iostream>
#include <float.h>
#include <vector>
#include "mgraph.h"

class sGraph : public mGraph {
private:
    //--------------STUFF-FOR-SORTING-------
    struct int3{
        int a[3];
    };
    std::vector <int3> colors;
    int timeOfVisit;
    void whiten();
    void vDFS( int node );
    //---------------QUEUE---------------
    class Queue {
    private:
        std::vector<int> queue;
        int cnt;
    public:
        Queue( int size );
        ~Queue();
        void enQueue( int a );
        int deQueue();
        void clear();
        bool isQueueEmpty();
    };
    Queue* q;
    //------------END-OF-QUEUE------------
public:
    sGraph( int nodes );
    ~sGraph();
    void simpleBFS( int node );
    void simpleDFS( int node );
};



#endif /* defined(__sgraph__) */
