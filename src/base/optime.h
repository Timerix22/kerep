#pragma once

#include "std.h"

#define __optime_print(opname, t)\
    char tnames[3][3]={"s\0","ms","us"};\
    int tni=0;\
    if(t>1000000){\
        t/=1000000;\
        tni=0;\
    } else if(t>1000){\
        t/=1000;\
        tni=1;\
    } else tni=2;\
    kprintf("\e[93moperation \e[94m%s\e[93m lasted \e[94m%f \e[93m%s\n",\
                                    opname,              t,  tnames[tni]);

#ifdef CLOCK_REALTIME 
/// executes codeblock and prints execution time
/// uint64 op_i is counter of the internal loop
/// uses non-standard high-precision clock
#define optime(opname,repeats,codeblock) ({\
    struct timespec start, stop;\
    clock_gettime(CLOCK_REALTIME, &start);\
    for(uint64 op_i=0;op_i<(uint64)repeats;op_i++)\
        (codeblock);\
    clock_gettime(CLOCK_REALTIME, &stop);\
    double t=(double)(stop.tv_sec-start.tv_sec)*1000000+(double)(stop.tv_nsec-start.tv_nsec)/1000;\
    __optime_print(opname,t)\
})
#else 
/// uses standard low precision clock
#define optime(opname,repeats,codeblock) ({\
    clock_t start=clock();\
    for(uint64 op_i=0;op_i<(uint64)repeats;op_i++)\
        (codeblock);\
    clock_t stop=clock();\
    double t=(double)(stop-start)/CLOCKS_PER_SEC*1000000;\
    __optime_print(opname,t)\
})
#endif
