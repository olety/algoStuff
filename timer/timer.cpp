//
//  timer.cpp
//  lab8
//
//  Created by Oleksii Kyrylchuk on 5/8/15.
//  Copyright (c) 2015 olety. All rights reserved.
//

#include "timer.h"
#include <iostream>
#include <chrono>


Timer::Timer(){
    this->beg_ = clock_::now();
}

void Timer::reset() { beg_ = clock_::now(); }

double Timer::elapsed() const {
    return std::chrono::duration_cast<second_>(clock_::now() - beg_).count();
}

