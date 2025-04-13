#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack* s) {
    s->top = -1;
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

void push(Stack* s, int value) {
    s->data[++(s->top)] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) return '\0';
    return s->data[(s->top)--];
}

int peek(Stack* s) {
    if (isEmpty(s)) return '\n';
    return s->data[s->top];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return -1;
}

// 중위 → 후위 변환 (postfix를 인자로 받아서 저장)
void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isdigit(ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            push(&s, ch);
        }
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
            }
            pop(&s); // '(' 버리기
        }
        else { // 연산자
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}

// 후위표기식 계산
int evaluatePostfix(char* postfix) {
    Stack s;
    initStack(&s);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isdigit(ch)) {
            push(&s, ch - '0'); // 문자 → 숫자
        }
        else { // 연산자
            int b = pop(&s);
            int a = pop(&s);
            int result;

            switch (ch) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/': result = a / b; break;
            case '%': result = a % b; break;
            default:
                printf("잘못된 연산자입니다: %c\n", ch);
                exit(1);
            }

            push(&s, result);
        }
    }

    return pop(&s);
}

// 메인 함수
int main(void) {
    char infix[MAX];
    char postfix[MAX];
    int result;

    printf("중위표기식을 입력하세요: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    result = evaluatePostfix(postfix);

    printf("후위표기식: %s\n", postfix);
    printf("계산 결과: %d\n", result);

    return 0;
}
