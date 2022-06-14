#include <stdio.h>
#include <stdlib.h>
#define N 8

enum STATUS 
{
    FINE = 0,
    UNKNOWN_ERR = 1,
    ALLOC_ERR = 2,
    NULL_REF = 3,
    IND_OUT_OF_RANGE = 4,
    NEG_IND = 5,
};


typedef struct int_list_node
{
    int data;
    struct int_list_node *next;
    struct int_list_node *prev;
}IntNode;


typedef struct int_linked_list
{
    IntNode *head;
    int length;
}IntLinkedList;



enum STATUS CreateIntList(IntLinkedList **ptr)
{
    enum STATUS status = FINE;
    *ptr = malloc(sizeof(*ptr));
    if (NULL == ptr){
        status = ALLOC_ERR;
    }else{
        (*ptr) -> length = 0;
        (*ptr) -> head = NULL;
    }
    return status;
}

enum STATUS ListAdd(IntLinkedList *list, int value)
{
    enum STATUS status = FINE;
    IntNode *node = NULL, *curr_node = NULL;

    node = malloc(sizeof(*node));

    if (NULL == list){
        status = NULL_REF;
    }else if(NULL == node){
        status = ALLOC_ERR;
    }

    if (FINE == status){
        node -> data = value;
        node -> next = NULL;
        curr_node = list -> head;
        if(curr_node == NULL){
            node -> prev = NULL;
            list -> head = node;
        }else{
            while (NULL != curr_node -> next){
                curr_node = curr_node -> next;
            }
            curr_node -> next = node;
            node -> prev = curr_node;
        }
        (list -> length) ++;
    }
    return status;
}

enum STATUS ListGet(int* target, IntLinkedList* list, int index)
{
    enum STATUS status = FINE;
    IntNode *curr_node = NULL;


    if (NULL == list){
        status = NULL_REF;
    }else if (list -> length <= index){
        status = IND_OUT_OF_RANGE;
    }else if (index < 0){
        status = NEG_IND;
    }

    if (FINE == status){
        curr_node = list -> head;
        for(;index > 0; index--){
            curr_node = curr_node -> next;
        }
        *target = curr_node -> data;
    }
    return status;
}

/* NODE MUST BE IN LIST*/

enum STATUS ListDetachNode(IntLinkedList *list, IntNode *node)
{
    enum STATUS status = FINE;
    if (NULL == list || NULL == node){
        status = NULL_REF;
    }
    if(FINE == status){
        if(list -> head == node)
            list -> head = list -> head -> next;
                
        if (node -> prev != NULL)
            node -> prev -> next = node -> next;

        if (node -> next != NULL)
            node -> next -> prev = node -> prev;
        
        (list -> length) --;

    }

    return status;
}

enum STATUS ListRemoveInstancesOf(IntLinkedList *list, int value)
{
    enum STATUS status = FINE;
    IntNode *curr_node = NULL, *temp = NULL;
    if (NULL == list){
        status = NULL_REF;
    }
    if (FINE == status){
        curr_node = list -> head;
        while(NULL != curr_node){
            if (value == curr_node -> data){

                temp = curr_node;

                status = ListDetachNode(list, temp);
                if (FINE != status)
                    break;
                
                curr_node = curr_node -> next;

                free(temp);
                
                
            }
            else{
                curr_node = curr_node -> next;
            }
        }
    }

    return status;
}

enum STATUS ListRemoveIndex(IntLinkedList *list, int index)
{
    enum STATUS status = FINE;
    IntNode *curr_node = NULL, *temp = NULL;

    if (NULL == list){
        status = NULL_REF;
    }else if (list -> length <= index){
        status = IND_OUT_OF_RANGE;
    }else if (index < 0){
        status = NEG_IND;
    }
    if (FINE == status){
        curr_node = list -> head;
        for(;index > 0; index--){
            curr_node = curr_node -> next;
        }

        status = ListDetachNode(list, curr_node);
        free(curr_node);

    }
    return status;
}

enum STATUS ListFromArray(IntLinkedList **ptr, int *array, int array_len)
{
    enum STATUS status = FINE;
    int index = 0;
    IntNode *node = NULL, *prev_node = NULL;
    status = CreateIntList(ptr);

    if (FINE == status){
        (*ptr) -> length = array_len;
        for(;index < array_len; index++){
            node = malloc(sizeof(*node));
            if (0 == index){
                (*ptr) -> head = node;
            }
            if (NULL == node){
                status = ALLOC_ERR;
                break;
            }
            node -> data = *(array + index);
            node -> prev = prev_node;
            if (NULL != prev_node)
                prev_node -> next = node;
            node -> next = NULL;
            prev_node = node;
        }
    }

    return status;
}

enum STATUS DeleteNodes(IntNode *node){
    if (NULL != node){
        DeleteNodes(node -> next);
        free(node);
    }
}

enum STATUS DeleteList(IntLinkedList *list)
{
    enum STATUS status = FINE;

    int cont = 1;
    if (NULL == list || 0 == list -> length){
        cont = 0;
    }
    if (cont){
        DeleteNodes(list -> head);
        list -> head = NULL;
        free(list);
    }

    return status;
}

enum STATUS PrintList(IntLinkedList *list)
{
    enum STATUS status = FINE;
    IntNode *curr = NULL;

    if (NULL == list){
        status = NULL_REF;
    }

    if (FINE == status){
        printf("[");
        curr = list -> head;
        while (NULL != curr){
            printf("%d", curr -> data);
            if (NULL != curr -> next){
                printf(",");
            }
            curr = curr -> next;
        }
        printf("]\n");
    }
    return status;
}

void handler(enum STATUS status){
    switch(status)
    {
        case FINE:
            break;
        
        case ALLOC_ERR:
            printf("Allocation Error !");
            exit(2);

        case NULL_REF:
            printf("Null reference error !");
            exit(3);
        
        case IND_OUT_OF_RANGE:
            printf("index out of range !");
            exit(4);
        
        case NEG_IND:
            printf("index is negative !");
            exit(5);

    }
}
/*
int main(void)
{
    int i = 0;
    IntLinkedList *list = NULL;
    int arr[5] = {1,5,9,5,1};
    
    handler(CreateIntList(&list));
    if (NULL == list){
        printf("CREATE FAILED\n");
    }
    for (;i < N; i++){
        handler(ListAdd(list, i));
    }
    
    handler(PrintList(list));
    handler(DeleteList(list));
    handler(ListFromArray(&list, arr, 5));
    handler(PrintList(list));
    handler(ListRemoveIndex(list, 4));
    handler(PrintList(list));
    printf("%d\n", list -> length);
    handler(ListRemoveInstancesOf(list, 5));
    handler(PrintList(list));
    printf("%d\n", list -> length);
    handler(DeleteList(list));
    
    printf("completed");
}

*/
