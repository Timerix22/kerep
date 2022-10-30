#include "tests.h"
#include "../src/kprint/kprint.h"
#if defined(_WIN32)|| defined(_WIN64)
    #include <windows.h>
#endif

#define testColor(COLOR) \
    kprint_setColor(kprint_bgBlack | kprint_fg##COLOR);\
    kprintf(#COLOR " ");\
    kprint_setColor(kprint_bg##COLOR | kprint_fgGray);\
    kprintf(#COLOR);\
    kprint_setColor(kprint_bgBlack | kprint_fgBlack);\
    kprintf("\n");

void test_kprint_colors(){
    /* IFWIN(
        ({
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            for(uint8 col=0; col<255; col++){
                SetConsoleTextAttribute(hConsole, col);
                kprintf("%u ",col);
            }
        }),
        ({
            for(uint8 col=0; col<255; col++)
                kprintf("\e[%um%u ", col, col);
        })
    ); 
    kprintf("\n"); */
    
    testColor(Black);
    testColor(DarkRed);
    testColor(DarkGreen);
    testColor(DarkYellow);
    testColor(DarkBlue);
    testColor(DarkMagenta);
    testColor(DarkCyan);
    testColor(Gray);
    testColor(DarkGray);
    testColor(Red);
    testColor(Green);
    testColor(Yellow);
    testColor(Blue);
    testColor(Magenta);
    testColor(Cyan);
    testColor(White);
    kprint_setColor(kprint_bgBlack | kprint_fgGray);

    kprint(kprint_fmtInt | kprint_fgCyan, 8888, kprint_fmtString | kprint_fgYellow, "  ooo  ", kprint_fmtFloat | kprint_bgDarkGreen | kprint_fgRed, 4.01, kprint_fmtString | kprint_fgWhite, "\ngg\n");
}