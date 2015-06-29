//
//  node.cpp
//  lab9
//
//  Created by Oleksii Kyrylchuk on 5/14/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include "DJFnode.h"


Node::Node(){
    this->parent = this;
    this->data = 0;
    this->rank = 0;
}