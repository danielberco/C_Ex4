

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUM_LETTERS 26

typedef struct Node{
    char letter;
    int last;
    struct Node* child[NUM_LETTERS];
    int pos;
} Node;


Node* addNode(char c){
    Node* n = (Node*)malloc(sizeof(Node));
    if(n == NULL) exit(1);
    n->letter = c;
    return n;
}

//Adding a new word
void addWord(Node* root, char* str){
    int i = -1;
    while(*str){
        char current = tolower(*str); //lower case
        if(root->child[current - 'a'] == NULL){
            root->child[current - 'a'] = addNode(current);
            root->pos = i;
        }
        root = root->child[current - 'a'];
        str++;
        i++;
        if(!*str){
            root->last++;
            root->pos = i;
        }
    }
}

void printTrie(Node* root, char *str) {
    if (root == NULL) return;
    str[root->pos] = root->letter;
    if (root->last) {
        str[root->pos + 1] = 0;
        printf("%s %d\n", str, root->last);
    }
    for (int i = 0; i < NUM_LETTERS; i++) {
        printTrie(root->child[i], str);
    }
}

//Printing reversed trie
void printRevTrie(Node* root, char *str){
    if(root == NULL) return;
    str[root->pos] = root->letter;
    for (int i = NUM_LETTERS-1 ; i >= 0; i--){
        printRevTrie(root->child[i], str);
    }
    if(root->last){
        str[root->pos + 1] = 0;
        printf("%s %d\n", str, root->last);
    }
}


void freeMemory(Node* root){
    if(root == NULL) return;
    for (int i = 0; i < NUM_LETTERS; i++){
        freeMemory(root->child[i]);
    }
    free(root);
}

int main(int argc, char const *argv[])
{
    Node* root = addNode(0);
    int i = 0;
    char *str = (char*)malloc(1);
    while(1)
    {
        char c = getchar();
        if(isspace(c) || c == EOF){
            str = realloc(str, i+1);
            str[i] = 0;
            addWord(root, str);
            i=0;

            if(c == EOF) break;
        }
        else if(isalpha(c)){ //checking lower case
            c = tolower(c);
            str = realloc(str, i+1);
            str[i] = c;
            i++;
        }
    }

    if(argc == 1)
        printTrie(root, str);
    else if(argc == 2 && strcmp(argv[1],"r")==0)
        printRevTrie(root, str);

    free(str);
    freeMemory(root);
    return 0;
}
