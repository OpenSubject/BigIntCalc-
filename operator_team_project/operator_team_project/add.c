#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


// 청크 단위가 맞는거 같다....
// 지금 여러가지 개념이 들어와서 헷갈리지만
int get_chunk_num(int length) {
  return (length + 18) / 19;
}

long long get_value_of_separates(char* separates){
  while (*separates && !isdigit(*separates)) {
    memmove(separates, separates + 1, strlen(separates));
  }
  
  long long separates_num = atoll(separates);
  // printf("문자열값 %s\n", separates);
  // printf("정수값 %lld\n", separates_num);
  return separates_num;
}

void remove_sign(char* str) {
    memmove(str, str + 1, strlen(str));
}

void remove_zeros(char* str, int carry) {
    // carry가 0보다 크면 0을 지우지 않는다.
    if (carry > 0) {
        return;
    }

    // 문자열 앞에 있는 0을 지운다.
    int index = 0;
    while (str[index] == '0') {
        index++;
    }

    // index가 0이 아니라면, 앞에 있는 0을 제거
    if (index > 0) {
        int i = 0;
        while (str[index]) {
            str[i++] = str[index++];
        }
        str[i] = '\0';  // 문자열 끝에 null 문자 추가
    }
}

// 중간배열을 위한 함수
void split_number(const char* str, char result[][19], int chunk_num, int size, int str_len){
  // 가장 뒤쪽부터 처리한다.
  // 고로 position을 가장 뒤쪽으로 잡고
  // 하나씩 줄여나가면사 배열에 추가한다.
  // 기본적으로 변수는 2가지 필요 - 배열의 위치, 몇번째 배열, 남은 빈공간
  
  for (int i = 0; i < chunk_num; i++) {
    memset(result[i], 0, size + 1);
  }

  int result_index = chunk_num - 1; // 역순으로 채우기 위해 초기 인덱스를 끝으로 설정
  int chunk_pos = 0;
  char temp[19] = {0}; // 임시 배열 초기화

  for (int pos = str_len - 1; pos >= 0; pos--) {
      // 임시 배열에 저장
      temp[chunk_pos] = str[pos];
      chunk_pos++;

      // printf("pos: %d, temp: %s, chunk_pos: %d\n", pos, temp, chunk_pos);

      if (chunk_pos == size) {
          // 임시 배열을 역방향으로 result에 복사
          for (int i = 0; i < size; i++) {
              result[result_index][i] = temp[size - i - 1];
          }
          result[result_index][size] = '\0'; // 널 문자 추가
          chunk_pos = 0;

          // 디버그 출력: result 배열의 현재 상태 출력
          // printf("Chunk filled: %d, result_index: %d\n", result_index + 1, result_index);
          // for (int j = 0; j < chunk_num; j++) {
          //     printf("Chunk %d: %s\n", j, result[j]);
          // }
          result_index--;
          memset(temp, 0, sizeof(temp));
      }
  }

  if (chunk_pos > 0) {
    // 마지막 부분 처리
    for (int i = 0; i < chunk_pos; i++) {
        result[result_index][i] = temp[chunk_pos - i - 1];
    }
    result[result_index][chunk_pos] = '\0'; // 널 문자 추가

    // printf("Final chunk processed: %d\n", result_index);
    // for (int j = 0; j < chunk_num; j++) {
    //     printf("Chunk %d: %s\n", j, result[j]);
    // }
  }

  // printf("Origial String : %s\n", str);
}

// 두개의 문자열을 인자로 받는다.
// 하나의 문자열을 반환한다.
// 문자열의 크기를 알아야하나?

