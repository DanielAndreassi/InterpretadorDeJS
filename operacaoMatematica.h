#include "pilhaOperacaoMatematica.h"

union tipo
{
    float valor;
    char operador[3];
    char funcao[20];
};

struct listaGenOperacao {
    char terminal[2]; //V = valor,O = operacao,F = funcao
    union tipo info;
    struct listaGenOperacao *cabeca, *cauda;
}; typedef struct listaGenOperacao ListaGenOperacao;

// usar para percorrer a listaGen em questao para resolver e devolver para o cabeca que esta como 0, a partir disso continuar a resolver a que esta na pilha
//como explicado em aula
struct termo {
    char informacao[20];
    struct termo *prox;
}; typedef struct termo Termo;

ListaGenOperacao *criaNo(char info[20]) {
    //o cria no tem que verificar se V,O ou F e consideranco isso para converter o valor
}

float resolverEquacao(Termo **listaTermo) {
    listaGenOperacao *lista = NULL,*atual;
    //considerando que a listaTermo ja passou pela funcao de criar ela, como uma lista encadeada com tudo separado //criarListaComOperacao()
    PilhaOperacaoMatematica *pilhaAndar *pilhaCabeca;
    init(&pilhaAndar);
    init(&pilhaCabeca);
    //considerando que a equacao nao esta nullo
    while(*listaTermo != NULL) {
        if(lista == NULL) {
            lista = atual = criaNo(listaTermo->informacao);
            push(&pilhaCabeca,lista);
        }
        else if(strcmp(listaTermo->info,"(") == 0) {
            atual->cauda = criaNo("0");
            atual = atual->cauda;
            push(&pilhaAndar,atual);
            push(&pilhaCabeca,atual);
            lista = lista->prox;
            atual->cabeca = criaNo(listaTermo->informacao);
        }
    }
}

Termo *ciarListaComOperacao (char equacao[200]) {

}