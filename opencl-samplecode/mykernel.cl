
// Simple OpenCL kernel that squares an input array.
// This code is stored in a file called mykernel.cl.
// You can name your kernel file as you would name any other
// file.  Use .cl as the file extension for all kernel
// source files.

// Kernel block.                                      //   1
kernel void square(                                   //   2
                   global float* input1,               //   3
                   global float* input2,
                   global float* output,
                   const int NUM)
{
    size_t i = get_global_id(0);
    float S;
    if (i < NUM){
        S = 0;
        for (int i=0; i<NUM; i++){
            S += input2[i];
        }
    output[i] = input1[i]*S + input2[i];
    }
    //printf("input %f output %f\n", input[i], output[i]);
}
