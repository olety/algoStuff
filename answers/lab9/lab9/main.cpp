//
//  main.cpp
//  lab9
//
//  Created by Oleksii Kyrylchuk on 5/14/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include <iostream>
#include "DJForest.h"
#include "vector"
#include "timer.h"

int main(int argc, const char * argv[]) {
    const int FOREST_SIZE = 10000000;
    Timer *time = new Timer();
    std::cout << "Started initializing forest with " << FOREST_SIZE << " elements" << std::endl;
    DJForest *djf = new DJForest(FOREST_SIZE);
    std::cout << "Ended initializing forest" << std::endl << "Elapsed time is " << time->elapsed() << " seconds" << std::endl;
    std::cout << "Started uniting" << std::endl;
    time->reset();
    for ( int i = 1; i < FOREST_SIZE; i++ ){
        djf->merge(djf->nodes[i-1], djf->nodes[i]);
    }
    std::cout << "Uniting took " << time->elapsed() << " seconds." << std::endl;
    return 0;
}
