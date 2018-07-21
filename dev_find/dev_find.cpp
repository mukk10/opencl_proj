#include <CL/cl.h>
#include <iostream>
#include <vector>

#define MAX_PLATFORMS 100
#define MAX_DEVICES 100

const char *gpcc_platAtt[] = { "Name", "Vendor", "Version", "Profile", "Extensions" };
const cl_platform_info gpcc_platAttType[] = { 
                                        CL_PLATFORM_NAME, 
                                        CL_PLATFORM_VENDOR,
                                        CL_PLATFORM_VERSION, 
                                        CL_PLATFORM_PROFILE, 
                                        CL_PLATFORM_EXTENSIONS };

const char *gpcc_devAtt[] = { "Name", "Global-Mem", "Local-Mem", "Max-Workgroup", 
                                "Max-Compute-Units", "Max-Workitem-dim" };
const cl_device_info gpcc_devAttType[] = {
                                        CL_DEVICE_NAME,
                                        CL_DEVICE_GLOBAL_MEM_SIZE,
                                        CL_DEVICE_LOCAL_MEM_SIZE,
                                        CL_DEVICE_MAX_WORK_GROUP_SIZE,
                                        CL_DEVICE_MAX_COMPUTE_UNITS,
                                        CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS };

int get_all_cl_devices(cl_platform_id pc_plat, cl_device_id *c_dev_id)
{
    cl_uint c_nDevices = 0;
    int ret = clGetDeviceIDs(pc_plat, CL_DEVICE_TYPE_ALL, MAX_DEVICES, c_dev_id, &c_nDevices);
    return c_nDevices;
}

void print_cl_device_info(cl_device_id pc_dev)
{
    long unsigned int i_infoSizeBytes;
    clGetDeviceInfo(pc_dev, gpcc_devAttType[0], 0, NULL, &i_infoSizeBytes);
    char *pc_info = (char *)malloc(i_infoSizeBytes);
    clGetDeviceInfo(pc_dev, gpcc_devAttType[0], i_infoSizeBytes, pc_info, &i_infoSizeBytes);
    std::cout   << "INFO:\t" << gpcc_devAtt[0] << ": " << pc_info << "\n";
    
    for(int i=1;i<sizeof(gpcc_devAtt)/sizeof(gpcc_devAtt[0]);i++)
    {
        clGetDeviceInfo(pc_dev, gpcc_devAttType[i], 0, NULL, &i_infoSizeBytes);
        unsigned long int pi_info; 
        clGetDeviceInfo(pc_dev, gpcc_devAttType[i], i_infoSizeBytes, &pi_info, NULL);
        std::cout   << "INFO:\t" << gpcc_devAtt[i] << ": " << pi_info << "\n";
     }
}

cl_uint get_all_cl_platforms(cl_platform_id *c_plat_id)
{
    cl_uint c_nPlatforms;
    int ret = clGetPlatformIDs(MAX_PLATFORMS, c_plat_id, &c_nPlatforms);
    return c_nPlatforms;
}

void print_cl_platform_info(cl_platform_id pc_plat)
{
   for(int i=0;i<sizeof(gpcc_platAtt)/sizeof(gpcc_platAtt[0]);i++)
   {
       long unsigned int i_infoSizeBytes;
       clGetPlatformInfo(pc_plat, gpcc_platAttType[i], 0, NULL, &i_infoSizeBytes);
       char *pc_info = (char *)malloc(i_infoSizeBytes);
       clGetPlatformInfo(pc_plat, gpcc_platAttType[i], i_infoSizeBytes, pc_info, NULL);
       std::cout   << "INFO:\t" << gpcc_platAtt[i] << ": " << pc_info << "\n";
    }
}

int main(void) 
{
    cl_platform_id c_plat_id[MAX_PLATFORMS];
    int i_nPlatforms = (int)get_all_cl_platforms(c_plat_id);
    std::cout << "INFO:\tNumber of platforms: " << i_nPlatforms << "\n";
    for(int i=0;i<i_nPlatforms;i++)
    {
        std::cout << "#####################\n";
        std::cout << "Platform number: " << i << "\n";
        print_cl_platform_info(c_plat_id[i]);
        cl_device_id c_device_id[MAX_DEVICES];
        int i_nDevices = (int)get_all_cl_devices(c_plat_id[i], c_device_id);
        std::cout << "INFO:\tNumber of devices: " << i_nDevices << "\n";
        for(int j=0;j<i_nDevices;j++)
        {
            std::cout << "---- Device number: " << j << " ----\n";
            print_cl_device_info(c_device_id[j]);
        }
        std::cout << "\n\n";
    }
    return 0;
}
