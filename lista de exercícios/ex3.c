#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "helper_functions.h"

struct Reg *RemoveNum(struct Reg *p, int a){
    struct Reg *t, *at;
    at = alocate_node();
    t = p;
    while(t!=NULL){
        if(p->num == a){
            p = p->prox;
            free(t);
            t = p;
        }
        else if(t->num == a){
            at->prox = t->prox;
            free(t);
            t = at->prox;
        }
        else{
            at = t;
            t=t->prox;
        }
    }
    return p;
}

struct Reg *RemoveRepetidos(struct Reg *p){
    struct Reg* t;
    t = p;
    while(t!=NULL){
        t->prox = RemoveNum(t->prox, t->num);
        t = t->prox;
    }
    return p;
}

int main(){
    int A[] = {1,2,2,2,2,2,2,2,3,3,3,3,0,4,5,5,6,6,6,7,8,8};
    int B[] = {1,2,3};
    int i, Al = 20, Bl=3, s;
    struct Reg *p, *q, *t;

    p = from_array_to_linked_list(A, Al);
    q = from_array_to_linked_list(B, Bl);

    /* t = RemoveNum(p, 6); */
    t = RemoveRepetidos(p);
    print_linked_list(t);

    return 0;
}