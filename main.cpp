//
//  main.cpp
//  DPM
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
#define NUM_VALUES 262144/2
#include "mykernel.cl.h"
#include "hardware.h"
#include "Host.h"
#include "cpu_code.h"

int init(float *a, float *b, int N){
    for (int i = 0; i < N; i++){
        a[i] = 2*i;
        b[i] = 2*i+1;
    }
    return 0;
}
int main(int argc, const char * argv[]) {
    float a[NUM_VALUES] = {}, b[NUM_VALUES] = {}, gpu[NUM_VALUES] = {}, cpu[NUM_VALUES] = {};
    init(a, b, NUM_VALUES);
    clock_t begin = clock();
    dispatch_queue_t __queue__ = createQueue();
    host(__queue__, a, b, gpu);
    dispatch_release(__queue__);
    clock_t end = clock();
    float elapsed_gpu = float(end - begin) / CLOCKS_PER_SEC;
    std::cout<<"\nGPU time: "<<elapsed_gpu<<" s";
    
    begin = clock();
    cpu_code(a, b, cpu, NUM_VALUES);
    end = clock();
    float elapsed_cpu = float(end - begin) / CLOCKS_PER_SEC;
    
    std::cout<<"\nCPU time: "<<elapsed_cpu<<" s";
    validate(gpu, cpu, NUM_VALUES);
    return 0;
}

