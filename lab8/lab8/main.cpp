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

using namespace std;

struct Element{
    Element *parent, *left, *right;
    int key;
    std::vector<std::string> words;
};


class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return chrono::duration_cast<second_>
        (clock_::now() - beg_).count(); }
    
private:
    typedef chrono::high_resolution_clock clock_;
    typedef chrono::duration<double, std::ratio<1> > second_;
    chrono::time_point<clock_> beg_;
};

class BST {
private:
    Element *root;
    Element* findWord ( Element* node, std::string word );
    Element* findSuccessor ( Element *node);
    Element* initElem( int k, std::string word );
    void addWord( Element* elem, std::string word );
    void clear( Element* node );
    void removeWord ( std::string word );
    void removeWord ( Element* node, std::string word );
    void outWords ( std::vector<std::string> words );
    bool wordOcc ( std::vector<std::string> strings, std::string word );
    bool removeNode ( Element* node );
    
public:
    
    BST();
    ~BST();
    void insert( std::string word );
    void outMax ();
    
};

BST::BST(){
    this->root = NULL;
}

BST::~BST(){
    this->clear( this->root );
    delete this;
}
void BST::outWords( std::vector<std::string> words ){
    for ( int i = 0; i < words.size(); i++ ){
        std::cout << words[i] << std::endl;
    }
}
void BST::outMax(){
    Element *temp = this->root;
    while ( temp->right != nullptr){
        temp = temp->right;
    }
    std::cout << "Most common words : ";
    outWords( temp->words );
}

void BST::clear( Element* node ){
    if ( node != NULL ){
        clear( node->left );
        clear( node->right );
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        delete node;
    }
}

void BST::addWord(Element *elem, std::string word){
    if ( elem == nullptr )
        return;
    
    elem->words.resize(elem->words.size()+1);
    elem->words[elem->words.size()-1] = word;
    
}

bool BST::wordOcc( std::vector<std::string> strings , std::string word ){
    for ( int i = 0; i < strings.size(); i++ ){
        if ( strings[i] == word ){
            return true;
        }
    }
    return false;
}

Element* BST::initElem( int k, std::string word){
    Element *elem = new Element;
    elem->words.resize(1);
    elem->key = k;
    elem->words[0] = word;
    elem->left = nullptr;
    elem->right = nullptr;
    elem->parent = nullptr;
    return elem;
}

void BST::insert( std::string word ){
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

Element* BST::findWord( Element* node, std::string word ){
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

void BST::removeWord( std::string word ){
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
void BST::removeWord( Element* node, std::string word ){
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

Element* BST::findSuccessor ( Element *node ){
    Element *temp = node->right;
    
    while ( temp->left != NULL ){
        temp = temp->left;
    }
    
    return temp;
}

bool BST::removeNode ( Element *node ){
    
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

struct Element1{
    Element1 *parent, *left, *right;
    std::string word;
    int value;
};

class BST1 {
private:
    Element1 *root;
    Element1 *initElem( std::string word );
    void clear( Element1* node );
    void removeKey();
    bool removeNode ( Element1 *node );
    Element1* findSuccessor ( Element1 *node );
    int findMaxVal( Element1 *node );
    void outWordDelValue ( Element1 *node, int val );
    void outAll( Element1 *node );
public:
    
    BST1();
    ~BST1();
    void insert( std::string word );
    void outMax ();
    void outElems ();
    
};

BST1::BST1(){
    this->root = NULL;
}

BST1::~BST1(){
    this->clear( this->root );
    delete this;
}

Element1* BST1::findSuccessor ( Element1 *node ){
    Element1 *temp = node->right;
    
    while ( temp->left != NULL ){
        temp = temp->left;
    }
    
    return temp;
}
void BST1::clear( Element1* node ){
    if ( node != NULL ){
        clear( node->left );
        clear( node->right );
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        delete node;
    }
}

Element1* BST1::initElem( std::string word){
    Element1 *elem = new Element1;
    elem->word = word;
    elem->value = 1;
    elem->left = nullptr;
    elem->right = nullptr;
    elem->parent = nullptr;
    return elem;
}



void BST1::insert( std::string word ){
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

bool BST1::removeNode ( Element1 *node ) {
    
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

int BST1::findMaxVal( Element1* node ){
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

void BST1::outWordDelValue( Element1 *node, int val){
    if ( node == nullptr )
        return;
    this->outWordDelValue(node->left, val);
    this->outWordDelValue(node->right, val);
    if ( node->value == val ){
        std::cout << node->word << " ( " << val << " )"<< ", " ;
        node->value = 0;
    }
}
void BST1::outAll(Element1 *node){
    if ( node != nullptr ){
        
        cout << node->word << " ( " << node->value << " ) " << std::endl;
        outAll(node->left);
        outAll(node->right);
    }
    
}
void BST1::outMax() {
    int max;
    std::cout << "Words with highest occurences : " ;
    for ( int i = 0; i < 10; i++ )
    {
        max = findMaxVal(this->root);
        this->outWordDelValue( this->root, max );
        max = 0;
    }
    std::cout << std::endl;
}

void BST1::outElems() {
    outAll(this->root);
}

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
    std::vector<string> words;
    char *line = new char[LENLINE];
    char *word = new char[512];
    char* temp = line;
    Timer *time = new Timer();
//    BST *tree = new BST();
    BST1 *tree1 = new BST1();
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
    cout << time->elapsed() << endl;
    time->reset();
    std::cout << "Started writing into BST1" << std::endl;
    for ( i = 0; i < words.size(); i++ ){
        // std::cout << "inserting " << words[i] << std::endl;
        tree1->insert(words[i]);
        if ( i % 10000 == 0  ){
         //   std::cout << "inserted " << i << " elements" << std::endl;
          //  tree1->outMax();
        }
    }
    //tree1->outElems();
    std::cout << "Ended writing into BST1" << std::endl;
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





























