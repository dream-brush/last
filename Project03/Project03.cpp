#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
    // clang, gcc, g++
    // 
    // c-compiler: msvc, 표준+a
    short n;
    char ch;

    printf("정수를 입력하세요: ");
    scanf("%hd", &n);
    printf("%s\n", n % 2 ? "홀수" : "짝수");

    scanf("%c", &ch);   // 입력버퍼 낭비시키기

    // 표준 입력 장치로부터 입력을 받아 변수 n에 저장
    printf("문자를 입력하세요: ");    
    // scanf("%hhd", &ch); // & 엠퍼센드, | 파이프라인
    scanf("%c", &ch);
    printf("입력된 문자: %c\n", ch);
    printf("ch에 저장된 값: %hhd\n", ch);

    return 0;
}
