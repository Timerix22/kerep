#include "tests.h"
#include "../src/kprint/kprint.h"
#if defined(_WIN32)|| defined(_WIN64)
    #include <windows.h>
#endif

#define testColor(COLOR) \
    kprint_setColor(kp_bgBlack|kp_fg##COLOR);\
    kprintf(#COLOR " ");\
    kprint_setColor(kp_bg##COLOR|kp_fgGray);\
    kprintf(#COLOR);\
    kprint_setColor(kp_bgBlack|kp_fgBlack);\
    kprintf("\n");

void test_kprint_colors(){
    /* IFWIN(
        ({
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            for(u8 col=0; col<255; col++){
                SetConsoleTextAttribute(hConsole, col);
                kprintf("%u ",col);
            }
        }),
        ({
            for(u8 col=0; col<255; col++)
                kprintf("\e[%um%u ", col, col);
        })
    ); 
    kprintf("\n"); */
    
    testColor(Black);
    testColor(RedD);
    testColor(GreenD);
    testColor(YellowD);
    testColor(BlueD);
    testColor(MagentaD);
    testColor(CyanD);
    testColor(Gray);
    testColor(GrayD);
    testColor(Red);
    testColor(Green);
    testColor(Yellow);
    testColor(Blue);
    testColor(Magenta);
    testColor(Cyan);
    testColor(White);
    kprint_setColor(kp_bgBlack|kp_fgGray);
}
