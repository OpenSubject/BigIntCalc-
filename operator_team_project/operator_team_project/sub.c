#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int tenSum(int x) {
    int num = 10;
    int temp = 0;
    while (num) {
        temp = x;
        x = x ^ num;
        num = (temp & num) << 1;
    }
    return x;
}

int digitMinus(int x, int y) {
    int temp = 0;
    while (y) {
        temp = x;
        x = x ^ y;
        y = ((~temp) & y) << 1;
    }
    return x;
}

void subtractNum(int lena, int lenb, int signa, char* a, char* b, char* val) {
    int borrow_bit = 0;
    lena -= 1;

    char res[100] = { 0 };
    strcpy_s(res, sizeof(res), a);

    for (int i = lenb - 1; i >= 0; i--) {
        int temp = 0;
        int x = a[lena] - '0';
        int y = b[i] - '0';

        if (x < y + borrow_bit) {
            x += 10; // borrow from the next digit
            temp = 1;
        }
        x = x - y - borrow_bit;

        if (temp) {
            borrow_bit = 1;
        }
        else {
            borrow_bit = 0;
        }

        res[lena] = x + '0';
        lena--;
    }

    while (lena >= 0 && borrow_bit) {
        int x = a[lena] - '0';
        if (x < borrow_bit) {
            x += 10; // borrow from the next digit
            borrow_bit = 1;
        }
        else {
            borrow_bit = 0;
        }
        res[lena] = x - borrow_bit + '0';
        lena--;
    }

    int idx = 0;
    while (idx < 100 && res[idx] == '0') {
        idx++;
    }

    int start = 0;
    if (signa == -1) {
        val[0] = '-';
        start = 1;
    }

    for (int i = idx; i < 100 && res[i] != '\0'; i++) {
        val[start] = res[i];
        start += 1;
    }
    val[start] = '\0'; // 문자열 끝을 명시적으로 설정
}


char* getMinus(char* a, char* b) {
    int lena = strlen(a);
    int lenb = strlen(b);
    int signa = 1;
    int signb = 1;

    if (a[0] != '-' && b[0] != '-' && lena < lenb) {
        signb = -1;
    }
    if (a[0] == '-') {
        for (int i = 1; i < lena; i++) {
            a[i - 1] = a[i];
        }
        a[lena - 1] = '\0';
        lena -= 1;
        signa = -1;
    }

    if (b[0] == '-') {
        for (int i = 1; i < lenb; i++) {
            b[i - 1] = b[i];
        }
        b[lenb - 1] = '\0';
        lenb -= 1;
        signb = -1;
    }

    char* res = (char*)malloc(100 * sizeof(char)); // 동적 메모리 할당
    if (res == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    memset(res, 0, 100 * sizeof(char));

    if (lena < lenb) {
        subtractNum(lenb, lena, -signb, b, a, res);
    }
    else if (lena == lenb) {
        int flag = 0;
        for (int i = 0; i < lena; i++) {
            if (a[i] > b[i]) {
                flag = 1; // a is bigger number
                break;
            }
        }
        if (flag == 1) {
            subtractNum(lena, lenb, signa, a, b, res);
        }
        else {
            subtractNum(lenb, lena, -signb, b, a, res);
        }
    }
    else {
        subtractNum(lena, lenb, signa, a, b, res);
    }

    return res;
}

