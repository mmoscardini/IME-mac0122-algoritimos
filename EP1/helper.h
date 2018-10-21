#include <stdio.h>
#include <stdlib.h>

struct Termo{
  float coef;
  int expo;
  struct Termo *prox;
};
 
typedef struct Termo* Polinomio;

struct Termo *AlocaTermo(){
  struct Termo *p;
  p = (struct Termo*)malloc(sizeof(struct Termo));
  if(p == NULL)
    exit(1);
  return p;
};

Polinomio CriaPolinomioNulo(){
  Polinomio p;
  p = AlocaTermo();
  p->coef = 0.0;
  p->expo = -1;
  p->prox = p;
  return p;
};

void InsereTermo(Polinomio p, float coef, int expo){
  struct Termo *t, *at,*q;
  /* Aloca memória para o novo termo: */
  q = AlocaTermo();
  q->coef = coef;
  q->expo = expo;
  /* Busca a posição correta para inserir o novo termo,
     O novo termo será inserido entre os termos apontados 
     por at e t.
  */
  at = p;
  t = p->prox;
  while(expo < t->expo){
    at = t;
    t = t->prox;
  }
  q->prox = t;
  at->prox = q;
};

void ImprimePolinomio(Polinomio p){
if(p == p->prox){
  printf("%d\n", 0);
  return;
}
struct Termo *t;
t = p->prox;
while(t != p){
  printf("%.2f*x^%d",t->coef,t->expo);
  t = t->prox;
  if(t != p){
    if(t->coef >= 0.0)
    printf("+");
  }
}

printf("\n");
};

Polinomio CriaPolinomio(char expr[]){
  Polinomio p;
  int expo,r,n,nn;
  float coef,sinal = 1.0;
  char c;
 
  nn = 0;
  p = CriaPolinomioNulo();
  while(1){
    r = sscanf(expr+nn," %f * x ^ %d %n",&coef, &expo,&n);
    if(r == 0 || r == EOF) 
      break;
    nn += n;
 
    InsereTermo(p, sinal*coef, expo);
     
    r = sscanf(expr+nn,"%c %n",&c,&n);
    if(r == EOF || r == 0)
      break;
    nn += n;
 
    if(c == '-')
      sinal = -1.0;
    else
      sinal = 1.0;
  }
  return p;
}
