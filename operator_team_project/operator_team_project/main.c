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
        first[currentIndex++] = '+';
        first[currentIndex++] = firstNumberSign;
        firstNumberSign = 0;
    }
    else if (firstNumberSign == '-')
    {
        first[currentIndex++] = '-';
        firstNumberSign = 1;
    }
    else
    {
        printf("�߸��� �Է°�\n");
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
            first[currentIndex++] = currentData;
        }
        else
        {
            printf("�߸��� �Է°�\n");
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

    printf("������ (+, -) or 0(EXIT): ");
    currentData = getchar();
    if ((currentData == '+') || (currentData == '-') || (currentData == '0'))
    {
        *operator = currentData;
        while (getchar() != '\n') // �Է� ���� ����
        {
            continue;
        }
    }
    else
    {
        printf("�߸��� �Է°�\n");
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
        second[currentIndex++] = '+';
        second[currentIndex++] = secondNumberSign;
        secondNumberSign = 0;
    }
    else if (secondNumberSign == '-')
    {
        second[currentIndex++] = '-';
        secondNumberSign = 1;
    }
    else
    {
        printf("�߸��� �Է°�\n");
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
            second[currentIndex++] = currentData;
        }
        else
        {
            printf("�߸��� �Է°�\n");
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
            second[index] = '0';
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
            first[index] = '0';
        }
    }

    return 0;
}

int main() {
    char firstNumber[MAX_LENGTH];
    char secondNumber[MAX_LENGTH];
    char operator[2];  // �����ڸ� ���� �迭
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
            // add �Լ� call
            /*res = getAdd(firstNumber, secondNumber);
            printf("���: %s\n", res);
            free(res);*/
            break;
        case 1:
            printf("ù��° ���� : %s\n", firstNumber);
            printf("�ι�° ���� : %s\n", secondNumber);
            res = getMinus(firstNumber, secondNumber);
            printf("���: %s\n", res);
            free(res);
            break;
        default:
            printf("�������� �ʴ� �������Դϴ�.\n");
            break;
        }

        puts("�޴��� ���ư��� ���ؼ� Enter�� �����ּ���.");
        getchar();  // Enter Ű �Է� ���
    }

    puts("���⸦ �����ϰڽ��ϴ�.");
    return 0;
}

int operatorSelector(char* first, char* second, char* operator) {
    int result; //0 �̸� add ������ call , 1�̸� sub ������ call

    // �����ڰ� - �϶�, �ι�° ��ȣ ����  
    if (*operator == '-') {
        if (second[0] == '-') {
            second[0] = '+';
        }
        else {
            second[0] = '-';
        }
    }

    if (first[0] == second[0]) {
        //���� ��ȣ�� ���� add ȣ�� 
        result = 0;
    }
    else {
        //xor �϶��� sub ȣ�� 
        result = 1;
    }

    return result;
}
