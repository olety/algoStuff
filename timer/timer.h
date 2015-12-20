//
//  timer.h
//  lab8
//
//  Created by Oleksii Kyrylchuk on 5/8/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#ifndef __timer__
#define __timer__

#include <iostream>
#include <chrono>

class Timer
{
public:
    Timer();
    void reset();
    double elapsed() const;
private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

#endif /* defined(__timer__) */
