#include "operator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeSign(char *str)
{
    memmove(str, str + 1, strlen(str));
}

void removeZeros(char *str)
{
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
    // 문자를 정수로 변환하는 부분
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
    // 문자열 2개를 순환하면서 값을 더한다.
    // 문자열들을 거꾸로 재배열한다.
    // 순환하면서 1의 자리부터 덧셈을 처리한다.
    // (가장 처음에는 \n값을 집어넣는다.)
    // 덧셈처리는 해당 문자값을 정수로 바꾼뒤 처리한다.
    // 만약 자리 올림값이 생기면 다음 자리수 계산에 추가하여 같이한다.
    // 결과값은 원하는 값이 거꾸로된 문자열이다.
    // 부호를 추가한다.
    // 해당값을 다시 거꾸로 재배열한다.
    // 재배열 후 출력한다.
    char sign = first[0];

    if (first[0] != second[0])
    {
        printf("올바른 부호값이 아닙니다.\n");
        return NULL;
    }

    // 문자열 복사
    char *first_copy = strdup(first);
    char *second_copy = strdup(second);

    // 부호삭제
    removeSign(first_copy);
    removeSign(second_copy);

    // 문자열 길이
    int first_length = (int)strlen(first_copy), second_length = (int)strlen(second_copy);

    // 가장 긴 문자열 길이
    int length = (first_length > second_length) ? first_length : second_length;
    length++; // \n값을 위한 처리

    // 자리 올림 값
    int carry_in = 0;

    // 두 문자열 거꾸로 재배열
    char *reversed_first = malloc(first_length + 2);
    char *reversed_second = malloc(second_length + 2);
    memset(reversed_first, 0, first_length + 2);
    memset(reversed_second, 0, second_length + 2);

    reversedString(first_copy, reversed_first);
    reversedString(second_copy, reversed_second);

    // 문자열 합 계산
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
        results[i + 1] = result + '0';
    }

    // 널 문자 추가
    results[length + 1] = '\0';

    // 다시 거꾸로 재배열 처리 준비
    char *reversed_results = malloc(length + 2);
    memset(reversed_results, 0, length + 2);

    // 부호 추가
    results[length] = sign;

    reversedString(results, reversed_results);
    removeZeros(reversed_results);

    // printf("Input A : %s\n", first);
    // printf("Input B : %s\n", second);
    // printf("결과 값 : %s\n", reversed_results);

    return reversed_results;
}