// 리턴이 가능하도록 포인터를 이용해본다.
// const를 적용시켜서 함수내에서 바뀌지않음을 보장한다.
char* add(char* first, char* second){
  // 계산 가능한 범위로 나눈다.
  // 반복문으로 처리한다고 가정
  // 필요한건 계산이 처리가 완성되었을때 사용될 문자열과
  // 자리 올림을 알려줄 수 있는 변수
  // 자리 올림이 발생하는 경우는 2가지를 충족해야한다.
  // 둘다 양수일것, 나눠진 32bit 안에 포함될것
  // 만약 양수와 음수의 덧셈이 적용된다면 -> 보수를 이용한 처리를 해야할까?
  // 좀 더 고민해본다. -> 팀원들과 이야기해본바 일단 부호의 xor상태는 넘어오지않는걸로 확인
  // 고로 부호를 먼저 확인하고 따로 저장한 뒤
  // 계산에서는 부호를 고려하지 않는다.
  // 그리고 계산 처리가 완료된 뒤 부호를 처리하는 방식은 어떨까?

  // 혹시나 모를 예외처리, 부호를 확인해서 다른 부호일 경우 처리한다.
  if (first[0] != second[0]){
    printf("올바른 부호값이 아닙니다.\n");
    return NULL;
  }

  char sign = first[0];

  char* first_copy = strdup(first);
  char* second_copy = strdup(second);

  // 부호삭제
  remove_sign(first_copy);
  remove_sign(second_copy);

  const int first_length = strlen(first_copy), second_length = strlen(second_copy);
  const int chunk_size = 19;

  // chunk num 필요해서 계산한다.
  const int first_chunk_num = get_chunk_num(first_length), second_chunk_num = get_chunk_num(second_length);
  const int chunk_num = (first_chunk_num > second_chunk_num) ? first_chunk_num : second_chunk_num;

  int length = (first_length > second_length) ? first_length : second_length;
  long long first_separates_int_value = 0, second_separates_int_value = 0;
  char results[length + 1];
  memset(results, 0, length + 1);

  long long carry_value = 0;

  // 중간 배열 -> 각 인자를 int계산이 가능한 범위로 나눠서 넣는 배열.
  char first_separates[first_length][chunk_size], second_separates[second_length][chunk_size];

  // for (int i = 0; i<4; i++){
  //   printf("배열크기 %ld", sizeof(first_separates) / sizeof(first_separates[0]));
  // }

  // 중간 배열로 나누는 처리
  split_number(first_copy, first_separates, first_chunk_num, chunk_size - 1, first_length);
  split_number(second_copy, second_separates, second_chunk_num, chunk_size - 1, second_length);

  char final_str_list[chunk_num][19];
  memset(final_str_list, 0, sizeof(final_str_list));

  for (int i = chunk_num - 1; i >= 0; i--) {
    long long sum_value = 0;
    // 나눠진 중간배열을 이용해서 덧셈진행
    // 중간 배열을 순차적으로 돌면서 first와 second의 값을 더한다.
    // 값으로 나온 숫자가 19자리 일때
    // 19자리의 수는 carry_value에 저장하고
    // 나머지 18자리의 문자열은 results에 저장하되, 가장 끝의 자리 chunk부터 저장한다.
    // 그리고 
    first_separates_int_value = get_value_of_separates(first_separates[i]);
    second_separates_int_value = get_value_of_separates(second_separates[i]);
    sum_value += first_separates_int_value + second_separates_int_value + carry_value;
    printf("합: %lld\n", sum_value);

    char sum_str[20] = {0};

    snprintf(sum_str, sizeof(sum_str), "%019lld", sum_value);
    // printf("문자열 %s\n", sum_str);
  
    remove_zeros(sum_str, carry_value);

    printf("문자열 %s\n", sum_str);
    if (strlen(sum_str) > 19) {
      carry_value = atoi(&sum_str[0]);
      memmove(sum_str, sum_str + 1, 19);
      sum_str[19] = '\0';
    } else {
      carry_value = 0;
    }
    // printf("자리올림 %lld\n", carry_value);

    // 자리 올림을 제외하고 값들을 리스트에 거꾸로 저장
    strcpy(final_str_list[i], sum_str);
  }


  // (아래 부분은 이전에 처리되기로함 혹시나 의견이 바뀌면 처리해야한다.)
  // 일단 두개의 부호를 확인한 뒤에
  // 다르면 연산을 뺄셈으로 처리한다.
  // 뺄셈 처리전에 음수 부호가 있는 문자열을 확인하고
  // 해당 문자열이 감수로 적용될 수 있도록 한다 (a - b b가 감수)

  // 두개의 부호가 같다는 가정하에 처리
  // 문자열을 나눠서 다시 저장하는게 먼저일까?
  for (int i = 0; i <= chunk_num; i++) {
    printf("%s", final_str_list[i]);
  }
  printf("\n");
  // printf("Final Result: %s\n", results);

  return first;
}

int main(void){
  printf("---------------로직 시작\n\n");
  add("+343534323566465434345555533332232323232111444434", "+8986869868969444534343434343434222345545453656565");
  return 0;
}