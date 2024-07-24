#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operator.h" // �ʿ��� ��� ���� ����

#define MAX_LENGTH 32

int inputProc(char* first, char* second, char* operator) // ���� : 0 return, ���� : 1 return
{
	char firstNumberSign; // ù��° �Է��� ��ȣ
	char firstSizeIncludeNul; // ù��° �Է��� ũ�� (��ȣ, null ����)
	char secondNumberSign; // �ι�° �Է��� ��ȣ
	char secondSizeIncludeNul;  // �ι�° �Է��� ũ�� (��ȣ, null ����)
	char currentIndex = 0;
	char currentData;
	char offset; // �Է��� ũ�� ����

	printf("ù��° ���� : ");
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
		printf("�߸��� �Է°�");
		while (getchar() != '\n') // �Է� ���� ����
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
			printf("�߸��� �Է°�");
			while (getchar() != '\n') // �Է� ���� ���� 
			{
				continue;
			}
			return 1;
		}

	}
	first[currentIndex] = '\0';
	firstSizeIncludeNul = currentIndex;
	currentIndex = 0;

	printf("������ (+, -, *, /) : ");
	currentData = getchar();
	if ((currentData == '+') || (currentData == '-') || (currentData == '*') || (currentData == '/'))
	{
		*operator=currentData;
		while (getchar() != '\n') // �Է� ���� ����
		{
			continue;
		}
	}
	else
	{
		printf("�߸��� �Է°�");
		while (getchar() != '\n') // �Է� ���� ���� 
		{
			continue;
		}
		return 1;
	}

	printf("�ι�° ���� : ");
	secondNumberSign = getchar();
	if (secondNumberSign >= '0' && secondNumberSign <= '9')
	{
		second[currentIndex++] = 0;
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
		printf("�߸��� �Է°�");
		while (getchar() != '\n') // �Է� ���� ����
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
			printf("�߸��� �Է°�");
			while (getchar() != '\n') // �Է� ���� ���� 
			{
				continue;
			}
			return 1;
		}

	}
	second[currentIndex] = '\0';
	secondSizeIncludeNul = currentIndex;
	currentIndex = 0;
	////////////////////////////////////////////////////////////////////////////////////////////////// �ڸ��� ���߱�
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


// �޴� ��� �Լ�
int print_menu(void) {
    int nInput = 0;
    system("cls");
    printf("[1] ���� \t[2] ���� \t[0] Exit\n");

    while (1) {
        int result = scanf_s("%d", &nInput);
        if (result != 1) {
            printf("�߸��� �Է��Դϴ�. ���ڸ� �Է����ּ���.\n");
            while (getchar() != '\n');
        }
        else {
            if (nInput < 0 || nInput > 2) {
                printf("�߸� �Է��ϼ̽��ϴ�. 0~2 ���� ������ �ٽ� �������ּ���.\n");
                while (getchar() != '\n');
            }
            else {
                break;
            }
        }
    }

    return nInput;
}

// �Է� �� �ޱ� �Լ�
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
            // ���� ó�� �ڵ� (���� �߰�)
            res = add(firstNumber, secondNumber);
            printf("결과: %s\n", res);
            free(res);
            break;

        case 2:
            res = getMinus(firstNumber, secondNumber);
            printf("���: %s\n", res);
            free(res);
            break;
        }

        free(firstNumber);
        free(secondNumber);

        puts("�޴��� ���ư��� ���ؼ� Enter�� �����ּ���.");
        getchar();
        getchar();
    }

    puts("���⸦ �����ϰڽ��ϴ�.");
    return 0;
}
