/*
 main.cpp
 lab10
 
 Created by Oleksii Kyrylchuk on 5/19/15.
 Copyright (c) 2015 olety. All rights reserved.
 
 
 Implement graph representation as an adjacency matrix.
 In the tasks vertices a numbered from 0. Any graph is without loops (a loop is an edge form a vertex to this same vertex)
 
 */

#include <iostream>
#include <sstream>
#include <float.h>
#include <vector>

class Graph {
private:
    std::vector <std::vector<double> > nodeMatrix;
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
    Graph( int nodes );
    ~Graph();
    void insertEdge( int node1, int node2, double weight );
    bool findEdge( int node1, int node2, double &weight );
    void showAsMatrix();
    void showAsArray();
    void simpleBFS( int node );
    void simpleDFS( int node );
};

Graph::Graph ( int nodes ){
    this->timeOfVisit = 0;
    this->q = new Queue(nodes);
    this->colors.resize((size_t) nodes);
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

Graph::~Graph (){
    
}

void Graph::insertEdge( int node1, int node2, double weight){
    if ( node1 == node2 || node1 >= this->nodeMatrix.size() || node2 >= this->nodeMatrix.size() )
        return;
    this->nodeMatrix[node1][node2] = weight;
    //    this->nodeMatrix[node2][node1] = weight;
}

bool Graph::findEdge( int node1, int node2, double &weight){
    if ( node1 >= this->nodeMatrix.size() || node2 >= this->nodeMatrix.size()
        || this->nodeMatrix[node1][node2] == DBL_MAX || node1 == node2 )
        return false;
    weight = this->nodeMatrix[node1][node2];
    return true;
}

void Graph::showAsMatrix(){
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

void Graph::showAsArray(){
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

Graph::Queue::Queue( int size ){
    this->queue.resize((size_t) size);
    this->cnt = 0;
}

Graph::Queue::~Queue(){
    
}

void Graph::Queue::enQueue( int a ){
    this->queue[this->cnt++] = a;
}

int Graph::Queue::deQueue(){
    int ret = this->queue[0];
    for ( int i = 0; i < this->cnt; i++) {
        this->queue[i] = this->queue[i+1];
    }
    this->cnt--;
    return ret;
}

bool Graph::Queue::isQueueEmpty(){
    return (this->cnt == 0);
}

void Graph::Queue::clear(){
    while (!this->isQueueEmpty()){
        this->deQueue();
    }
}

void Graph::whiten(){
    this->timeOfVisit = 0;
    for ( int i = 0; i < this->colors.size(); i++ ){
        colors[i].a[0] = 0; // 0 = white; 1 = gray; 2 = black
        colors[i].a[1] = INT_MAX;
    }
}


void Graph::simpleBFS( int node ){ //Breadth-first
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

void Graph::simpleDFS( int node ){ //Depth-first
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

void Graph::vDFS( int node ){
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

bool isCommand( const std::string command, const char *mnemonic ){
    return command==mnemonic;
}

int main(){
    std::string line,command;
    int currentG = 0, i, value1, value2, k;
    double value3;
//    bool retBool = false;
    std::vector<Graph*> g;
    std::cout << "START" << std::endl;
    while(true){
        getline(std::cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }
        
        // copy line on output with exclamation mark
        std::cout << "!" << line << std::endl;
        
        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);
        
        // zero-argument commands
        
        if(isCommand(command,"HA")){ // halt exec
            std::cout << "END OF EXECUTION" << std::endl;
            break;
        }
        
        if(isCommand(command,"SM")){ // Show as a matrix
            g[currentG]->showAsMatrix();
            continue;
        }
        
        if(isCommand(command,"SA")){ // Show as an array of lists
            g[currentG]->showAsArray();
            continue;
        }
        
        // read next argument, one int value
        stream >> value1;
        
        if(isCommand(command,"GO")){ // make x arrays of graphs
            g.resize(value1);
            continue;
        }
        
        if(isCommand(command,"BF")){ // Breadth-first search
            g[currentG]->simpleBFS(value1);
            continue;
        }
        
        if(isCommand(command,"DF")){ // Depth-first search
            g[currentG]->simpleDFS(value1);
            continue;
        }
        
        if(isCommand(command,"CH")){ //choose graph
            currentG = value1;
            continue;
        }
        
        //read 2nd argument
        stream >> value2;
        
        if(isCommand(command,"LG")){ //loadGraph, value1 = nodes, value2 = edges
            g[currentG] = new Graph( value1 );
            k = value2;
            for ( i = 0; i < k; i++ ){
                getline(std::cin,line);
                std::stringstream stream(line);
                stream >> value1 >> value2 >> value3;
                g[currentG]->insertEdge(value1, value2, value3);
            }
            continue;
        }
        
        if(isCommand(command,"FE")){ //findEdge
            if ( !(g[currentG]->findEdge(value1, value2, value3))){ //should it return val, if node1==node2?
                std::cout << "false" << std::endl;
                continue;
            }
            std::cout << value3 << std::endl;
            continue;
        }
        
        //read 3rd argument
        stream >> value3;
        
        if(isCommand(command,"IE")){ //insertEdge
            g[currentG]->insertEdge(value1, value2, value3);
            continue;
        }
        
        std::cout << "wrong argument in test: " << command << std::endl;
    }
}
