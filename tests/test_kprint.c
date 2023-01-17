#include "tests.h"
#include "../src/kprint/kprint.h"

void test_kprint(){
    //int
    kprint(kp_fgCyan|
        kp_i,-8888, kp_c,' ', kp_i,0, kp_c,' ', kp_i,1234567890987654321LL,kp_s,"\n");
    //uint
    kprint(kp_fgGreen|
        kp_u|kp_post,-8888, kp_c|kp_post|kp_upper,' ', kp_u,0, kp_c,' ', 
        kp_u,1234567890987654321LL, kp_c,'\n');
    //float
    kprint(kp_bgGreenD|kp_fgRed|
        kp_f,-4000.0109f, kp_c,' ', kp_f,-0.000020004f, kp_c,'\n',
        kp_f,-1.0f, kp_c,' ', kp_f,0.0f, kp_c,' ', kp_f,1.0f, kp_c,'\n', 
        kp_f|kp_post,0.000020004f, kp_c,' ',
        kp_f|kp_post|kp_upper,4000.0109f, kp_c,'\n');
    //double
    kprint(kp_bgBlueD|kp_fgRed|
        kp_f,-4000.0109, kp_c,' ', kp_f,-0.000020004, kp_c,'\n', 
        kp_f,-1.0, kp_c,' ', kp_f,0.0, kp_c,' ', kp_f,1.0, kp_c,'\n', 
        kp_f|kp_post,0.000020004, kp_c,' ', 
        kp_f|kp_post|kp_upper,4000.0109, kp_c,'\n');
    //hex
    kprint(kp_bgBlack|kp_fgYellow|
        kp_h,0, kp_c,' ', kp_h,1, kp_c,' ', kp_h,-1, kp_c,' ', kp_h,15, kp_c,'\n', 
        kp_h,4095, kp_c,' ', kp_h,-4095, kp_c,'\n', 
        kp_h,1234567890987654321LL, kp_c,'\n', kp_h,-1234567890987654321LL, kp_c,'\n');
    kprint(
        kp_h,-1.0f, kp_c,' ', kp_h,0.0f, kp_c,' ', kp_h,1.0f, kp_c,'\n',
        kp_h, 0.00016f, kp_c,' ', kp_h,-115515.009f, kp_c,'\n');
    kprint(
        kp_h|kp_pre, 0.00016, kp_c,'\n', 
        kp_h|kp_pre|kp_upper,-115515.009, kp_c,'\n');
    //bin
    kprint(kp_fgBlue|
        kp_b,0, kp_c,' ', kp_b,1, kp_c,' ', kp_b,-1, kp_c,' ', kp_b,15, kp_c,' ', 
        kp_b,4095, kp_c,' ', kp_b,-4095, kp_c,'\n', 
        kp_b,1234567890987654321LL, kp_c,'\n', kp_b,-1234567890987654321LL, kp_c,'\n');
    kprint(
        kp_b,-1.0f, kp_c,' ', kp_b,0.0f, kp_c,' ', kp_b,1.0f, kp_c,'\n',
        kp_b, 0.00016f, kp_c,' ', kp_b,-115515.009f, kp_c,'\n');
    kprint(
        kp_b|kp_pre, 0.00016, kp_c,'\n', 
        kp_b|kp_pre|kp_upper,-115515.009, kp_c,'\n');
    //string
    kprint(kp_s|kp_fgYellow, "\n  ooo  \n", 
        kp_s|kp_fgWhite, "gg",
        kp_fgGray|kp_bgBlack|kp_s, "\n");
}
