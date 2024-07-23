#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "operator.h" // 필요한 헤더 파일 포함

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
    int operator;
    char num1[10] = { '-', '1', '0', '0' }; // 초기값 설정
    char num2[10] = { '-', '8', '0' }; // 초기값 설정
    char* res;

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
            res = getMinus(num1, num2);
            printf("결과: %s\n", res);
            free(res);
            break;
        }

        free(num1);
        free(num2);

        puts("메뉴로 돌아가기 위해서 Enter를 눌러주세요.");
        getchar();
        getchar();
    }

    puts("계산기를 종료하겠습니다.");
    return 0;
}
