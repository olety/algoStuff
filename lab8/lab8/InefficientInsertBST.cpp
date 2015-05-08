//
//  InefficientInsertBST.cpp
//  lab8
//
//  Created by Oleksii Kyrylchuk on 5/8/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include "InefficientInsertBST.h"
#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>

InefficientInsertBST::InefficientInsertBST(){
    this->root = NULL;
}

InefficientInsertBST::~InefficientInsertBST(){
    this->clear( this->root );
    delete this;
}
void InefficientInsertBST::outWords( std::vector<std::string> words ){
    for ( int i = 0; i < words.size(); i++ ){
        std::cout << words[i] << std::endl;
    }
}
void InefficientInsertBST::outMax(){
    Element *temp = this->root;
    while ( temp->right != nullptr){
        temp = temp->right;
    }
    std::cout << "Most common words : ";
    outWords( temp->words );
}

void InefficientInsertBST::clear( Element* node ){
    if ( node != NULL ){
        clear( node->left );
        clear( node->right );
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        delete node;
    }
}

void InefficientInsertBST::addWord(Element *elem, std::string word){
    if ( elem == nullptr )
        return;
    
    elem->words.resize(elem->words.size()+1);
    elem->words[elem->words.size()-1] = word;
    
}

bool InefficientInsertBST::wordOcc( std::vector<std::string> strings , std::string word ){
    for ( int i = 0; i < strings.size(); i++ ){
        if ( strings[i] == word ){
            return true;
        }
    }
    return false;
}

Element* InefficientInsertBST::initElem( int k, std::string word){
    Element *elem = new Element;
    elem->words.resize(1);
    elem->key = k;
    elem->words[0] = word;
    elem->left = nullptr;
    elem->right = nullptr;
    elem->parent = nullptr;
    return elem;
}

void InefficientInsertBST::insert( std::string word ){
    //search for a word, then key = 1 if it's not found
    Element* temp2 = this->findWord(this->root, word);
    int k = 1;
    if ( temp2 != nullptr ){
        k = (temp2)->key + 1;
        this->removeWord(temp2,word);
    }
    Element *temp = this->root , *temp_prev = nullptr;
    
    while ( temp != NULL ){
        temp_prev = temp;
        if ( k < temp->key ){
            temp = temp->left;
        } else if ( k > temp->key){
            temp = temp->right;
        } else {
            //k is the same
            break;
        }
    }
    
    if ( temp_prev == temp && this->root != nullptr ){
        this->addWord(this->root, word);
    }
    
    Element *insert = initElem( k , word );
    insert->parent = temp_prev;
    
    if ( this->root == nullptr ){
        this->root = insert;
    } else if ( insert->key > temp_prev->key ) {
        temp_prev->right = insert;
    } else if ( insert->key < temp_prev->key){
        temp_prev->left = insert;
    } else {
        this->addWord(temp_prev, word);
    }
}

Element* InefficientInsertBST::findWord( Element* node, std::string word ){
    if ( node == nullptr ){
        return nullptr;
    }
    
    if ( wordOcc(node->words, word) ){
        return node;
    }
    
    Element *temp1, *temp2;
    
    if ( (temp1 = findWord(node->left, word)) != nullptr){
        return temp1;
    } else {
        return (temp2 = findWord(node->right, word));
    }
    
}

void InefficientInsertBST::removeWord( std::string word ){
    Element *temp = findWord(this->root, word);
    if ( temp->words.size() == 1 ){
        removeNode(temp);
        return;
    }
    for ( int i = 0; i < temp->words.size(); i++ ){
        if ( temp->words[i] == word ){
            temp->words.erase(temp->words.begin()+i);
            return;
        }
    }
    
}
void InefficientInsertBST::removeWord( Element* node, std::string word ){
    if ( node->words.size() == 1 ){
        removeNode(node);
        return;
    }
    for ( int i = 0; i < node->words.size(); i++ ){
        if ( node->words[i] == word ){
            node->words.erase(node->words.begin()+i);
            return;
        }
    }
    
}

Element* InefficientInsertBST::findSuccessor ( Element *node ){
    Element *temp = node->right;
    
    while ( temp->left != NULL ){
        temp = temp->left;
    }
    
    return temp;
}

bool InefficientInsertBST::removeNode ( Element *node ){
    
    if ( node == NULL )
        return false;
    
    Element *temp, *temp2;
    
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
        node->key = temp->key;
        node->words = temp->words;
    }
    
    return true;
    
}
