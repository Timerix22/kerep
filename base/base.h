#pragma once

#if __cplusplus
extern "C" {
#endif

#include "std.h"
#include "types.h"
#include "errors.h"
#include "mystr.h"

// executes codeblock and prints execution time
#ifdef CLOCK_REALTIME // non-standard high-precision clock
    #define optime(opname,repeats,codeblock) ({\
        struct timespec start, stop;\
        clock_gettime(CLOCK_REALTIME, &start);\
        for(uint64 ___OPREP=0;___OPREP<(uint64)repeats;___OPREP++)\
            (codeblock);\
        clock_gettime(CLOCK_REALTIME, &stop);\
        double t=(double)(stop.tv_sec-start.tv_sec+(double)(stop.tv_nsec-start.tv_nsec)/1000000000)/repeats;\
        printf("\e[93moperation \e[94m%s\e[93m lasted \e[94m%lf \e[93mseconds\n",opname,t);\
    })
#else // standard clock which works worse then previous
    #define optime(opname,repeats,codeblock) ({\
        clock_t start=clock();\
        for(uint64 ___OPREP=0;___OPREP<(uint64)repeats;___OPREP++)\
            (codeblock);\
        clock_t stop=clock();\
        double t=(double)(stop-start)/CLOCKS_PER_SEC/repeats;\
        printf("\e[93moperation \e[94m%s\e[93m lasted \e[94m%lf \e[93mseconds\n",opname,t);\
    })
#endif

#if __cplusplus
}
#endif