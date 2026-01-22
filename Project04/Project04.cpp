#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main()
{
	// 연산자: operators
	//
	// 1. 산술연산자: +, -, *, /, %
	// 2. 대입연산자: =, +=, -=, *=, /=, %=
	// 3. 증감연산자: ++, --
	// 4. 비교연산자: >, >=, <, <=, ==, !=
	// 5. 논리연산자: &&, ||, !
	// 6. 삼항연산자: ? :
	// 7. 비트연산자: <<, >>, &, |, ^, ~

	int n1 = 5;
	int n2 = 3;
	int n3 = n1 + n2;	
	printf("%d + %d = %d\n", n1, n2, n3);

	n3 = n1 - n2;
	printf("%d - %d = %d\n", n1, n2, n3);

	n3 = n1 * n2;
	printf("%d * %d = %d\n", n1, n2, n3);

	n3 = n1 / n2;
	printf("%d / %d = %d\n", n1, n2, n3);

	float f1 = n1 / (float)n2;
	printf("%d / %d = %f\n", n1, n2, f1);

	n3 = n1 % n2;
	printf("%d %% %d = %d\n", n1, n2, n3);

	// 대입연산자
	n3 = n1;	// n1에 있는 값을 n3에 대입시켜라
	n3 += n1;	// n3 = n3 + n1;
	printf("n1 = %d, n3 = %d\n", n1, n3);

	n3 -= n1;	// n3 = n3 - n1;
	n3 *= n1;	// n3 = n3 * n1;
	n3 /= n1;	// n3 = n3 / n1;
	n3 %= n1;	// n3 = n3 % n1;

	// 증감연산자: ++, --
	n1 = 0;
	n1++;	// n1 = n1 + 1;
	n1--;	// n1 = n1 - 1;
	++n1;	// n1 = n1 + 1;
	--n1;	// n1 = n1 - 1;
	//printf("정수를 입력하세요: ");
	//scanf("%d", &n1);
	printf("입력값: %d\n", n1);
	printf("n1++ ==> %d\n", n1++);	// 10 ==> 11, post-fix
	printf("n1++ ==> %d\n", n1++);	// 11 ==> 12
	printf("++n1 ==> %d\n", ++n1);	// 13 ==> 출력(13), pre-fix
	printf("n1 = %d\n", n1);		// 13

	// 비교(관계) 연산자 : 연산의 결과는 참 또는 거짓이다.
	n1 = 5;
	n2 = 3;	
	n3 = n1 < n2;	// 거짓
	n3 = n1 > n2;	// 참(0이아닌 값이 저장)
	printf("n3 = %d\n", n3);
	printf("%d == %d 의 결과? %d\n", n1, n2, n1 == n2);
	printf("%d != %d 의 결과? %d\n", n1, n2, n1 != n2);

	// 논리연산자 : &&(and), ||(or), !(not), 연산의 결과는 참 또는 거짓이다.
	n3 = n1 > n2 && n1 == n2;	// 0
	printf("%d > %d && %d == %d 의 결과? %d\n", n1, n2, n1, n2, n3);
	n3 = n1 > n2 || n1 == n2;	// 1
	printf("%d > %d || %d == %d 의 결과? %d\n", n1, n2, n1, n2, n3);
	n3 = !(n1 == n2);
	printf("!(%d == %d)의 결과? %d\n", n1, n2, n3);

	// 삼항 연산자
	// 조건식(관계식, 논리식, 산술식) ? 조건식이 참일때 반환값 : 조건식이 거짓일때 반환값;
	printf("%s", n1%2 ? "홀수":"짝수");
	n3 = n1 % 2 ? 1 : -1;



	return 0;	// 즉시 함수를 종료시킨다.
}