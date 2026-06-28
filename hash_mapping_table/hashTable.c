#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ARRAY 128

typedef struct Node {
    int productPrice;
    char *productName;
    struct Node *next;
} Node;

Node *table[MAX_ARRAY] = {};

uint32_t hashGenerate(char *key) {
    uint32_t value = 5381;
    while(*key != '\0'){
        value = (value * 31) + *key;
        key++;
    }

    return (value % MAX_ARRAY);
}

void buildHashTable(char *productName, int productValue)
{
    if(productName == NULL)
        return ;

    uint8_t index = hashGenerate(productName);
    Node *new = table[index];
    if(new != NULL) {
        while(new != NULL) {
            if(!strcmp(productName, new->productName)) {
                new->productPrice = productValue;
                return;
            }
            new = new->next;
        }
    }
    new = (Node *)malloc(sizeof(Node));
    if(new == NULL) {
        printf("Malloc Failed\n");
    }
    new->productName = strdup(productName);
    new->productPrice = productValue;
    new->next = NULL;

    if(table[index] != NULL) {
        new->next = table[index];
        table[index] = new;
    } else {
        table[index] = new;
    }
}

void hashTableLook(char *productName)
{
    uint32_t index = hashGenerate(productName);
    Node *node = table[index];
    if(node != NULL) {
        while (node !=NULL) {
            if(!strcmp(productName, node->productName)) {
                printf("Price of %s is Rs.%d\n", node->productName, node->productPrice);
                return;
            }
            node = node->next;
        }
    } else {
        printf("Product {%s} doesn't exist\n", productName);
    }
}

void deleteTable()
{
    int index = 0;
    for (index =0; index<MAX_ARRAY; index++)
    {
        Node *tmp = table[index];
        if(tmp != NULL) {
            while(tmp!=NULL)
            {
                Node *clear = tmp;
                tmp = tmp->next;
                free(clear->productName);
                free(clear);
            }
        }
    }
}

void deleteByItem(char *productName)
{
    uint32_t index = hashGenerate(productName);
    Node *delete = table[index];
    Node *tmp = NULL;
    bool isFirstNode = true;
    if(delete != NULL) {
        while(delete != NULL) {
            if(!strcmp(delete->productName, productName)) {
                if(isFirstNode) {
                    tmp = delete;
                    delete = delete->next;
                    free(tmp->productName);
                    free(tmp);
                    table[index] = delete;
                } else
                {
                    tmp->next = delete->next;
                    free(delete);
                }
                break;
            }
            if(isFirstNode)
                isFirstNode = false;

            tmp = delete;
            delete = delete->next;
        }
    }
}

void dumpTable()
{
    int index = 0;
    printf("Dumping product details:\n");
    for (index =0; index<MAX_ARRAY; index++)
    {
        Node *tmp = table[index];
        int count  = 0;
        if(tmp != NULL) {
            while(tmp!=NULL)
            {
                count ++;
                printf("    Price of %s is Rs.%d\n", tmp->productName, tmp->productPrice);
                tmp = tmp->next;
            }
        }
    }

}

int main(int argc, char *argv[]) {

    buildHashTable("Apple", 10);
    buildHashTable("Egg", 11);
    buildHashTable("straberry", 9);
    buildHashTable("Mango", 13);
    buildHashTable("Orange", 15);
    buildHashTable("Mulberry", 12);
    buildHashTable("elppA", 16);
    deleteByItem("Apple");
    deleteByItem("Mango");
    if (argc > 1)
    {
        if (!strcmp(argv[1], "dump"))
            dumpTable();

        deleteTable();
        return 0;
    }

    hashTableLook("Egg");
    hashTableLook("Idle");
    hashTableLook("Mango");
    hashTableLook("Mulberry");

    deleteByItem("elppA");
    deleteByItem("elppA");
 
    deleteTable();
    return 0;
}
