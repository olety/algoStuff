//
//  spGraph.h
//
//  Created by Oleksii Kyrylchuk on 6/3/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#ifndef __spgraph__
#define __spgraph__

#include "mgraph.h"

class spGraph : public mGraph {
private:
    std::vector<int> getConnections ( int node );
    int minUnvisited ( std::vector<double> paths, std::vector<int> unvisited );
    double getEdge( int node1, int node2 );
public:
    spGraph ( int nodes );
    std::vector<double> sssp ( int node );
    void printSP ( int node );
};

int min ( int int1, int int2 );
bool all0 ( std::vector<int> unvisited );
double min ( double dbl1, double dbl2 );

#endif /* defined(__spGraph__) */
