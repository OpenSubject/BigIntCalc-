#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operator.h" // �ʿ��� ��� ���� ����

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
    int operator;
    char num1[10] = { '-', '1', '0', '0' }; // �ʱⰪ ����
    char num2[10] = { '-', '8', '0' }; // �ʱⰪ ����
    char* res;

    while (1) {
        operator = print_menu();

        if (operator == 0) {
            break;
        }


        switch (operator) {
        case 1:
            // ���� ó�� �ڵ� (���� �߰�)
            break;

        case 2:
            res = getMinus(num1, num2);
            printf("���: %s\n", res);
            free(res);
            break;
        }

        free(num1);
        free(num2);

        puts("�޴��� ���ư��� ���ؼ� Enter�� �����ּ���.");
        getchar();
        getchar();
    }

    puts("���⸦ �����ϰڽ��ϴ�.");
    return 0;
}
