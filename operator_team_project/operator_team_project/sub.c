#include "operator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int tenSum(int x)
{
    int num = 10;
    int temp = 0;
    while (num)
    {
        temp = x;
        x = x ^ num;
        num = (temp & num) << 1;
    }
    return x;
}

int digitMinus(int x, int y)
{
    int temp = 0;
    while (y)
    {
        temp = x;
        x = x ^ y;
        y = ((~temp) & y) << 1;
    }
    return x;
}

void subtractNum(int lena, int lenb, int signa, char *a, char *b, char *val)
{
    int borrow_bit = 0;
    lena -= 1;

    char res[100] = {0};
    strcpy_s(res, sizeof(res), a);

    for (int i = lenb - 1; i >= 0; i--)
    {
        int temp = 0;
        int x = a[lena] - '0';
        int y = b[i] - '0';

        if (x == 0)
        {
            x = tenSum(x);
            temp = 1;
        }
        x = digitMinus(x, borrow_bit);
        if (x == 10 && y == 0)
        {
            res[lena] = '0';
            lena--;
            continue;
        }

        if (x < y)
        {
            x = tenSum(x);
            borrow_bit = 1;
        }
        else
        {
            borrow_bit = 0;
        }
        x = digitMinus(x, y);
        res[lena] = x + '0';
        if (temp == 1)
        {
            borrow_bit = 1;
        }
        x = digitMinus(x, borrow_bit);

        lena--;
    }

    int tempx = a[lena] - '0';
    tempx = digitMinus(tempx, borrow_bit);
    res[lena] = tempx + '0';
    int nr = strlen(res);

    int idx = 0;
    for (int i = 0; i < nr; i++)
    {
        if (res[i] != '0')
        {
            idx = i;
            break;
        }
    }
    int start = 0;
    if (signa == -1)
    {
        val[0] = '-';
        start = 1;
    }

    for (int i = idx; i < 100 && res[i] != '\0'; i++)
    {
        val[start] = res[i];
        start += 1;
    }
    val[start] = '\0'; 
}

char *getMinus(char *a, char *b)
{
    int lena = strlen(a);
    int lenb = strlen(b);
    int signa = 1;
    int signb = 1;

    if (a[0] != '-' && b[0] != '-' && lena < lenb)
    {
        signb = -1;
    }
    if (a[0] == '-')
    {
        for (int i = 1; i < lena; i++)
        {
            a[i - 1] = a[i];
        }
        a[lena - 1] = '\0';
        lena -= 1;
        signa = -1;
    }

    if (b[0] == '-')
    {
        for (int i = 1; i < lenb; i++)
        {
            b[i - 1] = b[i];
        }
        b[lenb - 1] = '\0';
        lenb -= 1;
        signb = -1;
    }
    if (a[0] == '+') {
        for (int i = 1; i < lena; i++) {
            a[i - 1] = a[i];
        }
        a[lena - 1] = '\n';
        lena -= 1;
    }

    if (b[0] == '+') {
        for (int i = 1; i < lenb; i++) {
            b[i - 1] = b[i];
        }
        b[lenb - 1] = '\n';
        lenb -= 1;
    }

    int idx = 0;
    for (int i = 0; i < lenb; i++) {
        if (b[i] != '0') {
            idx = i;
            lenb -= i;
            break;
        }
    }
    int start = 0;
    for (int i = idx; i < 100 && b[i] != '\0'; i++) {
        b[start] = b[i];
        start += 1;

    }
    b[start] = '\0'; // 문자열 끝을 명시적으로 설정

    int idxa = 0;
    for (int i = 0; i < lena; i++) {
        if (a[i] != '0') {
            idxa = i;
            lena -= i;
            break;
        }
    }
    int starta = 0;
    for (int i = idxa; i < 100 && a[i] != '\0'; i++) {
        a[starta] = a[i];
        starta += 1;

    }

    a[starta] = '\0'; // 문자열 끝을 명시적으로 설정

    char *res = (char *)malloc(100 * sizeof(char)); 
    if (res == NULL)
    {
        printf("fail malloc \n");
        exit(1);
    }
    memset(res, 0, 100 * sizeof(char));

    if (lena < lenb)
    {
        subtractNum(lenb, lena, signb, b, a, res);
    }
    else if (lena == lenb)
    {
        int flag = 0;
        for (int i = 0; i < lena; i++)
        {
            if (a[i] > b[i])
            {
                flag = 1; // a is bigger number
                break;
            }
        }
        if (flag == 1)
        {
            subtractNum(lena, lenb, signa, a, b, res);
        }
        else
        {
            subtractNum(lenb, lena, signb, b, a, res);
        }
    }
    else
    {
        subtractNum(lena, lenb, signa, a, b, res);
    }

    return res;
}
