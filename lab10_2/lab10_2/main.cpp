/*
 main.cpp
 lab10
 
 Created by Oleksii Kyrylchuk on 5/19/15.
 Copyright (c) 2015 olety. All rights reserved.
 
 
 Implement graph representation as an array of lists.
 In the tasks vertices a numbered from 0. Any graph is without loops (a loop is an edge form a vertex to this same vertex)
 
 */

#include <iostream>
#include <sstream>
#include <float.h>
#include <vector>

class Graph {
private:
    struct ElementL{
        ElementL *prev;
        ElementL *next;
        double weight;
        int nodeNum;
    };

    struct List {
        ElementL *head;
    };
    ElementL *initElem ( int nodeNum, double weight, ElementL *prev, ElementL *next );
    int nodeCnt;
    std::vector< List* > nodeArray;
    
public:
    Graph( int nodes );
    ~Graph();
    void insertEdge( int node1, int node2, double weight );
    bool findEdge( int node1, int node2, double &weight );
    bool findEdge( int node1, int node2 );
    void showAsMatrix();
    void showAsArray();
};

Graph::Graph ( int nodes ){
    this->nodeArray.resize((size_t) nodes);
    this->nodeCnt = nodes;
    for ( int i = 0; i < this->nodeCnt; i++ ){
        this->nodeArray[i] = new List;
        this->nodeArray[i]->head = initElem(i, 0., NULL, NULL);
    }
}

Graph::~Graph (){
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

Graph::ElementL *Graph::initElem(int nodeNum, double weight, Graph::ElementL *prev, Graph::ElementL *next ){
    Graph::ElementL *temp = new ElementL;
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

void Graph::insertEdge( int node1, int node2, double weight){
    if ( node1 == node2 || node1 >= this->nodeCnt || node2 >= this->nodeCnt )
        return;
    
    double a;
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

bool Graph::findEdge( int node1, int node2 ){
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

bool Graph::findEdge( int node1, int node2, double &weight){
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

void Graph::showAsMatrix(){
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

void Graph::showAsArray(){
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

bool isCommand(const std::string command,const char *mnemonic){
    return command==mnemonic;
}

int main(){
    std::string line,command;
    int currentG = 0, i, value1, value2, k;
    double value3;
    //    bool retBool = false;
    std::vector<Graph*> g;
   // std::cout << "START" << std::endl;
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
    //    std::cout << "!" << line << std::endl;
        
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
            if ( !(g[currentG]->findEdge(value1, value2, value3))){
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
