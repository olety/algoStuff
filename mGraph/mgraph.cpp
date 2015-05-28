//
//  mGraph.cpp
//  lab10
//
//  Created by Oleksii Kyrylchuk on 5/28/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include "mgraph.h"

mGraph::mGraph ( int nodes ){
    this->nodeMatrix.resize((size_t) nodes);
    for ( int i = 0; i < nodes; i++ ){
        this->nodeMatrix[i].resize((size_t) nodes);
        for ( int j = 0; j < nodes; j++ ){
            if ( i == j ){
                this->nodeMatrix[i][j] = 0;
                continue;
            }
            this->nodeMatrix[i][j] = DBL_MAX;
        }
    }
}

mGraph::~mGraph (){
    
}

void mGraph::insertEdge( int node1, int node2, double weight){
    if ( node1 == node2 || node1 >= this->nodeMatrix.size() || node2 >= this->nodeMatrix.size() )
        return;
    this->nodeMatrix[node1][node2] = weight;
    //    this->nodeMatrix[node2][node1] = weight;
}

bool mGraph::findEdge( int node1, int node2, double &weight){
    if ( node1 >= this->nodeMatrix.size() || node2 >= this->nodeMatrix.size()
        || this->nodeMatrix[node1][node2] == DBL_MAX || node1 == node2 )
        return false;
    weight = this->nodeMatrix[node1][node2];
    return true;
}

void mGraph::showAsMatrix(){
    for ( int i = 0; i < (int) this->nodeMatrix.size(); i++ ){
        for ( int j = 0; j < (int) this->nodeMatrix.size(); j++ ){
            if ( this->nodeMatrix[i][j] == DBL_MAX ){
                std::cout << "-," ;
                continue;
            }
            std::cout << this->nodeMatrix[i][j] << ",";
        }
        std::cout << std::endl;
    }
}

void mGraph::showAsArray(){
    for ( int i = 0; i < (int) this->nodeMatrix.size(); i++ ){
        std::cout << i << ":";
        for ( int j = 0; j < (int) this->nodeMatrix.size(); j++ ){
            if ( this->nodeMatrix[i][j] == DBL_MAX || i == j){
                continue;
            }
            std::cout << j << "(" << this->nodeMatrix[i][j] << ")" << ",";
        }
        std::cout << std::endl;
    }
}