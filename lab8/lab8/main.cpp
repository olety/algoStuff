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

using namespace std;

struct Element{
    Element *parent, *left, *right;
    int key,value;
};

class BST {
    
public:
    Element *root;
    
};

void init( BST &tree ){
    BST *temp = new BST;
    temp->root = NULL;
    tree = *temp;
}

Element* initElem ( int key, int val ){
    Element* elem = new Element;
    elem->left = NULL;
    elem->right = NULL;
    elem->parent = NULL;
    elem->key = key;
    elem->value = val;
    return elem;
}

bool insertElem ( BST &tree, int k , int val ){
    Element *temp = tree.root , *temp_prev = NULL;
    while ( temp != NULL ){
        temp_prev = temp;
        if ( k < temp->key ){
            temp = temp->left;
        } else if ( k > temp->key){
            temp = temp->right;
        } else {
            return false;
        }
    }
    Element *insert = initElem( k , val );
    insert->parent = temp_prev;
    if ( temp_prev == NULL ){
        tree.root = insert;
    } else if ( insert->key > temp_prev->key ) {
        temp_prev->right = insert;
    } else {
        temp_prev->left = insert;
    }
    
    return true;
}
bool insertElem ( BST &tree, Element Elem ){
    return insertElem(tree, Elem.key, Elem.value );
}

void showElement ( int key, int val ){
    cout << key << "(" << val << ")" << ",";
}

void showElement ( int key, int val, bool comma ){
    cout << key << "(" << val << ")";
    if ( comma ){
        cout << ",";
    }
}

void showElement ( Element elem ){
    showElement(elem.key, elem.value);
}

void showElement ( Element elem , bool newl, bool comma ){
    showElement(elem.key, elem.value, comma);
    if ( newl ){
        cout << endl;
    }
}


void showPreorder( Element *node ){
    if ( node != NULL ){
        showElement( *node );
        showPreorder( node->left );
        showPreorder( node->right );
    }
}

void showPreorder( BST &tree ){
    showPreorder(tree.root);
    cout << endl;
}


void showInorder( Element *node ){
    if ( node != NULL ){
        showPreorder( node->left );
        showElement( *node );
        showPreorder( node->right );
    }
}

void showInorder( BST &tree ){
    showInorder(tree.root);
    cout << endl;
}

void showPostorder( Element *node ){
    if ( node != NULL ){
        showPostorder( node->left );
        showPostorder( node->right );
        showElement( *node );
    }
}

void showPostorder( BST &tree ){
    showPostorder(tree.root);
    cout << endl;
}

Element* findKey ( Element *node, int key ) {
    if ( node == NULL ){
        return NULL;
    }
    if ( node->key == key ){
        return node;
    } else if ( node->key > key ){ // node.key > key, key is in the left subtree
        return findKey(node->left, key);
    } else {
        return findKey(node->right, key);
    }
}

bool findKey ( BST &tree, int key,  Element& elem ) {
    Element* temp;
    if ( (temp = findKey(tree.root, key)) != NULL ){
        elem = *temp;
        return true;
    }
    return false;
}

Element *findSuccessor ( Element *node ){
    Element *temp = node->right;
    
    while ( temp->left != NULL ){
        temp = temp->left;
    }
    
    return temp;
}

bool removeNode ( BST &tree, Element *node , Element* deletedNode) {
    
    if ( node == NULL )
        return false;
    
    Element *temp, *temp2;
    
    if ( node->left == NULL || node->right == NULL ){
        temp = node;
    } else {
        temp = findSuccessor(node);
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
        tree.root = temp2;
    } else if ( temp == temp->parent->left ){
        temp->parent->left = temp2;
    } else {
        temp->parent->right = temp2;
    }
    
    deletedNode = node;
    
    if ( temp != node ){
        node->key = temp->key;
        node->value = temp->value;
    }
    
    return true;
}


bool removeKey ( BST &tree, int key, Element& elem ) {
    Element *temp = findKey(tree.root, key);
    Element *temp2;
    if ( temp != NULL ){
        removeNode(tree, temp, temp2);
        elem.key = temp2->key;
        elem.value = temp2->value;
        delete temp2;
        return true;
    }
    return false;
}

void clear ( Element* node ){
    if ( node != NULL ){
        clear( node->left );
        clear( node->right );
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        delete node;
    }
}

void clear ( BST &tree ){
    clear(tree.root);
    tree.root = NULL;
}

void numberOfNodes ( Element *node, int* beforeCnt ){
    if ( node != NULL ){
        (*beforeCnt)++;
        numberOfNodes( node->left, beforeCnt );
        numberOfNodes( node->right, beforeCnt );
    }
}

int numberOfNodes ( BST &tree ){
    int p = 0;
    numberOfNodes(tree.root, &p);
    return p;
}

int max ( int a , int b ){
    if ( a > b ){
        return a;
    }
    return b;
}

int height ( Element *node ){
    if ( node == NULL ){
        return 0;
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return max(leftHeight,rightHeight)+1;
}


int height ( BST &tree ){
    return height(tree.root);
}

void showBool(bool val){
    if(val)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

void showInt ( int a ){
    cout << a << endl;
}

int getNextWord ( char **line, char* word ){
    if ( **line == '\0' ){
        return -1;
    }
    
    char a = **line;
    int n = 0;
    
    if ( !isalpha(a) ){
        while ( !isalpha(a) && ( a != '\0') ) {
            n++;
            a = *( *(line) + n );
        }
        *line += n;
        return 0;
    }
        
    while ( isalpha(a) ){
        a = tolower(a);
        *(word+n) = a;
        n++;
        a = *( *(line) + n );
    }
   
    *(word+n) = '\0';
    
    *line += n;
    
    return 1;
};

int main(int argc, const char * argv[]) {
    ifstream fs;
    std::vector<string> words;
    char *line = new char[100000];
    std::string line1;
    char *word = new char[512];
    char *temp;
    int i = 0;
    fs.open("big.txt", fstream::in);
    if ( fs.is_open() ){
        while ( std::getline(fs, line1) ){
            copy(line1.begin(),line1.end(), line);
            line[line1.size()] = '\0';
            temp = line;
            while ( (i = getNextWord(&temp, word)) != -1){
                if ( i != 0){
                   // std::cout << word << endl;
                    words.resize(words.size()+1);
                    words[words.size()-1] = std::string(word);
                }
            }
        }
    }
    
//    cout << "ending execution" << endl;
    delete[] line;
    delete[] word;
    return 0;
}





























