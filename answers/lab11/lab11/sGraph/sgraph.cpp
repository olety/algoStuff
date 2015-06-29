//
//  searchGraph.cpp
//  lab11
//
//  Created by Oleksii Kyrylchuk on 5/28/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include "sgraph.h"


sGraph::sGraph ( int nodes ) : mGraph(nodes) {
    this->timeOfVisit = 0;
    this->q = new Queue(nodes);
    this->colors.resize((size_t) nodes);
}

sGraph::~sGraph (){
    
}

sGraph::Queue::Queue( int size ){
    this->queue.resize((size_t) size);
    this->cnt = 0;
}

sGraph::Queue::~Queue(){
    
}

void sGraph::Queue::enQueue( int a ){
    this->queue[this->cnt++] = a;
}

int sGraph::Queue::deQueue(){
    int ret = this->queue[0];
    for ( int i = 0; i < this->cnt; i++) {
        this->queue[i] = this->queue[i+1];
    }
    this->cnt--;
    return ret;
}

bool sGraph::Queue::isQueueEmpty(){
    return (this->cnt == 0);
}

void sGraph::Queue::clear(){
    while (!this->isQueueEmpty()){
        this->deQueue();
    }
}

void sGraph::whiten(){
    this->timeOfVisit = 0;
    for ( int i = 0; i < this->colors.size(); i++ ){
        colors[i].a[0] = 0; // 0 = white; 1 = gray; 2 = black
        colors[i].a[1] = INT_MAX;
    }
}

void sGraph::simpleBFS( int node ){ //Breadth-first
    //    We don't use weight and sort nodes by their numbers
    this->whiten();
    //    this->showAsMatrix();
    std::cout << node << ",";
    this->colors[node].a[0] = 1;
    this->colors[node].a[1] = 0;
    this->q->enQueue(node);
    int tempNode,i;
    while ( !this->q->isQueueEmpty()){
        tempNode = this->q->deQueue();
        for ( i = 0; i < this->nodeMatrix.size(); i++ ){
            if ( this->nodeMatrix[tempNode][i] != DBL_MAX && tempNode != i && this->colors[i].a[0] == 0 ){
                this->colors[i].a[0] = 1; //gray it
                this->colors[i].a[1] = this->colors[tempNode].a[1] + 1;
                this->q->enQueue(i);
                std::cout << i << ",";
            }
        }
        this->colors[tempNode].a[0] = 2;
    }
    std::cout << std::endl;
}

void sGraph::vDFS( int node ){
    std::cout << node << ",";
    this->colors[node].a[0] = 1;
    this->colors[node].a[1] = ++this->timeOfVisit;
    for ( int i = 0; i < this->nodeMatrix.size(); i++ ){
        if ( this->nodeMatrix[node][i] != DBL_MAX && node != i && this->colors[i].a[0] == 0 ){
            vDFS(i);
        }
    }
    this->colors[node].a[0] = 2;
    this->colors[node].a[2] = ++this->timeOfVisit;
}

void sGraph::simpleDFS( int node ){ //Depth-first
    // We don't use weight and sort nodes by their numbers
    this->whiten();
    colors[node].a[0] = 2;
    std::cout << node << ",";
    for ( int i = 0; i < this->nodeMatrix.size(); i++ ){
        if ( this->nodeMatrix[node][i] != DBL_MAX && node != i && this->colors[i].a[0] == 0 ){
            vDFS(i);
        }
    }
    std::cout << std::endl;
}


