CC = g++
CCFLAGS = -std=c++0x
INCDIR = -I/usr/include/CL
LIBDIR = -L/usr/lib/x86_64-linux-gnu
LIBS = -lOpenCL
RM = rm -rf

BIN = dev_info

all: $(BIN)

dev_info: dev_find.cpp
	$(CC) $(CCFLAGS) $(INCDIR) $(LIBDIR) -o $@ $< $(LIBS)

clean:
	$(RM) $(BIN)
