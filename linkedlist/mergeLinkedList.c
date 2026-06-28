#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;


Node *createNode(int val)
{
    Node *new = NULL;
    new = (Node *)malloc(sizeof(Node));

    if(new != NULL) {
        new->val = val;
        new->next = NULL;
    } else {
        printf("Malloc failed to create Memory\n");
    }

    return new;
}

Node *mergeNode (int arr1[], int size1,  int arr2[], int size2)
{
    Node dummy = { .val=0, .next = NULL };
    Node *cur = &dummy;
    int arrindex1 = 0, arrindex2 = 0;
    while(size1 > arrindex1 && size2 > arrindex2){
            if(arr1[arrindex1] > arr2[arrindex2]) {
                cur->next = createNode(arr2[arrindex2]);
                arrindex2++;
            } else {
                cur->next = createNode(arr1[arrindex1]);
                arrindex1++;
            }
            cur = cur->next;
    }
    return dummy.next;
}

void printNode_Delete(Node *list)
{
    Node *tmp = NULL;
    while(list != NULL) {
        printf(" %d\n", list->val);
        tmp = list;
        list = list->next;
        free(tmp);
    }
    list = NULL;
}
int main()
{
    int arr1[] = {2,4,6,8,10};
    int arr2[] = {1,3,5,7,9};
    int size1 = sizeof(arr1)/sizeof(arr1[0]);
    int size2 = sizeof(arr2)/sizeof(arr2[0]);
    Node *list = mergeNode(arr1, size1, arr2, size2);
    printNode_Delete(list);
    return 0;
}
