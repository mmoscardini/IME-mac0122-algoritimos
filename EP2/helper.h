#include <stdio.h>
#include <stdlib.h>

typedef struct _RegPilha{
 int dado;
 struct _RegPilha *prox;
} RegPilha;
typedef RegPilha* Pilha;
typedef enum boolean {false,true} bool;

RegPilha *AlocaRegPilha(){
 RegPilha* q;
 q = (RegPilha*)calloc(1, sizeof(RegPilha));
 if(q==NULL) exit(-1);
 return q;
}

Pilha CriaPilha(){
 Pilha p;
 p = AlocaRegPilha();
 p->prox = NULL;
 return p;
}

void LiberaPilha(Pilha p){
 RegPilha *q,*t;
 q = p;
 while(q!=NULL){
 t = q;
 q = q->prox;
 free(t);
 }
}

bool PilhaVazia(Pilha p){
 return (p->prox==NULL);
}

void Empilha(Pilha p, int x){
 printf("empilha %d\n", x);
 RegPilha *q;
 q = AlocaRegPilha();
 q->dado = x;
 q->prox = p->prox;
 p->prox = q;
}

int Desempilha(Pilha p){
 RegPilha *q;
 int x;
 q = p->prox;
 if(q==NULL) exit(-1);
 x = q->dado;
 p->prox = q->prox;
 free(q);
 return x;
}

void PrintPilha(Pilha p){
 printf("[");
 while(p!=NULL){
    printf("%d ", p->dado);
    p = p->prox;
 }
 printf("]\n");
}

/* FILAS */
typedef struct _RegFila{
 int dado;
 struct _RegFila *prox;
} RegFila;
typedef RegFila* Fila;

RegFila *AlocaRegFila(){
 RegFila* q;
 q = (RegFila*)calloc(1, sizeof(RegFila));
 if(q==NULL) exit(-1);
 return q;
}

Fila CriaFila(){
 Fila p;
 p = AlocaRegFila();
 p->prox = p;
 return p;
}

void LiberaFila(Fila p){
 RegFila *q,*t;
 q = p->prox;
 while(q!=p){
 t = q;
 q = q->prox;
 free(t);
 }
 free(p);
}

bool FilaVazia(Fila p){
 return (p==p->prox);
}

void InsereFila(Fila *p, int x){
 RegFila *q;
 q = AlocaRegFila();
 q->dado = x;
 q->prox = (*p)->prox;
 (*p)->prox = q;
 *p = q;
}

int RemoveFila(Fila *p){
 RegFila *q,*t;
 int x;
 q = (*p)->prox;
 if(q==*p) exit(-1); /* Fila Vazia */
 t = q->prox;
 x = t->dado;
 q->prox = t->prox;
 if(t==*p) *p = q;
 free(t);
 return x;
}