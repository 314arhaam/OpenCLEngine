#ifndef Host_h
#define Host_h
int host(
         dispatch_queue_t queue,
         float* test_x,
         float* test_y,
         float* test_z
         ){
    void* mem_x  = gcl_malloc(sizeof(cl_float) * NUM_VALUES, test_x,
                              CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR);
    void* mem_y  = gcl_malloc(sizeof(cl_float) * NUM_VALUES, test_y,
                              CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR);
    void* mem_z  = gcl_malloc(sizeof(cl_float) * NUM_VALUES, test_z,
                              CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR);
    dispatch_sync(queue, ^{
        // Although we could pass NULL as the workgroup size, which would tell
        // OpenCL to pick the one it thinks is best, we can also ask
        // OpenCL for the suggested size, and pass it ourselves.
        size_t wgs;
        gcl_get_kernel_block_workgroup_info(square_kernel,
                                            CL_KERNEL_WORK_GROUP_SIZE,
                                            sizeof(wgs), &wgs, NULL);
        
        // The N-Dimensional Range over which we'd like to execute our
        // kernel.  In this case, we're operating on a 1D buffer, so
        // it makes sense that the range is 1D.
        cl_ndrange range = {                                              // 6
            1,                     // The number of dimensions to use.
            
            {0, 0, 0},             // The offset in each dimension.  To specify
            // that all the data is processed, this is 0
            // in the test case.                   // 7
            
            {NUM_VALUES, 0, 0},    // The global range—this is how many items
            // IN TOTAL in each dimension you want to
            // process.
            
            {wgs, 0, 0}            // The local size of each workgroup.  This
            // determines the number of work items per
            // workgroup.  It indirectly affects the
            // number of workgroups, since the global
            // size / local size yields the number of
            // workgroups.  In this test case, there are
            // NUM_VALUE / wgs workgroups.
        };
        square_kernel(&range, (cl_float*)mem_x,
                      (cl_float*)mem_y,
                      (cl_float*)mem_z,
                      NUM_VALUES);
        gcl_memcpy(test_z, mem_z, sizeof(cl_float) * NUM_VALUES);
    });
    gcl_free(mem_x);
    gcl_free(mem_y);
    gcl_free(mem_z);
    return 0;
}
#endif
