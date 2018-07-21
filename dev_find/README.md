# Find all Devices

Find and display all OpenCL conformant devices on the system.

:copyright: All rights reserved by the author and the respective
owners of the software. No guarantees of any kind, nor the author
is responsible for any use of this software. 

## Build
```
g++ -std=c++0x -L/usr/lib/x86_64-linux-gnu -I/usr/include/CL -o dev_info dev_find.cpp -lOpenCL
```
