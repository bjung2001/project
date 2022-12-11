#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct attraction {
    char name[100];
    int limit;
    int time;
    struct attraction* next;
}attraction;

char data[100];
char* scan_data(void) {
    scanf("%s", data);
    return data;
}



void menu(); 
char* scan_data(void); 
void printAll(attraction* hp); 
void add(attraction* hp, char*(*fp) (void)); 
void search(attraction* hp); 
void del(attraction* hp); 
void loadfile(attraction* hp); 
void Exit(attraction* hp);



// 주어진 노드의 올바른 정렬 위치에 주어진 노드를 삽입하는 함수
// 오름차순으로 정렬
void sortedInsert_l(struct attraction** head, struct attraction* newNode)
{
    struct attraction dummy;
    struct attraction* current = &dummy;
    dummy.next = *head;
 
    while (current->next != NULL && current->next->limit < newNode->limit) {
        current = current->next;
    }
 
    newNode->next = current->next;
    current->next = newNode;
    *head = dummy.next;
}


void sortedInsert_t(struct attraction** head, struct attraction* newNode)
{
    struct attraction dummy;
    struct attraction* current = &dummy;
    dummy.next = *head;
 
    while (current->next != NULL && current->next->time < newNode->time) {
        current = current->next;
    }
 
    newNode->next = current->next;
    current->next = newNode;
    *head = dummy.next;
}

// 목록이 주어지면 정렬된 순서로 변경.
void insertSort_l(struct attraction** head)
{
    struct attraction* result = NULL;     
    struct attraction* current = *head;   
    struct attraction* next;
 
    while (current != NULL)
    {
        next = current->next;
 
        sortedInsert_l(&result, current);
        current = next;
    }
 
    *head = result;
}

void insertSort_t(struct attraction** head)
{
    struct attraction* result = NULL;     
    struct attraction* current = *head;  
    struct attraction* next;
 
    while (current != NULL)
    {
        next = current->next;
 
        sortedInsert_t(&result, current);
        current = next;
    }
 
    *head = result;
}

//메인 함수

