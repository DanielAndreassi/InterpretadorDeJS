#include "operacaoMatematica.h"

struct pilhaOperacaoMatematica {
    ListaGenOperacao *listaOperacao;
    pilhaOperacaoMatematica *prox;
}; typedef struct pilhaOperacaoMatematica PilhaOperacaoMatematica;

void init (PilhaOperacaoMatematica **pilha) {
    *pilha = NULL;
}

void push (PilhaOperacaoMatematica **pilha, ListaGenOperacao *lista) {
    PilhaOperacaoMatematica *nova = malloc(sizeof(PilhaOperacaoMatematica));

    nova->listaOperacao =  lista;
    nova->prox = *pilha;
    *pilha = nova;
}

char isEmpty (PilhaOperacaoMatematica *pilha) {
    return pilha == NULL;
}

PilhaOperacaoMatematica top (PilhaOperacaoMatematica *pilha) {
    if(!isEmpty(pilha)) return *pilha;
} 

void pop (PilhaOperacaoMatematica **pilha,ListaGenOperacao *lista) {
    PilhaOperacaoMatematica *aux = (*pilha)->prox;

    if(!isEmpty(*pilha)) {
        lista = (*pilha)->listaOperacao;
        *pilha = aux->prox;
        free(aux);
    }
}

void limparPilha(pilhaOperacaoMatematica **pilha) {
    PilhaOperacaoMatematica *aux = (*pilha);
    while(!isEmpty(*pilha)) {
        aux = (*pilha);
        *pilha = (*pilha)->prox;
        free(aux);
    }
}

