#ifndef hardware_h
#define hardware_h

dispatch_queue_t createQueue(){
	char name[128];
	dispatch_queue_t queue =
	gcl_create_dispatch_queue(CL_DEVICE_TYPE_GPU, NULL);
	if (queue == NULL) {
			queue = gcl_create_dispatch_queue(CL_DEVICE_TYPE_CPU, NULL);
	}
	cl_device_id gpu = gcl_get_device_id_with_dispatch_queue(queue);
	clGetDeviceInfo(gpu, CL_DEVICE_NAME, 128, name, NULL);
	fprintf(stdout, "GPU Hardware:\t%s\n", name);
	return queue;
}

#endif
