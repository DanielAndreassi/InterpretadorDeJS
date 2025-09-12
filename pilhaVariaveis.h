struct pilhaVariaveis {
    char variavel[30];
    char valor [50];
    pProgama *ponteiro;
    struct pilhaVariaveis *prox;
}; typedef struct pilhaVariaveis PilhaVariaveis;

void init (PilhaVariaveis **pilha) {
    *pilha = NULL;
}

void push (PilhaVariaveis **pilha, char *variavel, char *valor, pProgama *ponteiro) {
    PilhaVariaveis *nova = malloc(sizeof(PilhaVariaveis));
    strcpy(nova->variavel, variavel);
    strcpy(nova->valor, valor);
    nova->ponteiro = ponteiro;
    nova->prox = *pilha;
    *pilha = nova;
}

char isEmpty (PilhaVariaveis *pilha) {
    return pilha == NULL;
}

PilhaVariaveis top (PilhaVariaveis *pilha) {
    if(!isEmpty(pilha)) return *pilha;

    return NULL;
}

void pop (PilhaVariaveis **pilha, char *variavel, char *valor, pProgama *ponteiro) {
    PilhaVariaveis *aux = (*pilha)->prox;
    if(!isEmpty(*pilha)) {
        *variavel = (*pilha)->variavel;
        *valor = (*pilha)->valor;
        *ponteiro = (*pilha)->ponteiro;
        *pilha = aux->prox;
        free(aux);
    }
}


void limparPilha(PilhaVariaveis **pilha) {
    PilhaVariaveis *aux;
    while(!isEmpty(*pilha)) {
        aux = (*pilha);
        *pilha = (* pilha)->prox;
        free(aux);
    }
}
