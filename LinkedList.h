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

enum STATUS CreateIntList(IntLinkedList **ptr);

enum STATUS ListAdd(IntLinkedList *list, int value);

enum STATUS ListGet(int* target, IntLinkedList* list, int index);

enum STATUS ListRemoveInstancesOf(IntLinkedList *list, int value);

enum STATUS ListRemoveIndex(IntLinkedList *list, int index);

enum STATUS ListFromArray(IntLinkedList **ptr, int *array, int array_len);

enum STATUS DeleteList(IntLinkedList *list);

enum STATUS PrintList(IntLinkedList *list);
