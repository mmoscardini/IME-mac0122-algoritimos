/* header_file.h */
#ifndef HEADER_FILE
#define HEADER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Reg{
    int num;
    struct Reg *prox;
};

extern struct Reg *alocate_node(){
    struct Reg *p;  

    p = (struct Reg *)malloc(sizeof(struct Reg*));
    if (p == NULL){
        printf("Erro ao alocar memoria");
    }
    return p;
}

extern void print_linked_list(struct Reg *p){
    while(p != NULL){
        printf("%d ", p->num);
        p = p->prox;
    }   
    printf("\n");
}

extern struct Reg *from_array_to_linked_list(int A[], int n){
    int i;
    struct Reg *curr, *before;

    curr = alocate_node();
    
    for (i=n-1;i>=0;i--){
        if (curr == NULL)
            curr = alocate_node();
        before = alocate_node();
        curr->num = A[i];
        before->prox = curr;
        if(i == 0) break;
        curr = before;
    };
    return curr;
}

#endif