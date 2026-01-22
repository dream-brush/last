
// C언어

// 함수(Function)들로 코드를 구성하는 언어
// 함수 : 특정 기능을 구현하는 코드 단위
// C언어로 작성된 코드의 실행은 main 함수에서 시작해서 main함수에서 끝난다.

// c언어에서 문장의 끝은 반드시 ;(세미콜론)으로 마감한다!!!


#include <stdio.h>

// Entry Point(시작점)
int main()
{
    // 출력 함수
    printf("Hello World\n");

    // 변수(Variable)
    // Byte : 데이터를 처리하는 최소 단위
    // Bit : 0,1을 저장할수 있는 데이터 표현의 최소 단위
    // 1 Byte : 8bit
    // 정수 : char(1byte), short(2byte), int(4byte), long(W:4, m:8), long long(8byte)
    // 실수 : float, double, long double

    // 1bit : 0 또는 1의 두가지 데이터를 표현할 수 있다.
    // 2bit : 4가지의 서로 다른 데이터를 표현할 수 있다. 2^2
    // 00, 01, 10, 11
    // 8bit : 2^8, 256가지의 서로 다른 데이터를 표현할 수 있다.
    // 16bit : 2^16, -32,768 ~ 32,767

    // n이라는 이름의 1바이트 정수형 변수를 선언한다.
    char n; // -128 ~ 0 ~ 127
    n = 127;    // n이라는 변수에 정수 127을 대입하라.
    printf("%d\n", n);  // n에 들어있는 값을 출력하라

    n = 128;
    printf("%d\n", n);  // n에 들어있는 값을 출력하라

    // 변수 : 데이터를 일시적으로 저장하는 공간




    return 0;   
}
