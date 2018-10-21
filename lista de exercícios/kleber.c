#include <stdio.h>
#include <stdlib.h>

float potencia (float base, int exp){
    float pot = 1; int i = 0;
    while(i < exp){pot = pot*base; i++;} return pot;
}
struct Termo {
    float coef;
    int expo;
    struct Termo *prox;
} ;
typedef struct Termo* Polinomio;

struct Termo *AlocaTermo(){

  struct Termo *p;
  p = (struct Termo*)malloc(sizeof(struct Termo));
  if(p == NULL)
    exit(1);
  return p;
}
Polinomio CriaPolinomioNulo(){
  Polinomio p;
  p = AlocaTermo();
  p->coef = 0.0;
  p->expo = -1;
  p->prox = p;
  return p;
}

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
}

Polinomio CriaPolinomio(char expr[]){  Polinomio p;
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

void ImprimePolinomio(Polinomio p){
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
}

float Valor(Polinomio p, float x){
    struct Termo *q;
    struct Termo *t;
    float n = 0;
    q = p->prox;

    while (q != p){
        n = n + (q->coef)*(potencia(x, q->expo));
        q = q->prox;
    }
    return n;
}

void LiberaPolinomio(Polinomio p){
    struct Termo *q;
    q = p->prox;

     while(q != p){
       p->prox = q->prox;
       free(q);
       q = p->prox;
     }
    free(p);
}

Polinomio Derivada(Polinomio p){
    Polinomio d;
    struct Termo *q;
    float dcoef;
    int dexpo;
    q = p->prox;
    d = CriaPolinomioNulo();
    while (q->expo != 0 && q->expo != -1 ){
        dcoef = 0;
        dexpo = 0;
        if(q->expo == 1){
            InsereTermo(d, q->coef, 0);
            break;
        }
        else{
                dcoef = q->coef * q->expo;
                dexpo = q->expo - 1;
                InsereTermo(d, dcoef, dexpo);
                }
        q = q->prox;
    }
    return d;
    }
Polinomio DerivadaSegunda(Polinomio p){
    Polinomio dd;
    struct Termo *q;
    float dcoef;
    int dexpo;
    q = p->prox;
    dd = CriaPolinomioNulo();
    while (q->expo != 0 && q->expo != 1 && q->expo != -1){
        dcoef = 0;
        dexpo = 0;
        if(q->expo == 2){
            InsereTermo(dd, (q->coef*q->expo), 0);
            break;
        }
        else{
            dcoef = (q->coef * q->expo)*(q->expo -1);
            dexpo = q->expo - 2;
            InsereTermo(dd, dcoef, dexpo);
        }
        q = q->prox;
    }
    return dd;


}

int main(){
  Polinomio p;
  char s[1000];
  float x;
  scanf("%f",&x);
  fgets(s,1000-1,stdin);
  printf("%s", s);
  p = CriaPolinomio(s);
  printf("%.2f\n", Valor(p, x));
  ImprimePolinomio(Derivada(p));
  ImprimePolinomio(DerivadaSegunda(p));
  LiberaPolinomio(p);
  return 0;
}