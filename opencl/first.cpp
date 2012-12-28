// http://www.codeproject.com/Articles/110685/Part-1-OpenCL-Portable-Parallelism
#include <iostream>

using namespace std;

#define __NO_STD_VECTOR;
#define __NO_STD_STRING;

#include <CL/cl.h>

#define DATA_SIZE (1024*1240)

const char *KernelSource = "\n"         \
    "__kernel void square(          \n" \
    "  __global float* input,       \n" \
    "  __global float* output,      \n" \
    "  const unsigned int count)    \n" \
    "{                              \n" \
    "   int i = get_global_id(0);   \n" \
    "   if (i<count)               \n" \
    "       output[i] = input[i]*input[i]; \n" \
    "}                              \n" \
    "\n";

int main(int argc, char* argv[]) {
    int devType = CL_DEVICE_TYPE_CPU;   // Use CPU
    
    cl_int err;
    size_t global;
    size_t local;
    cl_platform_id cpPlatform;
    cl_device_id device_id;
    cl_context context;
    cl_command_queue commands;
    cl_program program;
    cl_kernel kernel;

    // Connect to compute device
    err = clGetPlatformIDs(1, &cpPlatform, NULL);
    if (err != CL_SUCCESS) {
        cerr << "Error - failed to find platform" << endl;
        return EXIT_FAILURE;
    }

    // Get a device of type devType
    err = clGetDeviceIDs(cpPlatform, devType, 1, &device_id, NULL);
    if (err != CL_SUCCESS) {
        cerr << "Error - failed to get device id" << endl;
        return EXIT_FAILURE;
    }

    context = clCreateContext(0, 1, &device_id, NULL, NULL, &err);
    if (!context) {
        cerr << "Error - failed to create context" << endl;
        return EXIT_FAILURE;
    }

    commands = clCreateCommandQueue(context, device_id, 0, &err);
    if (!commands) {
        cerr << "Error - failed to create command queue" << endl;
        return EXIT_FAILURE;
    }

    program = clCreateProgramWithSource(context, 1, (const char**)&KernelSource, NULL, &err);
    if (!program) {
        cerr << "Error - failed to create program" << endl;
        return EXIT_FAILURE;
    }

    err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        size_t len;
        char buffer[2048];
        cerr << "Error - failed to build program executable" << endl;
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG,
            sizeof(buffer), buffer, &len);
        cerr << buffer << endl;
        return EXIT_FAILURE;
    }

    kernel = clCreateKernel(program, "square", &err);
    if (!kernel) {
        cerr << "Error - failed to create kernel" << endl;
        return EXIT_FAILURE;
    }

    // Create data for the run
    float* data = new float[DATA_SIZE];
    float* results = new float[DATA_SIZE];
    unsigned int correct;
    cl_mem input;
    cl_mem output;

    // Fill vector with random values
    unsigned int count = DATA_SIZE;
    for (int i; i<count; i++) 
        data[i] = rand()/(float)RAND_MAX;

    // Create device memory vectors
    input = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float)*count,
            NULL, NULL);
    output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float)*count,
            NULL, NULL);
    if (!input || !output) {
        cerr << "Failed to allocate device memory" << endl;
        return EXIT_FAILURE;
    }

    // Transfer input vector to device
    err = clEnqueueWriteBuffer(commands, input, CL_TRUE, 0, sizeof(float)*count,
            data, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        cerr << "Could not transfer input to device" << endl;
        return EXIT_FAILURE;
    }

    // Set the arguments to the compute kernel.
    err = 0;
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &input);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &output);
    err |= clSetKernelArg(kernel, 2, sizeof(unsigned int), &count);
    if (err != CL_SUCCESS) {
        cerr << "Failed to set kernel arguments!" << endl;
        return EXIT_FAILURE;
    }

    // Get the maximum work group 
    err = clGetKernelWorkGroupInfo(kernel, device_id, 
        CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL);
    if (err != CL_SUCCESS) {
        cerr << "Could not get work group size " << err << endl;
        return EXIT_FAILURE;
    }

    // Execute the kernel
    global = count;
    err = clEnqueueNDRangeKernel(commands, kernel, 
        1, NULL, &global, &local, 0, NULL, NULL);
    if (err!=CL_SUCCESS) {
        cerr << "Failed to execute kernel!" << endl;
        return EXIT_FAILURE;
    }

    // Wait for all commands to finish
    clFinish(commands);

    // Read back results
    err = clEnqueueReadBuffer(commands, output, 
        CL_TRUE, 0, sizeof(float)*count, results, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        cerr << "Failed to read back results!" << endl;
        return EXIT_FAILURE;
    }

    // Validate
    correct = 0;
    for (int i = 0; i < count; i++) {
        if (results[i] == data[i]*data[i]) {
            correct++;
        }
    }

    cout << "Computed " << correct << " / " << count << " correct values" << endl;
    delete [] data; delete [] results;

    clReleaseMemObject(input);
    clReleaseMemObject(output);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commands);
    clReleaseContext(context);
    return 0;
}
