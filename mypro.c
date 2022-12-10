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

void menu(); //메뉴를 출력해주는 함수
char* scan_data(void); // 문자열을 입력값으로 받아 리턴해주는 함수
void printAll(attraction* hp); // 노드에 연결된 정보를 출력해주는 함수
void add(attraction* hp, char*(*fp) (void)); // 노드에 정보를 추가해주는 함수
void search(attraction* hp); // 노드로 검색하는 함수
void del(attraction* hp); // 노드를 삭제하는 함수
void loadfile(attraction* hp); // 파일에서 데이터를 노드에 저장해주는 함수
void Exit(attraction* hp); // 노드의 데이터를 파일에 저장해주는 함수

    








void main()
{
    attraction* head = (attraction*)malloc(sizeof(attraction)); //헤드 노드 생성
    head->next = NULL; //초기화
    int num; //메뉴에서 선택한 값 저장

    loadfile(head); //파일정보노드에 입력

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
            break;
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
    printf("1. 놀이기구 명단\n");
    printf("2. 놀이기구 추가\n");
    printf("3. 놀이기구 검색\n");
    printf("4. 놀이기구 삭제\n");
    printf("5. 나가기\n");
    printf("*********************************************\n");
    printf("옵션을 선택해주세요: ");
    return;
}

//놀이기구 추가 함수
void add(attraction* hp, char*(*fp) (void)) {
    char* info; // 문자열을 입력받는 함수를 호출한다.
    attraction* temp = (attraction*)malloc(sizeof(attraction)); // 입력받은 값을 저장할 노드를 생성한다.
    attraction* last;
    last = hp;
    while (last->next != NULL) {
        last = last->next;
    }
    printf("--------------------추가--------------------\n");
    printf("놀이기구명: ");
    info = scan_data(); // 문자열을 입력받을때, 호출한 함수를 이용하여 노드의 값으로 넘긴다.
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
        printf("존재하지 않는 데이터입니다.\n");
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


// 연결된 목록의 시작 부분에 새 노드를 삽입하는 도우미 함수(limit)
void push_l(struct attraction** head, int data)
{
    struct attraction* newNode = (struct attraction*)malloc(sizeof(struct attraction));
    newNode->limit = data;
    newNode->next = *head;
    *head = newNode;
}

// 연결된 목록의 시작 부분에 새 노드를 삽입하는 도우미 함수(time)
void push_t(struct attraction** head, int data)
{
    struct attraction* newNode = (struct attraction*)malloc(sizeof(struct attraction));
    newNode->time = data;
    newNode->next = *head;
    *head = newNode;
}
 
// 주어진 노드의 올바른 정렬 위치에 주어진 노드를 삽입하는 함수
// 오름차순으로 정렬된 리스트
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
 
// 목록이 주어지면 정렬된 순서로 변경합니다(`sortedInsert()` 사용).
void insertSort_l(struct attraction** head)
{
    struct attraction* result = NULL;     // 여기에 답을 작성합니다.
    struct attraction* current = *head;   // 원래 목록을 반복합니다.
    struct attraction* next;
 
    while (current != NULL)
    {
        // 까다로운: 변경하기 전에 다음 포인터를 확인합니다.
        next = current->next;
 
        sortedInsert(&result, current);
        current = next;
    }
 
    *head = result;
}





































void loadfile(attraction* hp) {
    //파일 내용 연결리스트에 저장
    char names[50];
    int limit;
    int time;
    //파일 오픈
    FILE* fp;
    fp = fopen("attractionlist.dat", "a+");
    //파일 실행 실패
    if (fp == NULL) {
        printf("failed to open file\n");
        return;
    }
    //파일 실행 성공
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
    //temp뒤에 temp생성
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

//파일에 데이터 업데이트
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

*/