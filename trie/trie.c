#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// struct for trie nodes

#define WORDSIZE 128
typedef struct trie {
    struct trie *next[WORDSIZE];
    bool iswordEnd;
} trie;

trie *createNode()
{
    trie *new = (trie *)malloc(sizeof(trie));
    if(new == NULL) {
        printf("No space. Malloc failed\n");
        return NULL;
    }
    for(int i=0; i<WORDSIZE; i++)
    {
        new->next[i] = NULL;
    }
    new->iswordEnd = false;
    return new;
}

void insertWord(trie *root, const char *word) {
    trie *iter = root;
    for (int i=0; word[i]!='\0'; i++) {
        unsigned char index = (unsigned char) word[i];
        if(iter->next[index] == NULL) {
            iter->next[index] = createNode();
        }
        iter = iter->next[index];
    }
    iter->iswordEnd = true;
}

bool searchWord(trie *root, const char *word) {
    trie *iter = root;
    for (int i=0; word[i]!='\0'; i++) {
        unsigned char index = (unsigned char) word[i];
        if(iter->next[index] == NULL) {
            return false;
        }
        iter = iter->next[index];
    }

    return (iter!=NULL && (iter->iswordEnd == true));
}

void deleteDB(trie **root) {
    if(*root == NULL) {
        return;
    }
    for(int i=0; i<WORDSIZE; i++)
    {
        if((*root)->next[i]!=NULL)
            deleteDB(&(*root)->next[i]);
    }
    free(*root);
    *root= NULL;
}

void PrintDB(trie *root, char *buffer, int len) {
    if(root == NULL) {
        return;
    }

    if(root->iswordEnd == true) {
        buffer[len] = '\0';
        printf("%s\n", buffer);
    }

    for(int i=0; i<WORDSIZE; i++)
    {
        if(root->next[i]!=NULL) {
            buffer[len] = (unsigned char)i;
            PrintDB(root->next[i], buffer, len+1);
        }
    }
}

int main()
{
    trie *root = createNode();
    char buffer[256] = {0};
    insertWord(root, "cat");
    insertWord(root, "car"); 
    insertWord(root, "carry");
    insertWord(root, "call");
    insertWord(root, "Est");
    insertWord(root, "Ester");

    printf("Word %s is %s\n", "carry", searchWord(root, "carry") ? "Exist": "Dont exist");
    printf("Word %s is %s\n", "call", searchWord(root, "call") ? "Exist": "Dont exist"); 
    printf("Word %s is %s\n", "xyz", searchWord(root, "xyz") ? "Exist": "Dont exist");
    printf("Word %s is %s\n", "Xkl", searchWord(root, "xyz") ? "Exist": "Dont exist");
    printf("Word %s is %s\n", "Ester", searchWord(root, "Ester") ? "Exist": "Dont exist");

    PrintDB(root, buffer, 0);
    deleteDB(&root);
    root = NULL;
    return 0;
}

