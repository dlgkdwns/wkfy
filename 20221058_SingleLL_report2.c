#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Contact {
    char name[30];
    char phone[20];
    struct Contact* next;
} Contact;


Contact* addContact(Contact* head, const char* name, const char* phone) {
    Contact* newNode = (Contact*)malloc(sizeof(Contact));
    if (newNode == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = head; // 앞에 삽입
    return newNode;
}


void searchContact(Contact* head, const char* name) {
    Contact* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf(" %s 님의 전화번호: %s\n", current->name, current->phone);
            return;
        }
        current = current->next;
    }
    printf(" \"%s\" 님을 찾을 수 없습니다.\n", name);
}


Contact* deleteContact(Contact* head, const char* name) {
    if (head == NULL) return NULL;

    if (strcmp(head->name, name) == 0) {
        Contact* temp = head;
        head = head->next;
        free(temp);
        printf(" \"%s\" 님의 연락처 삭제 완료.\n", name);
        return head;
    }

    Contact* current = head;
    while (current->next != NULL && strcmp(current->next->name, name) != 0) {
        current = current->next;
    }

    if (current->next == NULL) {
        printf(" \"%s\" 님을 찾을 수 없습니다.\n", name);
        return head;
    }

    Contact* temp = current->next;
    current->next = current->next->next;
    free(temp);
    printf("🗑️ \"%s\" 님의 연락처 삭제 완료.\n", name);
    return head;
}


void printContacts(Contact* head) {
    printf("\n 전화번호부 목록:\n");
    if (head == NULL) {
        printf(" 비어 있습니다.\n");
        return;
    }
    Contact* current = head;
    while (current != NULL) {
        printf("- %s: %s\n", current->name, current->phone);
        current = current->next;
    }
}


void freeContacts(Contact* head) {
    Contact* current;
    while (head != NULL) {
        current = head;
        head = head->next;
        free(current);
    }
}


int main() {
    Contact* phoneBook = NULL;
    int choice;
    char name[30];
    char phone[20];

    while (1) {
        printf("\n=== 전화번호부 관리 시스템 ===\n");
        printf("1. 새로운 연락처 추가\n");
        printf("2. 이름으로 연락처 검색\n");
        printf("3. 이름으로 연락처 삭제\n");
        printf("4. 전체 연락처 출력\n");
        printf("5. 종료\n");
        printf("선택 >> ");
        scanf("%d", &choice);
        getchar(); // 입력 버퍼 정리

        switch (choice) {
        case 1:
            printf("이름 입력: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            printf("전화번호 입력: ");
            fgets(phone, sizeof(phone), stdin);
            phone[strcspn(phone, "\n")] = 0;

            phoneBook = addContact(phoneBook, name, phone);
            printf(" 연락처가 추가되었습니다.\n");
            break;

        case 2:
            printf("검색할 이름 입력: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;
            searchContact(phoneBook, name);
            break;

        case 3:
            printf("삭제할 이름 입력: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;
            phoneBook = deleteContact(phoneBook, name);
            break;

        case 4:
            printContacts(phoneBook);
            break;

        case 5:
            freeContacts(phoneBook);
            printf(" 프로그램을 종료합니다.\n");
            return 0;

        default:
            printf(" 올바른 번호를 입력하세요 (1~5).\n");
        }
    }
}
