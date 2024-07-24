#include <stdio.h>

int get_size(int length){
  // int size = (length % 32) ? length / 32 + 1 : length / 32;
  // return size;
  return (length + 31) / 32;
}
// 두개의 문자열을 인자로 받는다.
// 하나의 문자열을 반환한다.
// 문자열의 크기를 알아야하나?

// 리턴이 가능하도록 포인터를 이용해본다.
// const를 적용시켜서 함수내에서 바뀌지않음을 보장한다.
char* add(const char* first, const char* second){
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
  const int first_length = strlen(first), second_length = strlen(second);
  const int first_size = get_size(first_length), second_size = get_size(second_length);

  int length = (first_length > second_length) ? first_length : second_length;
  char result[length];
  memset(result, 0, length);

  int carry_value = 0;

  // 중간 배열 -> 각 인자를 int계산이 가능한 범위로 나눠서 넣는 배열.
  char first_separates[first_length][first_size], second_separates[second_length][second_size];

  // 일단 두개의 부호를 확인한 뒤에
  // 다르면 연산을 뺄셈으로 처리한다.
  // 뺄셈 처리전에 음수 부호가 있는 문자열을 확인하고
  // 해당 문자열이 감수로 적용될 수 있도록 한다 (a - b b가 감수)

  // 두개의 부호가 같다는 가정하에 처리
  // 문자열을 나눠서 다시 저장하는게 먼저일까?

  
}