//
//  cpu_code.h
//  OpenCLEngine
//
//  Created by Parham Abbasi on 4/15/18.
//  Copyright © 2018 Parham Abbasi. All rights reserved.
//

#ifndef cpu_code_h
#define cpu_code_h

int cpu_code(float *a, float *b, float *c, int N){
    float sum;
    for (int i = 0; i < N; i++){
        sum = 0;
        for (int j = i; j < N; j++){
            sum += b[j];
        }
        c[i] = a[i] + sum;
    }
    return 0;
}

int validate(float *gpu, float* cpu, int N){
    for (int i = 0; i < N; i++){
        if (gpu[i] != cpu[i]){
            printf("\nelement %d value is not same.", i);
            return 1;
        }
    }
    printf("\nresults are validate.\n");
    return 0;
}
#endif /* cpu_code_h */
