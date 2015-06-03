//
//  spGraph.cpp
//
//  Created by Oleksii Kyrylchuk on 6/3/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include "spgraph.h"

double spGraph::getEdge( int node1, int node2){
    return this->nodeMatrix[node1][node2];
}

std::vector<int> spGraph::getConnections( int node ){
    std::vector<int> connections;
    int k = 0;
    for ( int i = 0; i < this->nodeMatrix.size(); i++ ){
        if ( this->getEdge(node, i) != DBL_MAX ){
            connections.resize(connections.size()+1);
            connections[k++] = i;
        }
    }
    return connections;
}

int min ( int int1, int int2 ){
    return (int1 < int2) ? int1 : int2;
}

double min ( double dbl1, double dbl2 ){
    return (dbl1 < dbl2) ? dbl1 : dbl2;
}

int spGraph::minUnvisited( std::vector<double> paths, std::vector<int> unvisited ){
    double pathMin = DBL_MAX;
    int min = 0;
    for ( int i = 0; i < paths.size(); i++ ){
        if ( unvisited[i] && paths[i] < pathMin ){
            pathMin = paths[i];
            min = i;
        }
    }
    return min;
}

bool all0 ( std::vector<int> unvisited ){
    for ( int i = 0; i < unvisited.size(); i++ ){
        if ( unvisited[i] != 0 )
            return false;
    }
    return true;
}

std::vector<double> spGraph::sssp ( int node ){
    std::vector<double> paths(this->nodeMatrix.size());
    std::vector<int> connections, unvisited(this->nodeMatrix.size());
    int i, cur_node;
    for ( i = 0; i < paths.size(); i++ ){
        paths[i] = DBL_MAX;
        unvisited[i] = 1;
    }
    paths[node] = 0;
    
    cur_node = node;
    
    while ( !all0(unvisited) ){
    
        connections = this->getConnections(cur_node);
        
        for ( i = 0; i < connections.size(); i++ ){
            if ( unvisited[connections[i]] ){
                paths[connections[i]] = min(this->getEdge( cur_node, connections[i] ) + paths[cur_node],
                                            paths[connections[i]]);
            }
        }
        unvisited[cur_node] = 0;
        cur_node = this->minUnvisited( paths, unvisited );
    }
   
    return paths;
}

void spGraph::printSP( int node ){
    std::vector<double> paths = this->sssp( node );
    for ( int i = 0; i < paths.size(); i++ )
        std::cout << i << "(" << paths[i] << ")" << std::endl;
}

spGraph::spGraph ( int nodes ) : mGraph( nodes ){
}

