#include <stdio.h>

int main()
{
	int scores[10];
	int sum = 0;
	double average;

	printf("학생 10명의 성적을 입력하시오");
	for (int i = 0; i < 10; i++) {
		printf("학생 %d의 성적:", i + 1);
		scanf_s("%d", &scores[i]);
		sum += scores[i];
	}
	average = sum / 10.0;
	printf("학생들의 평균은 %.2f 입니다.\n", average);

	return 0;


}
