//
//  main.cpp
//  lab5tester
//
//  Created by Oleksii Kyrylchuk on 4/4/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include <iostream>
#include <stdio.h>
using namespace std;
int main(int argc, const char * argv[]) {
    srand(NULL);
    int i;
    cout << "№ of elements to generate" << endl;
    cin >> i;
    int k = 0;
    FILE *out = fopen("out.txt", "w+");
    for ( int j = 0; j < i; j++){
        //int k = rand()/10000;
        k++;
        fprintf(out, "%d\n", k);
    }
    
    cout << "ended generating array" << endl;
    return 0;
}
