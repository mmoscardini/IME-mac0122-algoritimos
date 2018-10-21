#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

float Valor(Polinomio p, float x){
    float result = 0, y = 1;
    struct Termo *t;
    t = p->prox;
    while(t != p){
        float expoent = t->expo;
        while (expoent > 0){
            y *= x; 
            --expoent;
        }
        result += y*t->coef;
        y=1;
        t = t->prox;
    }
    printf("%5.2f \n", result);
    return result;
};

void LiberaPolinomio(Polinomio p){
    struct Termo *t = p, *q;
    while(t != p){
        q = t->prox;
        free(t);
        t = q;
    }
    return;
};

Polinomio Derivada(Polinomio p){
    struct Termo *t, *ant;
    ant = p;
    t = p->prox;
    while(t != p){
        if (t->expo == 0){
            ant->prox = p;
        }
        else{
            t->coef *= t->expo;
            t->expo -= 1;
        }
        ant = t;
        t = t->prox;
    }
    if(p == p->prox){
        p = CriaPolinomioNulo();
    }
    return p;

};

Polinomio DerivadaSegunda(Polinomio p){
    p = Derivada(p);
    p = Derivada(p);
    return p;
};

int main()
{
    char s[200];
    float x;
    scanf("%f%*c %[^\n]",&x ,s);
    /* printf("%f\n", x);
    printf("%s\n", s);
     */

    Polinomio p, d;
    p = CriaPolinomio(s);
    Valor (p, x);
    d = Derivada(p);
    ImprimePolinomio(d);
    d = Derivada(d);
    ImprimePolinomio(d);
    
    LiberaPolinomio(p);
    LiberaPolinomio(d);
    return 0;
}
