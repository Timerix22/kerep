#include "tests.h"
#include "../src/kprint/kprint.h"
#if defined(_WIN32)|| defined(_WIN64)
    #include <windows.h>
#endif

#define testColor(COLOR) \
    kprint_setColor(kprint_bgBlack | kprint_fg##COLOR);\
    printf(#COLOR " ");\
    kprint_setColor(kprint_bg##COLOR | kprint_fgGray);\
    printf(#COLOR);\
    kprint_setColor(kprint_bgBlack | kprint_fgBlack);\
    printf("\n");

void test_kprint_colors(){
    IFWIN(
        ({
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            for(uint8 col=0; col<255; col++){
                SetConsoleTextAttribute(hConsole, col);
                printf("%u ",col);
            }
        }),
        ({
            for(uint8 col=0; col<255; col++)
                printf("\e[%um%u ", col, col);
        })
    ); 
    printf("\n");
    
    testColor(Black);
    testColor(DarkRed);
    testColor(DarkGreen);
    testColor(DarkYellow);
    testColor(DarkBlue);
    testColor(DarkMagneta);
    testColor(DarkCyan);
    testColor(Gray);
    testColor(DarkGray);
    testColor(Red);
    testColor(Green);
    testColor(Yellow);
    testColor(Blue);
    testColor(Magneta);
    testColor(Cyan);
    testColor(White);
    kprint_setColor(kprint_bgBlack | kprint_fgGray);

    kprint(kprint_fmtInt | kprint_fgCyan, 8888, kprint_fmtString | kprint_fgYellow, "  ooo  ", kprint_fmtFloat | kprint_bgDarkGreen | kprint_fgRed, 4.01, kprint_fmtString | kprint_fgWhite, "\ngg\n");
}