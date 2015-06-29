//
//  EfficientBST.cpp
//  lab8
//
//  Created by Oleksii Kyrylchuk on 5/8/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include "EfficientBST.h"
#include <iostream>
#include <string>



EfficientBST::EfficientBST(){
    this->root = NULL;
}

EfficientBST::~EfficientBST(){
    this->clear( this->root );
    delete this;
}

Element1* EfficientBST::findSuccessor ( Element1 *node ){
    Element1 *temp = node->right;
    
    while ( temp->left != NULL ){
        temp = temp->left;
    }
    
    return temp;
}
void EfficientBST::clear( Element1* node ){
    if ( node != NULL ){
        clear( node->left );
        clear( node->right );
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        delete node;
    }
}

Element1* EfficientBST::initElem( std::string word){
    Element1 *elem = new Element1;
    elem->word = word;
    elem->value = 1;
    elem->left = nullptr;
    elem->right = nullptr;
    elem->parent = nullptr;
    return elem;
}



void EfficientBST::insert( std::string word ){
    Element1 *temp = this->root , *temp_prev = nullptr;
    while ( temp != NULL ){
        temp_prev = temp;
        if ( strcmp(word.c_str(),temp->word.c_str()) > 0 ){
            temp = temp->right;
        } else if ( strcmp(word.c_str(), temp->word.c_str()) < 0 ){
            temp = temp->left;
        } else {
            temp->value++;
            return;
        }
    }
    
    Element1 *insert = initElem(  word );
    insert->parent = temp_prev;
    
    if ( this->root == nullptr ){
        this->root = insert;
    } else if ( strcmp(word.c_str(),temp_prev->word.c_str()) > 0 ){
        temp_prev->right = insert;
    } else {
        temp_prev->left = insert;
    }
}

bool EfficientBST::removeNode ( Element1 *node ) {
    
    if ( node == NULL )
        return false;
    
    Element1 *temp, *temp2;
    
    if ( node->left == NULL || node->right == NULL ){
        temp = node;
    } else {
        temp = this->findSuccessor(node);
    }
    
    if ( temp->left == NULL ){
        temp2 = temp->right;
    } else {
        temp2 = temp->left;
    }
    
    if ( temp2 != NULL ){
        temp2->parent = temp->parent;
    }
    
    if ( temp->parent == NULL ){
        this->root = temp2;
    } else if ( temp == temp->parent->left ){
        temp->parent->left = temp2;
    } else {
        temp->parent->right = temp2;
    }
    
    
    if ( temp != node ){
        node->word = temp->word;
        node->value = temp->value;
    }
    delete temp;
    return true;
}

int EfficientBST::findMaxVal( Element1* node ){
    if ( node == nullptr )
        return 0;
    if ( node->left == nullptr && node->right == nullptr )
        return node->value;
    
    int maxLeft, maxRight;
    maxLeft = findMaxVal( node->left );
    maxRight = findMaxVal( node->right );
    
    if ( node->value >= maxRight && node->value >= maxLeft ){
        return node->value;
    }   else if ( maxRight >= maxLeft ) {
        return maxRight;
    }
    
    return maxLeft;
    
}

void EfficientBST::outWordDelValue( Element1 *node, int val){
    if ( node == nullptr )
        return;
    this->outWordDelValue(node->left, val);
    this->outWordDelValue(node->right, val);
    if ( node->value == val ){
        std::cout << node->word << " ( " << val << " )"<< ", " ;
        node->value = 0;
    }
}
void EfficientBST::outAll(Element1 *node){
    if ( node != nullptr ){
        
        std::cout << node->word << " ( " << node->value << " ) " << std::endl;
        outAll(node->left);
        outAll(node->right);
    }
    
}
void EfficientBST::outMax() {
    int max;
    std::cout << "Words with highest occurences : " << std::endl;
    for ( int i = 0; i < 10; i++ )
    {
        max = findMaxVal(this->root);
        this->outWordDelValue( this->root, max );
        max = 0;
    }
    std::cout << std::endl;
}

void EfficientBST::outElems() {
    outAll(this->root);
}
