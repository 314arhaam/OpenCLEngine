#pragma OPENCL EXTENSION cl_khr_fp64 : enable
/*
    write in-house kernel functions like this:

float CL_sqrt(float x){
    float root = x, error, absError = 1e-3;
    do{
        error = (root*root - x)/(2*root);
        root -= error;
    } while (error < -absError || error > +absError);
    return root;
}
*/

// Kernel block.
kernel void square(
                   global float* __x__,
                   global float* __y__,
                   global float* __z__,
                   const int NUM)
{
    int i = get_global_id(0);
    if (i < NUM){
      __z__[i] = __x__[i] + __y__[i];
    }
}