void main()
{
    attraction* head = (attraction*)malloc(sizeof(attraction)); 
    head->next = NULL;
    int num; 
    
    char* (*fp)(void);//함수 포인터를 인자로 전달하기 위한 코드
    fp = scan_data;

    loadfile(head); 

    while (1) {
        menu();
        scanf("%d", &num);
        if (num == 7) {
            Exit(head);
            break;
        }
        switch (num) {
        case 1:
            printAll(head);
            break;
        case 2:
            add(head, fp);
            break;
         case 3:
            search(head);
            break;
        case 4:
            del(head);
            break;
        case 5:
            insertSort_l(&head);
            printAll(head);
            break;
        case 6:
            insertSort_t(&head);
            printAll(head);
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
    printf("1. 놀이기구 명단\n");
    printf("2. 놀이기구 추가\n");
    printf("3. 놀이기구 검색\n");
    printf("4. 놀이기구 삭제\n");
    printf("5. 이용인원 오름차순 정렬\n");
    printf("6. 이용시간 오름차순 정렬\n");
    printf("7. 나가기\n");
    printf("*********************************************\n");
    printf("옵션을 선택해주세요: ");
    return;
}

//놀이기구 추가 함수
void add(attraction* hp, char*(*fp) (void)) {
    char* info; 
    attraction* temp = (attraction*)malloc(sizeof(attraction)); 
    attraction* last;
    last = hp;
    while (last->next != NULL) {
        last = last->next;
    }
    printf("-------------------추가-----------------\n");
    printf("놀이기구명: ");
    info = scan_data(); 
    strcpy(temp->name, info);
    printf("이용 인원: ");
    scanf("%d", &temp->limit);
    printf("이용 시간: ");
    scanf("%d", &temp->time);
    printf("추가되었습니다.\n");
    last->next = temp;
    temp->next = NULL;
}

//삭제 함수
void del(attraction* hp) {
    attraction* temp = hp->next;
    attraction* last = hp;
    attraction* del;
    attraction* data = (attraction*)malloc(sizeof(attraction));
    int dele = 0;
    char delname[100];
    printf("--------------------삭제--------------------\n");
    printf("삭제 놀이기구: ");
    scanf("%s", delname);
    strcpy(data->name, delname);
    while (temp != NULL) {
        if (!strcmp(temp->name, data->name)) {
            last->next = temp->next;
            del = temp;
            temp = temp->next;
            free(del);
            dele = 1;
            break;
        }
        temp = temp->next;
        last = last->next;
    }
    if (dele == 1) {
        printf("삭제되었습니다.\n");
    }
    else {
        printf("없는 데이터입니다.\n");
    }
}

//검색 함수

void search(attraction* hp) {
    int success = 0;
    int select;
    int searchlimit;
    int searchtime;
    char searchname[50];
    attraction* temp = hp->next;
    attraction* search = (attraction*)malloc(sizeof(attraction));
    search->limit = 0;
    search->time = 0;
    printf("--------------------검색--------------------\n");
    printf("무엇으로 검색하시겠습니까?\n");
    printf("1. 놀이기구 이름\n");
    printf("2. 이용 인원\n");
    printf("3. 이용 시간\n");
    printf("--------------------------------------------\n");
    printf("선택: ");
    scanf("%d", &select);
    switch (select) {
    case 1:
        printf("놀이기구 이름을 입력: ");
        scanf("%s", searchname);
        strcpy(search->name, searchname);
        while (temp != NULL) {
            if (!strcmp(temp->name, search->name)) {
                success = 1;
                printf("--------------------------------------------\n");
                printf("놀이기구이름\t이용인원\t이용시간\n");
                printf("%s\t", temp->name);
                printf("%d\t\t", temp->limit);
                printf("%d\n", temp->time);
                printf("--------------------------------------------\n");

            }
            temp = temp->next;
        }
        if (success == 0) {
            printf("--------------------------------------------\n");
            printf("해당 놀이기구가 없습니다.\n");
            printf("--------------------------------------------\n");
        }       free(search);
        break;
    case 2:
        printf("이용인원으로 찾기: ");
        scanf("%d", &searchlimit);
        while (temp != NULL) {
            if (temp->limit == searchlimit) {
                success = 1;
                printf("--------------------------------------------\n");
                printf("놀이기구이름\t이용인원\t이용시간\n");
                printf("%s\t", temp->name);
                printf("%d\t\t", temp->limit);
                printf("%d\n", temp->time);
                printf("--------------------------------------------\n");
            }
            temp = temp->next;
        }
        if (success == 0) {
            printf("--------------------------------------------\n");
            printf("검색된 이용인원이 이용하는 놀이기구는 없습니다.\n");
            printf("--------------------------------------------\n");
        }
        break;
    case 3:
        printf("이용시간으로 찾기: ");
        scanf("%d", &searchtime);
        while (temp != NULL) {
            if (temp->limit == searchtime) {
                success = 1;
                printf("--------------------------------------------\n");
                printf("놀이기구이름\t이용인원\t이용시간\n");
                printf("%s\t", temp->name);
                printf("%d\t\t", temp->limit);
                printf("%d\n", temp->time);
                printf("--------------------------------------------\n");
            }
            temp = temp->next;
        }
        if (success == 0) {
            printf("--------------------------------------------\n");
            printf("검색된 이용시간으로 운영하는 놀이기구는 없습니다.\n");
            printf("--------------------------------------------\n");
        }
        break;
    }
}

//놀이기구 명단

void printAll(attraction* hp) {
    attraction* temp = hp->next;
    while (temp != NULL) {
        printf("--------------------------------------------\n");
        printf("놀이기구이름\t이용인원\t이용시간\n");
        printf("%s\t", temp->name);
        printf("%d\t\t", temp->limit);
        printf("%d\n", temp->time);
        temp = temp->next;
    }
    printf("--------------------------------------------\n");
}


void loadfile(attraction* hp) {
    char names[50];
    int limit;
    int time;
    
    FILE* fp;
    fp = fopen("attractionlist.dat", "a+");
    
    if (fp == NULL) {
        printf("failed to open file\n");
        return;
    }
    
    attraction* temp;
    attraction* last;
    temp = (attraction*)malloc(sizeof(attraction));
    fscanf(fp, "%s %d %d", names, &limit, &time);
    //head뒤에 temp연결
    if (feof(fp) == 0) {
        temp->limit = limit;
        temp->time = time;
        strcpy(temp->name, names);
        hp->next = temp;
        temp->next = NULL;
        last = temp;
    }
    else free(temp);
    
    while (1) {
        temp = (attraction*)malloc(sizeof(attraction));
        fscanf(fp, "%s %d %d", names, &limit, &time);
        if (feof(fp) == 0) {
            temp->limit = limit;
            temp->time = time;
            strcpy(temp->name, names);
            last->next = temp;
            temp->next = NULL;
            last = temp;
        }
        else {
            free(temp);
            break;
        }
    }
    fclose(fp);
}


void Exit(attraction* hp)
{
    attraction* temp = hp->next;
    FILE* fp = fopen("attractionlist.dat", "wt");
    if (temp == NULL)
        return;
    else
    {
        while (temp != NULL)
        {
            fputs(temp->name, fp); fputs(" ", fp);
            fprintf(fp, "%d", temp->limit); fputs(" ", fp);
            fprintf(fp, "%d", temp->time); fputs("\n", fp);
            temp = temp->next;
        }
    }
    fclose(fp);
    return;
}