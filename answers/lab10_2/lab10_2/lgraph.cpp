//
//  lgraph.cpp
//  lab10_2
//
//  Created by Oleksii Kyrylchuk on 5/28/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include "lgraph.h"

lGraph::lGraph ( int nodes ){
    this->nodeArray.resize((size_t) nodes);
    this->nodeCnt = nodes;
    for ( int i = 0; i < this->nodeCnt; i++ ){
        this->nodeArray[i] = new List;
        this->nodeArray[i]->head = initElem(i, 0., NULL, NULL);
    }
}

lGraph::~lGraph (){
    ElementL *temp,*temp_prev;
    for ( int i = 0; i < this->nodeCnt; i++ ){
        temp = nodeArray[i]->head;
        while ( temp != NULL ){
            temp_prev = temp;
            temp = temp->next;
            delete temp_prev;
        }
        delete nodeArray[i];
    }
}

lGraph::ElementL *lGraph::initElem(int nodeNum, double weight, lGraph::ElementL *prev, lGraph::ElementL *next ){
    lGraph::ElementL *temp = new ElementL;
    temp->nodeNum = nodeNum;
    temp->weight = weight;
    temp->next = next;
    temp->prev = prev;
    if ( (temp->next) )
        temp->next->prev = temp;
    if ( (temp->prev) )
        temp->prev->next = temp;
    return temp;
}

void lGraph::insertEdge( int node1, int node2, double weight){
    if ( node1 == node2 || node1 >= this->nodeCnt || node2 >= this->nodeCnt )
        return;
    
    ElementL *temp = this->nodeArray[node1]->head->next, *temp_prev = this->nodeArray[node1]->head;
    
    while ( temp != NULL && temp->nodeNum > node2 ){
        temp_prev = temp;
        temp = temp->next;
    }
    
    if ( temp == NULL ){
        initElem(node2, weight, temp_prev, temp);
        return;
    } else if ( node2 > temp->nodeNum ){
        initElem(node2, weight, temp, temp->next);
        return;
    }
    
    temp->weight = weight;
    
    
}

bool lGraph::findEdge( int node1, int node2 ){
    ElementL *temp = this->nodeArray[node1]->head;
    
    if ( node1 == node2 || temp->next->nodeNum > node2 )
        return false;
    
    do {
        if ( temp->nodeNum == node2 ){
            return true;
        }
        temp = temp->next;
    } while (temp != NULL);
    
    return false;
}

bool lGraph::findEdge( int node1, int node2, double &weight){
    ElementL *temp = this->nodeArray[node1]->head;
    
    if ( node1 == node2 || temp->next->nodeNum > node2 )
        return false;
    
    do {
        if ( temp->nodeNum == node2 ){
            weight = temp->weight;
            return true;
        }
        temp = temp->next;
    } while (temp != NULL);
    
    return false;
}

void lGraph::showAsMatrix(){
    ElementL *temp;
    for ( int i = 0; i < this->nodeCnt; i++ ){
        temp = this->nodeArray[i]->head->next;
        for (int j = 0; j < this->nodeCnt; j++ ){
            if ( temp == NULL || j < temp->nodeNum ){
                if ( i == j ){
                    std::cout << "0,";
                    continue;
                }
                std::cout << "-,";
            } else {
                std::cout << temp->weight << ",";
                temp = temp->next;
            }
        }
        std::cout << std::endl;
    }
}

void lGraph::showAsArray(){
    ElementL *temp;
    for ( int i = 0; i < (int) this->nodeArray.size(); i++ ){
        std::cout << i << ":";
        temp = this->nodeArray[i]->head->next;
        while ( temp != NULL ){
            std::cout << temp->nodeNum << "(" << temp->weight << ")" << ",";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
}