struct pilhaOperadorValor {
    union valorOperador valorOperador;
    pilhaOperadorValor *prox;
}; typedef struct pilhaOperadorValor PilhaOperadorValor;

union valorOperador {
    char operador[2];
    float valor;
};

void init (PilhaOperadorValor **pilha) {
    *pilha = NULL;
}

void push (PilhaOperadorValor **pilha, char info[30]) {
        
}

