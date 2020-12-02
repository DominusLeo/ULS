#include "libmx.h"

static int two_byte(int *num, wchar_t c) {
    num[1] = 128 + c % (wchar_t)(mx_pow(2, 6));
    num[0] = 192 + (c >> 6);
    return 1;
}

static int three_byte(int *num, wchar_t c) {
    num[2] = 128 + c % (wchar_t)(mx_pow(2, 6));
    num[1] = 128 + ((c % (wchar_t)(mx_pow(2, 12))) >> 6);
    num[0] = 224 + (c >> 12);
    return 2;
}

static int four_byte(int *num, wchar_t c) {
    num[3] = 128 + c % (wchar_t)(mx_pow(2, 6));
    num[2] = 128 + ((c % (wchar_t)(mx_pow(2, 12))) >> 6);
    num[1] = 128 + ((c % (wchar_t)(mx_pow(2, 18))) >> 12);
    num[0] = 240 + (c >> 18);
    return 3;
}

void mx_print_unicode(wchar_t c) {
    int num[4] = {0};
    int i = 0;

    if (c < 128)
        num[0] = c;
    if (c >= 128 && c < 2048)
        i = two_byte(num, c);
    if (c >=2048 && c < 65536)
        i = three_byte(num, c);
    if (c >= 65536 && c < 1114112)
        i = four_byte(num, c);
    if (c >= 1114112)
        return;
    for(int j = 0 ; j <= i; j++)
        write(1, &num[j], 1);
    return;
}

/*void mx_print_unicode(wchar_t c) {
    int num0 = 0;
    int i = 0;

    if (c < 128)
        num0 = c - 128;
    if (c >= 128 && c < 2048) {
//        num[1] = c % (wchar_t)(mx_pow(2, 6));
        num0 = 64 + (c >> 6);
        i = 1;
    }
    if (c >=2048 && c < 65536) {
//        num[2] = c % (wchar_t)(mx_pow(2, 6));
//        num[1] = ((c % (wchar_t)(mx_pow(2, 12))) >> 6);
        num0 = 96 + (c >> 12);
        i = 2;
    }
    if (c >= 65536 && c < 1112065) {
//        num[3] = c % (wchar_t)(mx_pow(2, 6));
//        num[2] = ((c % (wchar_t)(mx_pow(2, 12))) >> 6);
//        num[1] = ((c % (wchar_t)(mx_pow(2, 18))) >> 12);
        num0 = 112 + (c >> 18);
        i = 3;
    }
    if (c >= 1112065)
        return;
    for(int j = 0 ; j <= i; j++) {
        c = num0 + 128;
        c = c %
        //        num[j] += 128;// + c % 64;
        //c >> 6;
        write(1, &c, 1);
    }
    return;
}*/

// 64 >> 2 == 64 / 2^2
// 128 >> 6 == 128 / 2^6

// 010000 >> 6 >> 000001 & 011111 = 011111 | (0000001) -> 0000001 0100000
// 010000
// 100000
// 110000
// 111000

//1111                                      111111                            011100
