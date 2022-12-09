#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct attraction {

    char name[100];
    int limit;
    int time;
    struct Class* next;
}attraction;

char data[100];
char* scan_data(void) {
    scanf("%s", data);
    return data;

}
    








void main()
{
    attraction* head = (attraction*)malloc(sizeof(attraction));
    head->next = NULL;
    int num;

    loadfile(head);

    while (1) {
        menu();
        scanf("%d", &num);
        if (num == 5) {
            Exit(head);
            break;
        }
        switch (num) {
        case 1:
            printAll(head);
            break;
        case 2:
            add(head, scan_data);
         case 3:
            search(head);
            break;
        case 4:
            del(head);
            break;

        default:
            printf("잘못된 선택입니다.\n");
            break;
        }
    }
    attraction* node = head;
    attraction* del;
    while (node != NULL) {
        del = node;
        node = node->next;
        free(del);
    }
}

void menu()
{
    printf("*********************************************\n");
    printf("1. 놀이기구 추가\n");
    printf("2. 놀이기구 삭제\n");
    printf("3. 놀이기구 검색\n");
    printf("놀이")
}
