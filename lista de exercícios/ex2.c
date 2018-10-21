#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "helper_functions.h"


/*Program*/

int NumElementos(struct Reg *p){
    int count = 0;
    while (p != NULL){
        count++;
        p = p->prox;
    }
    printf("%d \n", count);
    return count;
}

int Pertence(struct Reg *p, int x){
    while(p != NULL){
        if (x == p->num){
            /* printf("%d PERTENCE a lista \n", x); */
            return 1;
        }
        p = p->prox;
    }  
    /* printf("%d NÃO PERTENCE a lista \n", x); */
    return 0;
}

struct Reg *Interseccao(struct Reg *p, struct Reg *q){
    struct Reg *r, *before;

    r = alocate_node();
    
    while (p != NULL){

        if (Pertence(q, p->num)){
            before = alocate_node();
            before->prox = r;
            
            if(r==NULL){
                r = alocate_node();
                r->prox = NULL;
            }
            else{
                r = before;
            }
            r->num = p->num;
        }

        p = p->prox;
    };
    return r;

}

int main (){
    int A[] = {1,2,3,6,6,6,7,8};
    int B[] = {1,2,3};
    int i, Al = 8, Bl=3, s;
    struct Reg *p, *q, *t;

    p = from_array_to_linked_list(A, Al);
    q = from_array_to_linked_list(B, Bl); 
    NumElementos(p);
    NumElementos(q);

    s = Pertence(q, 1);
    printf("%d \n", s);
    s= Pertence(q, 2);
    printf("%d \n", s);
    printf("\n");

    t = Interseccao(p, q);
    print_linked_list(t);
    
    return 0;
}
