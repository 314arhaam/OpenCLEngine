//
//  main.cpp
//
//  Created by Parham Abbasi on 3/15/18.
//  Copyright © 2018 Parham Abbasi. All rights reserved.
//
#include <stdio.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <OpenCL/opencl.h>
#define NUM_VALUES 16*16*4
#include "mykernel.cl.h"
#include "hardware.h"
#include "Host.h"

int main(int argc, const char * argv[]) {
    // input data
    // they'll be from a real source in a real problem
    float a[NUM_VALUES] = {1};
    float b[NUM_VALUES] = {2};
    float c[NUM_VALUES] = {};
    
    clock_t begin = clock();
    // create GPU queue
    dispatch_queue_t __queue__ = createQueue();
    // sending data to host
    // data will be proceed through GPU memory within host
    host(__queue__, a, b, c);
    // release queue after using
    dispatch_release(__queue__);
    clock_t end = clock();
    float elapsed_secs1 = float(end - begin) / CLOCKS_PER_SEC;
    std::cout<<"\nGPU time: "<<elapsed_secs1<<" s\n";
    return 0;
}

