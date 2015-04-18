//
//  main.cpp
//  lab7
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sstream>

using namespace std;

typedef struct Element{
    Element *parent, *left, *right;
    int key,value;
}Element;

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

void showInorder( Element *node ){
    if ( node != NULL ){
        showInorder( node->left );
        showElement( *node );
        showInorder( node->right );
    }
}

void showInorder( BST &tree ){
    showInorder(tree.root);
    cout << endl;
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

bool removeNode ( BST &tree, Element *node , Element& deletedNode) {
    
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
    
    deletedNode = *node;
    
    if ( temp != node ){
        node->key = temp->key;
        node->value = temp->value;
    }
    
    return true;
}


bool removeKey ( BST &tree, int key, Element& elem ) {
    Element *temp = findKey(tree.root, key);
    if ( temp != NULL ){
        removeNode(tree, temp, elem);
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

bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}

int main(){
    string line;
    string command;
    BST *tree = NULL;
    int currentT=0;
    bool retBool;
    int retInt = 0;
    Element *elem = new Element;
    int value1=0, value2=0;
    cout << "START" << endl;
    while(true){
        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }
        
        // copy line on output with exclamation mark
        cout << "!" << line << endl;;
        
        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);
        
        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
        }
        
        
        // zero-argument command
        
        
        if(isCommand(command,"IN"))
        {
            init(tree[currentT]);
            continue;
        }
        
        if(isCommand(command,"SI"))
        {
            showInorder(tree[currentT]);
            continue;
        }
        
        if(isCommand(command,"SP"))
        {
            showPreorder(tree[currentT]);
            continue;
        }
        
        if(isCommand(command,"SQ"))
        {
            showPostorder(tree[currentT]);
            continue;
        }
        
        
        if(isCommand(command,"CL"))
        {
            clear(tree[currentT]);
            continue;
        }
        
        if(isCommand(command,"NN"))
        {
            retInt = numberOfNodes(tree[currentT]);
            showInt(retInt);
            continue;
        }
        
        if(isCommand(command,"HE"))
        {
            retInt = height(tree[currentT]);
            showInt(retInt);
            continue;
        }
        
        // read next argument, one int value
        stream >> value1;
        
        if(isCommand(command,"FK"))
        {
            retBool = findKey(tree[currentT], value1, *elem);
            if ( retBool ){
                showElement(*elem, true, false);
            } else {
                showBool(retBool);
            }
            continue;
        }
        
        if(isCommand(command,"RK"))
        {
            retBool = removeKey(tree[currentT], value1, *elem);
            if ( retBool ){
                showElement(*elem, true, false);
            } else {
                showBool(retBool);
            }
            continue;
        }
        
        if(isCommand(command,"GO"))
        {
            tree = new BST[value1];
            continue;
        }
        
        if(isCommand(command,"CH"))
        {
            currentT = value1;
            continue;
        }
        
        //read 2nd argument
        stream >> value2;
        
        if(isCommand(command,"IE"))
        {
            retBool = insertElem(tree[currentT], value1, value2);
            showBool(retBool);
            continue;
        }
        
        cout << "wrong argument in test: " << command << endl;
    }
    delete elem;
    delete [] tree;
}

















