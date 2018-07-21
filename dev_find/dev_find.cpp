#include <CL/cl.h>
#include <iostream>
#include <vector>

#define MAX_PLATFORMS 100

const char* pcc_attName[] = { "Name", "Vendor", "Version", "Profile", "Extensions" };
const cl_platform_info pcc_attType[] = { 
                                        CL_PLATFORM_NAME, 
                                        CL_PLATFORM_VENDOR,
                                        CL_PLATFORM_VERSION, 
                                        CL_PLATFORM_PROFILE, 
                                        CL_PLATFORM_EXTENSIONS };

cl_uint get_all_cl_devices(cl_platform_id *c_plat_id)
{
    cl_uint c_nPlatforms;
    int ret = clGetPlatformIDs(MAX_PLATFORMS, c_plat_id, &c_nPlatforms);
    return c_nPlatforms;
}

void print_cl_platform_info(cl_platform_id *pc_plat, cl_uint c_nPlatforms)
{
    for(int i=0;i<c_nPlatforms;i++)
    {
        for(int j=0;j<sizeof(pcc_attName)/sizeof(pcc_attName[0]);j++)
        {
            long unsigned int i_infoSizeBytes;
            clGetPlatformInfo(pc_plat[i], pcc_attType[j], 0, NULL, &i_infoSizeBytes);
            char *pc_info = (char *)malloc(i_infoSizeBytes);
            clGetPlatformInfo(pc_plat[i], pcc_attType[j], i_infoSizeBytes, pc_info, NULL);
            std::cout   << "INFO:\t\t Platform: " << i << "\t"
                        << pcc_attName[j] << ": " << pc_info << "\n";
        }
    }

}

int main(void) 
{
    cl_platform_id c_plat_id[MAX_PLATFORMS];
    int i_nPlatforms = (int)get_all_cl_devices(c_plat_id);
    std::cout << "Number of platforms: " << i_nPlatforms << "\n";
    print_cl_platform_info(c_plat_id, (cl_uint)i_nPlatforms);
    return 0;
}
