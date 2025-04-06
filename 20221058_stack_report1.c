#include <stdio.h>
#include <stdlib.h>

#define MAX 100 // 스택의 최대 크기 정의

typedef struct {
	int data[MAX];
	int top; //스택의 최상단 요소를 가르키는 인덱스
} Stack;

// 스택 초기화 함수
void initStack(Stack* s) {
	s->top = -1;
}
// 스택이 비어있는지 확인
int isEmpty(Stack* s) {
	return s->top == -1;
}
// 스택이 가득 찼는지 확인
int isFull(Stack* s) {
	return s->top == MAX - 1;
}
void push(Stack* s, int value) {
	if (isFull(s)) {
		printf("Stack overFlow! cannot push %d\n", value);
		return;
	}
	s->data[++(s->top)] = value;
}

int pop(Stack* s) {
	if (isEmpty(s)) {
		printf("Stack is underfolw cannot pop %d\n");
		return -1;
	}
	return s->data[(s->top)--];
}
int peek(Stack* s) {
	if (isEmpty(s)) {
		printf("Stack is empty! Cannot peek\n");
		return -1;
	}
	return s->data[s->top];
}
void display(Stack* s) {
	if (isEmpty(s)) {
		printf("Stack is empty!\n");
		return;
	}
	printf("Stack contents:");
	for (int i = 0; i <= s->top; i++) {
		printf("%d ", s->data[i]);
	}
	printf("\n");
}
int main() {
	Stack s;
	initStack(&s);

	char korean[100];

	printf("문자열을 입력하시오:");
	fgets(korean, sizeof(korean), stdin);
	

	for (int i = 0; korean[i] != '\0'; i++) {
		push(&s, korean[i]);
	}

	printf("역순 출력:");
	while (!isEmpty(&s)) {
		printf("%c", pop(&s));

	}
	printf("\n");

	return 0;
}
