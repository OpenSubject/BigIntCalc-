#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operator.h" // 필요한 헤더 파일 포함

#define MAX_LENGTH 32

int inputProc(char* first, char* second, char* operator) // 성공 : 0 return, 실패 : 1 return
{
	char firstNumberSign; // 첫번째 입력의 부호
	char firstSizeIncludeNul; // 첫번째 입력의 크기 (부호, null 포함)
	char secondNumberSign; // 두번째 입력의 부호
	char secondSizeIncludeNul;  // 두번째 입력의 크기 (부호, null 포함)
	char currentIndex = 0;
	char currentData;
	char offset; // 입력의 크기 차이

	printf("첫번째 숫자 : ");
	firstNumberSign = getchar();
	if (firstNumberSign >= '0' && firstNumberSign <= '9')
	{
		first[currentIndex++] = 0;
		first[currentIndex++] = firstNumberSign - '0';
		firstNumberSign = 0;
	}
	else if (firstNumberSign == '-')
	{
		first[currentIndex++] = '-';
		firstNumberSign = 1;
	}
	else
	{
		printf("잘못된 입력값");
		while (getchar() != '\n') // 입력 버퍼 비우기
		{
			continue;
		}
		return 1;
	}

	while ((currentData = getchar()) != '\n')
	{
		if (currentData >= '0' && currentData <= '9')
		{
			first[currentIndex++] = currentData - '0';
		}
		else
		{
			printf("잘못된 입력값");
			while (getchar() != '\n') // 입력 버퍼 비우기 
			{
				continue;
			}
			return 1;
		}

	}
	first[currentIndex] = '\0';
	firstSizeIncludeNul = currentIndex;
	currentIndex = 0;

	printf("연산자 (+, -) or 0(EXIT): ");
	currentData = getchar();
	if ((currentData == '+') || (currentData == '-') || (currentData == '0'))
	{
		*operator=currentData;
		while (getchar() != '\n') // 입력 버퍼 비우기
		{
			continue;
		}
	}
	else
	{
		printf("잘못된 입력값");
		while (getchar() != '\n') // 입력 버퍼 비우기 
		{
			continue;
		}
		return 1;
	}

	printf("두번째 숫자 : ");
	secondNumberSign = getchar();
	if (secondNumberSign >= '0' && secondNumberSign <= '9')
	{
		second[currentIndex++] = '+';
		second[currentIndex++] = secondNumberSign - '0';
		secondNumberSign = 0;
	}
	else if (secondNumberSign == '-')
	{
		second[currentIndex++] = '-';
		secondNumberSign = 1;
	}
	else
	{
		printf("잘못된 입력값");
		while (getchar() != '\n') // 입력 버퍼 비우기
		{
			continue;
		}
		return 1;
	}

	while ((currentData = getchar()) != '\n')
	{
		if (currentData >= '0' && currentData <= '9')
		{
			second[currentIndex++] = currentData - '0';
		}
		else
		{
			printf("잘못된 입력값");
			while (getchar() != '\n') // 입력 버퍼 비우기 
			{
				continue;
			}
			return 1;
		}

	}
	second[currentIndex] = '\0';
	secondSizeIncludeNul = currentIndex;
	currentIndex = 0;
	////////////////////////////////////////////////////////////////////////////////////////////////// 자리수 맞추기
	if (firstSizeIncludeNul > secondSizeIncludeNul)
	{
		offset = firstSizeIncludeNul - secondSizeIncludeNul;
		for (int count = 0; count < secondSizeIncludeNul; count++)
		{
			second[secondSizeIncludeNul - count + offset] = second[secondSizeIncludeNul - count];
		}
		for (int index = 1; index < offset + 1; index++)
		{
			second[index] = 0;
		}
	}
	else if (firstSizeIncludeNul < secondSizeIncludeNul)
	{
		offset = secondSizeIncludeNul - firstSizeIncludeNul;
		for (int count = 0; count < firstSizeIncludeNul; count++)
		{
			first[firstSizeIncludeNul - count + offset] = first[firstSizeIncludeNul - count];
		}
		for (int index = 1; index < offset + 1; index++)
		{
			first[index] = 0;
		}
	}

	return 0;
}


int main() {
	char firstNumber[MAX_LENGTH];
	char secondNumber[MAX_LENGTH];
	char operator[2];  // 연산자를 위한 배열
	char* res;

	while (1) {
		int inputErr = inputProc(firstNumber, secondNumber, operator);
		if (inputErr == 0 && *operator == '0') {
			break;
		}
		if (inputErr == 1) {
			continue;
		}

		int functionCall = operatorSelector(firstNumber, secondNumber, operator);
		switch (functionCall) {
		case 0:
			// add 함수 call
			break;
		case 1:
			res = getMinus(firstNumber, secondNumber);
			printf("결과: %s\n", res);
			free(res);
			break;
		default:
			printf("지원되지 않는 연산자입니다.\n");
			break;
		}

		puts("메뉴로 돌아가기 위해서 Enter를 눌러주세요.");
		getchar();  // Enter 키 입력 대기


	}

	puts("계산기를 종료하겠습니다.");
	return 0;
}

int operatorSelector(char* first, char* second, char* operator) {
	int result; //0 이면 add 연산자 call , 1이면 sub 연산자 call

	// 연산자가 - 일때, 두번째 부호 반전  
	if (*operator == '-') {
		if (second[0] == '-') {
			second[0] = '+';
		}
		else {
			second[0] = '-';
		}
	}

	if (first[0] == second[0]) {
		//같은 부호일 때만 add 호출 
		result = 0;
	}
	else {
		//xor 일때만 sub 호출 
		result = 1;
	}

	return result;
}