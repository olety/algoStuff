//
//  mgraph.h
//  mgraph means matrixGraph :)
//  Created by Oleksii Kyrylchuk on 5/28/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#ifndef __mgraph__
#define __mgraph__

#include <iostream>
#include <vector>
#include <float.h>

class mGraph {
protected:
    std::vector<std::vector<double> > nodeMatrix;
public:
    mGraph( int nodes );
    ~mGraph();
    void insertEdge( int node1, int node2, double weight );
    bool findEdge( int node1, int node2, double &weight );
    void showAsMatrix();
    void showAsArray();
};


#endif /* defined(__mgraph__) */
