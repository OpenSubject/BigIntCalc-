#include "operator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeSign(char *str)
{
    memmove(str, str + 1, strlen(str));
}

void removeZeros(char *str, int carry)
{
    // carry가 0보다 크면 0을 지우지 않는다.
    if (carry > 0)
    {
        return;
    }

    // 문자열 앞에 있는 0을 지운다.
    int index = 0;
    while (str[index] == '0')
    {
        index++;
    }

    // index가 0이 아니라면, 앞에 있는 0을 제거
    if (index > 0)
    {
        int i = 0;
        while (str[index])
        {
            str[i++] = str[index++];
        }
        str[i] = '\0'; // 문자열 끝에 null 문자 추가
    }
}

// 그니까....
// 생각해보니
// 그냥 문자열을 순환하면서
// 각각을 마지막 자리수부터 덧셈을 처리하면 될거 같다.
// 굳이 이걸 정수로 바꿨다가 왔다갔다 하지말고
// 그냥 문자열을 거꾸로 순환하면서
// 덧셈을 쭉 처리하면 되는걸로 보인다.

void reversedString(const char *origin_char, char *result)
{
    int length = strlen(origin_char);

    for (int i = 0; i < length; i++)
    {
        result[i] = origin_char[length - 1 - i];
    }
    result[length] = '\0'; // 문자열의 끝에 null 문자 추가
}

int charToInt(char c)
{
    // 문자값 확인
    // printf("%c\n", c);
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else
    {
        // 숫자 문자가 아닌 경우 에러 처리
        printf("Invalid input: %c\n", c);
        return -1; // 에러 값
    }
}

char *getAdd(char *first, char *second)
{
    // 문자열을 거꾸로 순환한다.

    char sign = first[0];

    if (first[0] != second[0])
    {
        printf("올바른 부호값이 아닙니다.\n");
        return NULL;
    }

    char* first_copy = _strdup(first);
    char* second_copy = _strdup(second);

    // 부호삭제
    removeSign(first_copy);
    removeSign(second_copy);

    int first_length =(int)strlen(first_copy), second_length = (int)strlen(second_copy);
    int length = (first_length > second_length) ? first_length : second_length;
    int carry_in = 0;

    char *reversed_first = malloc(first_length + 2);
    char *reversed_second = malloc(second_length + 2);
    memset(reversed_first, 0, first_length + 2);
    memset(reversed_second, 0, second_length + 2);
    // char reversed_first[first_length + 2];
    // char reversed_second[second_length + 2];

    reversedString(first_copy, reversed_first);
    reversedString(second_copy, reversed_second);

    char first_char_value = 0, second_char_value = 0;
    int result = 0;
    int sum = 0;
    char *results = malloc(length);
    memset(results, 0, length);

    for (int i = 0; i <= length; i++)
    {
        int first_value = 0, second_value = 0;

        if (i <= first_length - 1)
        {
            first_char_value = reversed_first[i];
            first_value = charToInt(first_char_value);
        }
        if (i <= second_length - 1)
        {
            second_char_value = reversed_second[i];
            second_value = charToInt(second_char_value);
        }

        sum = first_value + second_value + carry_in;

        if (sum > 9)
        {
            carry_in = 1;
            result = sum - 10;
        }
        else
        {
            carry_in = 0;
            result = sum;
        }
        results[i] = result + '0';
    }

    char *reversed_results = malloc(length + 4);

    results[length] = sign;

    reversedString(results, reversed_results);
    removeZeros(reversed_results, 0);

    // printf("Input A : %s\n", first);
    // printf("Input B : %s\n", second);
    // printf("결과 값 : %s\n", reversed_results);

    return reversed_results;
}