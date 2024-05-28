#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char *data;
    struct node *next;
    struct node *prev;
};
typedef struct node Node;

Node *head;
Node *tail;
int size=0;

void add_node(Node *pre, char *item){
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = malloc(strlen(item) + 1);
    strcpy(new_node->data, item);
    new_node->prev = NULL;
    new_node->next = NULL;

    if(pre==NULL && head==NULL){
        head=new_node;
        tail=new_node;
    }
    else if(pre==NULL) {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    else if(pre==tail) {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    else {
        new_node->prev=pre;
        new_node->next=pre->next;
        pre->next->prev=new_node;
        pre->next=new_node;
    }
    size++;
}

void insert_at_position(int position, char *item){
    Node *p = head;
    for(int i=1; i<position; i++){
        if(p == NULL){
            printf("입력한 위치가 리스트의 길이를 초과합니다.\n");
            return;
        }
        p = p->next;
    }
    add_node(p, item);
}

void remove_node(Node *p) {
    if(head==p && tail==p) {
        head=NULL;
        tail=NULL;
    }
    else if(head==p) {
        p->next->prev=NULL;
        head=p->next;
    }
    else if(tail==p) {
        p->prev->next=NULL;
        tail=p->prev;
    }
    else{
        p->prev->next=p->next;
        p->next->prev=p->prev;
    }
    free(p->data);
    free(p);
}

void add_ordered_list(char *item) {
    Node *p = tail;
    while(p!=NULL && strcmp(p->data, item) < 0)
        p=p->prev;
    add_node(p, item);
}

void print_list() {
    Node *p = head;
    while (p != NULL) {
        printf("%s ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(void) {
    int choice, position;
    char input[100];

    while (1) {
        printf("\n1. 노드 추가\n2. 원하는 위치에 노드 추가\n3. 노드 삭제\n4. 종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("추가할 사람 이름을 입력하세요: ");
                scanf("%s", input);
                add_ordered_list(input);
                break;
            case 2:
                printf("추가할 사람 이름을 입력하세요: ");
                scanf("%s", input);
                printf("원하는 위치를 입력하세요: ");
                scanf("%d", &position);
                insert_at_position(position, input);
                break;
            case 3:
                printf("삭제할 사람 이름을 입력하세요: ");
                scanf("%s", input);
                Node *p = head;
                while (p != NULL) {
                    if (strcmp(p->data, input) == 0) {
                        remove_node(p);
                        break;
                    }
                    p = p->next;
                }
                if (p == NULL) {
                    printf("해당 이름을 가진 사람이 없습니다.\n");
                }
                break;
            case 4:
                printf("프로그램을 종료합니다.\n");
                printf("최종 리스트: ");
                print_list();
                return 0;
            default:
                printf("잘못된 입력입니다.\n");
        }
        printf("현재 리스트: ");
        print_list();
    }

    return 0;
}
/*
구조체 정의.
각 노드는 문자열 데이터를 저장하는 data와 이전 노드를 가리키는 prev 포인터, 다음 노드를 가리키는 next 포인터가 있다.
typedef를 통해 node 구조체를 Node로 재정의한다.

전역 변수로 head는 리스트의 첫번째 노드를 가리키는 포인터, tail은 마지막 노드를 가리키는 포인터다.
size는 현재 리스트에 있는 노드의 수를 저장하는 변수다.

add_node함수
pre 노드 뒤에 새 노드를 추가하는 함수. 새 노드를 할당하고 item 문자열을 복사하여 새 노드의 data에 저장함.
pre 노드가 리스트의 어디에 있는지에 따라 적절히 새 노드를 리스트에 연결

insert_at_position 함수
사용자가 입력한 위치에 새 노드를 삽입하는 함수
head부터 시작하여 position번째 노드를 찾아 add_node 함수를 호출해서 새 노드를 삽입한다.

remove_node 함수
노드를 리스트에서 제거하는 함수.
p가 어디 있는지에 따라 prev와 next 포인터를 재조정하여 p를 리스트에서 분리하고 p와 그 data를 메모리에서 해제

add_ordered_list 함수
item을 리스트에 순서대로 추가하는 함수.
리스트를 끝에서 시작하여 item이 들어갈 위치를 찾은 후 add_node 함수를 호출하여 item을 삽입함.

print_list 함수
모든 노드를 출력하는 함수.
head부터 next 포인터를 따라 리스트를 돌며 각 노드의 data를 출력함.

main 함수
여태 구현한 함수들을 바탕으로 실질적으로 굴러가는 코드 부분
메뉴 선택을 입력받고 해당하는 작업을 수행하고 현재 리스트를 출력함.
사용자가 종료하면 최종 리스트를 출력하고 종료하도록 구현함.


*/