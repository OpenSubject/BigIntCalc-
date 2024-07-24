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

	printf("연산자 (+, -, *, /) : ");
	currentData = getchar();
	if ((currentData == '+') || (currentData == '-') || (currentData == '*') || (currentData == '/'))
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
		second[currentIndex++] = 0;
		second[currentIndex++] = secondNumberSign - '0';
		secondNumberSign = 0;
	}
	else if (firstNumberSign == '-')
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


// 메뉴 출력 함수
int print_menu(void) {
    int nInput = 0;
    system("cls");
    printf("[1] 덧셈 \t[2] 뺄셈 \t[0] Exit\n");

    while (1) {
        int result = scanf_s("%d", &nInput);
        if (result != 1) {
            printf("잘못된 입력입니다. 숫자를 입력해주세요.\n");
            while (getchar() != '\n');
        }
        else {
            if (nInput < 0 || nInput > 2) {
                printf("잘못 입력하셨습니다. 0~2 사이 정수로 다시 선택해주세요.\n");
                while (getchar() != '\n');
            }
            else {
                break;
            }
        }
    }

    return nInput;
}

// 입력 값 받기 함수
//char* getInput(const char* prompt) {
//
//}

int main() {

    char* res;

	char firstNumber[MAX_LENGTH];
	char secondNumber[MAX_LENGTH];
	char operator;

	while (1)
	{
		int inputErr = inputProc(firstNumber, secondNumber, &operator);
		if (inputErr == 0)
		{
			break;
		}
	}

    while (1) {
        operator = print_menu();

        if (operator == 0) {
            break;
        }


        switch (operator) {
        case 1:
            // 덧셈 처리 코드 (추후 추가)
            break;

        case 2:
            res = getMinus(firstNumber, secondNumber);
            printf("결과: %s\n", res);
            free(res);
            break;
        }

        free(firstNumber);
        free(secondNumber);

        puts("메뉴로 돌아가기 위해서 Enter를 눌러주세요.");
        getchar();
        getchar();
    }

    puts("계산기를 종료하겠습니다.");
    return 0;
}
