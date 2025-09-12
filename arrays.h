struct array {
    char terminal[2];
    conteudo conteudoArray;
    array *cabeca, *cauda;
}; typedef struct array Array; //V para string, F para numero quebrado, N para numero normal 

union conteudo {
    char frase[20];
    float numeroQuebrado;
    int numeroInteiro;
};

