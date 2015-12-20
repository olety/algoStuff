//
//  main.cpp
//  lab8
//
//  Created by Oleksii Kyrylchuk on 5/4/15.
//  Copyright (c) 2015 olety. All rights reserved.
//
#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "InefficientInsertBST.h"
#include "timer.h"
#include "EfficientBST.h"

bool getNextWord ( char **line, char* word ){
    if ( **line == '\0' || **line == '\n' ){
        return false;
    }
    
    char a = **line;
    int n = 0;
    
    if ( !isalpha(a) ){
        while ( !isalpha(a) ) {
            (*line)++;
            a = **line;
            if ( **line == '\0' || **line == '\n' ) {
                return false;
            }
        }
    }
        
    while ( isalpha(a) ){
        a = tolower(a);
        *(word+n) = a;
        n++;
        a = *( *(line) + n );
    }
   
    *(word+n) = '\0';
    
    *line += n;
    
    return true;
};
void hasht ( std::vector<std::string> words ){
    std::unordered_map<std::string, int> hash;
    std::unordered_map<std::string, int>::iterator it;
    for ( std::vector<std::string>::const_iterator i = words.begin(); i != words.end(); i++){
        
        if ( (it = hash.find(*i)) != hash.end() ){
            it->second++;
            continue;
        }
        hash[*i] = 1;
    }
    
    int findmax;
    std::cout << "Words with highest occurences : " << std::endl;
    for ( int k = 0; k < 10; k++){
        findmax = 0;
        for ( it = hash.begin(); it != hash.end(); it++){
            if ( it->second > findmax )
                findmax = it->second;
        }
        for ( it = hash.begin(); it != hash.end(); it++){
            if ( it->second == findmax ){
                std::cout << it->first << " ( " << it->second << " ), " ;
                it->second = -1;
            }
        }
    }
    std::cout << std::endl;

}
void rbtree ( std::vector<std::string> words ){
    std::map<std::string, int> tree;
    std::map<std::string, int>::iterator it;
    for ( std::vector<std::string>::const_iterator i = words.begin(); i != words.end(); i++){
        
        if ( (it = tree.find(*i)) != tree.end() ){
            it->second++;
            continue;
        }
        tree[*i] = 1;
    }
    
    int findmax;
    std::cout << "Words with highest occurences : " << std::endl;
    
    for ( int k = 0; k < 10; k++){
        findmax = 0;
        for ( it = tree.begin(); it != tree.end(); it++){
            if ( it->second > findmax )
                findmax = it->second;
        }
        for ( it = tree.begin(); it != tree.end(); it++){
            if ( it->second == findmax ){
                std::cout << it->first << " ( " << it->second << " ), " ;
                it->second = -1;
            }
        }
    }
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    srand(NULL);
    const int LENLINE = 1024;
    FILE *in = fopen("big.txt","r");
    std::vector<std::string> words;
    char *line = new char[LENLINE];
    char *word = new char[512];
    char* temp = line;
    Timer *time = new Timer();
//    BST *tree = new BST();
    EfficientBST *tree1 = new EfficientBST();
    int i;
    std::cout << "Started processing text" << std::endl;
    while ( fgets(line, LENLINE-1, in) != NULL ){
        while ( getNextWord(&line, word)){
               // std::cout << word << endl;
                words.resize(words.size()+1);
                words[words.size()-1] = std::string(word);
        }
        line = temp;
    }
    std::cout << "Ended processing text" << std::endl;
    // Inefficient BST here
    /*
     std::cout << "Started writing into BST" << std::endl;
     for ( i = 0; i < words.size(); i++ ){
     // std::cout << "inserting " << words[i] << std::endl;
     tree->insert(words[i]);
     if ( i == 10000  ){
     std::cout << "inserted " << i << " elements" << std::endl;
     tree->outMax();
     }
     }
     std::cout << "Ended writing into BST" << std::endl;
     tree->outMax();
     */
    std::cout << time->elapsed() << std::endl;
    time->reset();
    std::cout << "Started writing into EfficientBST" << std::endl;
    for ( i = 0; i < words.size(); i++ ){
        // std::cout << "inserting " << words[i] << std::endl;
        tree1->insert(words[i]);
        if ( i % 10000 == 0  ){
         //   std::cout << "inserted " << i << " elements" << std::endl;
          //  tree1->outMax();
        }
    }
    //tree1->outElems();
    std::cout << "Ended writing into EfficientBST" << std::endl;
    tree1->outMax();
    std::cout << "Efficient BST took " << time->elapsed() << " seconds. " << std::endl;
    time->reset();
    rbtree(words);
    std::cout << "Red-Black tree took " << time->elapsed() << " seconds. " << std::endl;
    time->reset();
    hasht(words);
    std::cout << "Hashtable took " << time->elapsed() << " seconds. " << std::endl;
    delete[] temp;
    delete[] word;
    return 0;
}





























